#lang racket

;Praca grupowa Filip Komorowski, Maurycy Borkowski,Piotr Piesiak, Marcin Badowski

(provide (contract-out
            [with-labels with-labels/c]
            [foldr-map foldr-map/c]
            [pair-from pair-from/c]))

(provide with-labels/c foldr-map/c pair-from/c)

(define with-labels/c
  (parametric->/c [a b] (-> (-> a b) (listof a) (listof (list/c b a)))))


(define (with-labels func xs)
  (define (labels-iter helpxs xs)
    (if (null? xs)
        (reverse helpxs)
        (labels-iter (cons (list (func (car xs)) (car xs)) helpxs) (cdr xs))))
  (labels-iter null xs))

(define pair-from/c
  (parametric->/c [a b c] (-> (-> a b) (-> a c) (-> a (cons/c b c)))))

(define (pair-from f g)
  (lambda (x) (cons (f x) (g x))))

(define foldr-map/c
  (parametric->/c [a b c] (-> (-> a b (cons/c a b)) b (listof a) (cons/c (listof a) b))))

(define (foldr-map f a xs)
   (define (it a xs ys)
      (if (null? xs)
          (cons ys a)
          (let [(p (f (car xs) a))]
            (it (cdr p)
                 (cdr xs)
                 (cons (car p) ys)))))
   (it a (reverse xs) null))