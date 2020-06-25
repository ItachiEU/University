#lang racket
;Praca grupowa
;Filip Komorowski, Piotr Piesiak, Maurycy Borkowski, Marcin Badowski

(provide merge-sort)

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

(define (merge-sort lista)
  (define temporary (split lista))
  (if (= (length lista) 1)
      lista
      (merge (merge-sort (car temporary)) (merge-sort (cdr temporary)))))
          