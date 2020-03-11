#lang racket

(provide cube-root)

(define (square x)(* x x))

(define (cube x)(* x x x))

(define (cube-root x)
  (define (good-enough? guess)
    (< (abs (- (cube guess) x)) 0.0001))
    (define (improve guess)
      (/ (+ (* guess 2) (/ x (square guess) ) ) 3))
    (define (cube-root-iter guess)
      (if (good-enough? guess)
          guess
          (cube-root-iter (improve guess))))
  (cube-root-iter 1.0))

;testy
(define test1 (cube-root 8))
(define test2 (cube-root 81))
(define test3 (cube-root 27))
(define test4 (cube-root -1000))
(define test5 (cube-root -1))
(define test6 (cube-root 1))
