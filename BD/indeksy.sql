-- 103, BRIN, range_inclusion_ops, <<    --Filip Komorowski, 315373

-- Indeks BRIN (Block Range Index) jest najbardziej przydatny kiedy mamy bardzo dużo danych w tabeli i istnieje pewna korelacja pomiędzy wartością wiersza i jego lokalizacją w tabeli. 
--Przykładowo, gdy mamy tabelę z datami transakcji, to te z wcześniejszą datą będa wyżej niż z późniejszą, dodatkowo bliskie daty będą blisko siebie.
-- BRIN grupuje dane do bloków danych, trzymając lokalizacje pierwszego bloku or minimum i maximum wartości dla każdego bloku.
-- Korzystając z BRIN, możemy sprytnie omijać duże bloki rekordów,
-- o których wiemy, że nie spełniają zapytania i dzięki temu jesteśmy w stanie znacznie szybciej znajdować wyniki niż przeglądając wszystko po kolei.


--Tworzenie tabeli i wrzucanie danych
CREATE TABLE test(id serial PRIMARY KEY, range int8range, losowy_text text);

INSERT INTO test (range, losowy_text) ( SELECT int8range((random()*10+1)::int, (random()*10000+12)::int), md5(random()::text) from generate_series(1,10000000) ORDER BY 1);

VACUUM ANALYZE;
	
-- Testy przed indeksowaniem i ich czasy wykonania

EXPLAIN ANALYZE select id from test where range << int8range(10, 1000);

-- Seq Scan on test  (cost=10000000000.00..10000238637.70 rows=1 width=4) (actual time=1111.040..1111.041 rows=0 loops=1)
--   Filter: (range << '[10,1000)'::int8range)
--   Rows Removed by Filter: 10000000
-- Planning Time: 0.304 ms
-- JIT:
--   Functions: 4
--   Options: Inlining true, Optimization true, Expressions true, Deforming true
--   Timing: Generation 1.507 ms, Inlining 16.959 ms, Optimization 27.918 ms, Emission 8.064 ms, Total 54.448 ms
-- Execution Time: 1112.606 ms
--(9 rows)


EXPLAIN ANALYZE select id from test where losowy_text LIKE '%a%b%' and range << int8range(2000, 3000);

--Seq Scan on test  (cost=10000000000.00..10000263637.84 rows=1333992 width=4) (actual time=72.438..1703.961 rows=1199188 loops=1)
--   Filter: ((losowy_text ~~ '%a%b%'::text) AND (range << '[2000,3000)'::int8range))
--   Rows Removed by Filter: 8800812
-- Planning Time: 0.402 ms
-- JIT:
--   Functions: 4
--   Options: Inlining true, Optimization true, Expressions true, Deforming true
--   Timing: Generation 1.636 ms, Inlining 28.237 ms, Optimization 31.633 ms, Emission 11.644 ms, Total 73.150 ms
-- Execution Time: 1733.211 ms
--(9 rows)


-- Tworzenie indeksu

CREATE INDEX ON test USING BRIN (range range_inclusion_ops);

VACUUM ANALYZE test;
--set enable_seqscan=off; <-- musiałem z tego skorzystać

EXPLAIN ANALYZE select id from test where range << int8range(10, 1000);

-- Gather  (cost=1052.42..166773.14 rows=1 width=4) (actual time=844.820..856.735 rows=0 loops=1)
--   Workers Planned: 2
--   Workers Launched: 2
--   ->  Parallel Bitmap Heap Scan on test  (cost=52.42..165773.04 rows=1 width=4) (actual time=788.643..788.644 rows=0 loops=3)
--         Recheck Cond: (range << '[10,1000)'::int8range)
--         Rows Removed by Index Recheck: 2834773
--         Heap Blocks: lossy=33764
--         ->  Bitmap Index Scan on test_range_idx  (cost=0.00..52.42 rows=10000056 width=0) (actual time=8.744..8.745 rows=966400 --loops=1)
--               Index Cond: (range << '[10,1000)'::int8range)
-- Planning Time: 1.148 ms
-- JIT:
--   Functions: 12
--   Options: Inlining false, Optimization false, Expressions true, Deforming true
--   Timing: Generation 2.939 ms, Inlining 0.000 ms, Optimization 4.203 ms, Emission 15.153 ms, Total 22.295 ms
-- Execution Time: 858.147 ms
-- (15 rows)


EXPLAIN ANALYZE select id from test where losowy_text LIKE '%a%b%' and range << int8range(2000, 3000);

-- Bitmap Heap Scan on test  (cost=359.16..263997.00 rows=1226957 width=4) (actual time=17.679..1950.960 rows=1199188 loops=1)
--   Recheck Cond: (range << '[2000,3000)'::int8range)
--   Rows Removed by Index Recheck: 8010057
--   Filter: (losowy_text ~~ '%a%b%'::text)
--   Rows Removed by Filter: 790755
--   Heap Blocks: lossy=113637
--   ->  Bitmap Index Scan on test_range_idx  (cost=0.00..52.42 rows=10000056 width=0) (actual time=11.290..11.291 rows=1136640 loops=1)
--         Index Cond: (range << '[2000,3000)'::int8range)
-- Planning Time: 0.274 ms
-- JIT:
--   Functions: 6
--   Options: Inlining false, Optimization false, Expressions true, Deforming true
--   Timing: Generation 2.636 ms, Inlining 0.000 ms, Optimization 0.442 ms, Emission 5.694 ms, Total 8.772 ms
-- Execution Time: 1984.313 ms
-- (14 rows)



-- Przy pierwszym zapytaniu udało się uzyskać trochę lepszy czas, ale widać, że nie są to jakieś kosmiczne różnice. Z tego co udało mi się wczytać w internecie to faktycznie ciężko uzyskać widoczną różnicę w działaniu czasowym.(stąd tak duża baza danych do testów) BRIN za to ma przewagę nad BTree w zajmowanej pamięci. Przy milionie rekordów BTree zajęłoby 21Gb a BRIN 1.7MB. (źródło: https://blog.crunchydata.com/blog/avoiding-the-pitfalls-of-brin-indexes-in-postgres#:~:text=A%20BRIN%20is%20a%20Block,all%20values%20in%20those%20blocks.)
