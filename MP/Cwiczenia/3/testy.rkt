#lang racket

(define (reverse lista)
  (if (null? lista)
      null
      (append (reverse (cdr lista))(list (car lista)))))

(define (reverse-iter lista)
  (define (iter l1 l-result)
    (if (null? l1)
        l-result
        (iter (cdr l1)(cons (car l1) l-result))))
  (iter lista null))

(define (insert xs n)
  (define (insert-pom pre suf)
    (if (null? suf)
        (append pre (list n))
        (if (< n (car suf))
           (append pre (list n) suf)
           (insert-pom (append pre (list (car suf))) (cdr suf)))))
  (insert-pom null xs))


(define (insert-sort lista)
  (define (iter result pom)
	(if (null? pom)
    	result
    	(iter (insert result (car pom)) (cdr pom))))
  (iter null lista))

(define (split lista1)
  (define (split-iter pref suf)
    (if (>= (length pref) (/ (length lista1) 2))
        (cons pref suf)
        (split-iter (append pref (list (car suf) )) (cdr suf))))
  (split-iter null lista1))



(define (merge lista1 lista2)
  (define (merge-helper l1 l2 result)
    (cond
         ((and (null? l1) (null? l2))
            result)
          ((null? l1)
            (merge-helper l1 null (append result l2)))
          ((null? l2)
            (merge-helper null l2 (append result l1)))
          ((<= (car l1) (car l2))
           (merge-helper (cdr l1) l2 (append result (list(car l1)))) )
          (else
           (merge-helper l1 (cdr l2) (append result (list(car l2)))) )
          )
    )
  (merge-helper lista1 lista2 null))

(define (merge-sort lista))
          