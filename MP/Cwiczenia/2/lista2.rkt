#lang racket

(define (square x)(* x x))

(define (inc x)(+ x 1))

;drugie
(define (compose f g)
  (lambda (x) (f (g x))))

;trzecie
(define (repeated p n)
  (if (= n 0)
      identity
      (compose p
               (repeated p (- n 1)))))
;czwarte
(define (product-rec term a next b)
  (if (> a b)
      1
      (* (term a) (product-rec term (next a) next b))))

(define (product-iter term a next b)
  (define (product-acc a acc)
    (if (> a b)
        acc
        (product-acc (next a) (* acc (term a)))))
  (product-acc a 1))

(product-rec (lambda (x) x) 1 inc 3)
(product-iter (lambda(x) x) 1 inc 3)

;szoste
;iteracyjne
(define (cont-frac-iter num den k)
  (define (iter a result)
    (if (= a 0)
        result
        (iter (- a 1) (/ (num a)(+ (den a) result)))))
       (iter k 0))
;rekurencyjna
(define (cont-frac num den k)
  (if (= k 0)
      0
      (/ (num 1) (+ (den 1) (cont-frac (compose num inc) (compose den inc) (- k 1))))))

;siodme
(define (chain-pi iter-number)
  (+ 3 (cont-frac (lambda(x)(square (- (* 2 x) 1))) (lambda(x) 6.0) iter-number)))
