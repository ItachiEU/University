#lang racket

;Praca grupowa
;Filip Komorowski, Piotr Piesiak, Maurycy Borkowski, Marcin Badowski

(define (partition n xs)
  (define (pom lista small big)
	(if (null? lista)
    	(cons small big)
    	(if (<= (car lista) n)
        	(pom (cdr lista) (append small (list (car lista))) big)
        	(pom (cdr lista) small (append big (list (car lista)))))))
  (pom xs null null))

(define (quick-sort lista)
  (if (null? lista)
      lista
      (append (quicksort (car (partition (car lista) lista))) (quicksort (cdr (partition (car lista) lista))))))


