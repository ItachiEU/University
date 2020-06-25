#lang racket

;Praca grupowa
;Filip Komorowski, Piotr Piesiak, Maurycy Borkowski, Marcin Badowski

(provide partition quicksort)

(define (partition n xs)
  (define (pom lista small big)
	(if (null? lista)
    	(cons small big)
    	(if (<= (car lista) n)
        	(pom (cdr lista) (append small (list (car lista))) big)
        	(pom (cdr lista) small (append big (list (car lista)))))))
  (pom xs null null))

(define (quicksort L)
  (if (null? L)
      L
      (append
       (append
        (quicksort (car (partition (car L) (cdr L)))) (list (car L)))
        (quicksort (cdr (partition (car L) (cdr L)))))))
