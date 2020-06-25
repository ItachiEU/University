#lang racket

(provide cube-root)

(define (abs x)(if (< x 0) (- x) x))

(define (square x)(* x x))

(define (cube x)(* x x x))

(define (cube-root x)
  (define (good-enough? guess)
    (< (abs (- (cube guess) x)) 0.0001)
    (define (improve guess)
      (/ (+ (* guess 2) (/ x (square guess) ) ) 3))
    (define (cube-root-iter guess)
      (if (good-enough? guess)
          guess
          (cube-root-iter (improve guess)))))
  (cube-root-iter 1.0))
