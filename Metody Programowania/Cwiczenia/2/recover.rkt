#lang racket
(define (square x)(* x x))

(define (inc x)(+ x 1))

;drugie
(define (compose f g)
  (lambda (x) (f (g x))))

;trzecie
(define (repeated p n)
  (if (= n 1)
      (identity p)
      (repeated (compose p p) (- n 1))))
;czwarte
