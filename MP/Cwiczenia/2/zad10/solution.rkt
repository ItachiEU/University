#lang racket

(provide cont-frac)

(define (square x)(* x x))

(define (inc x)(+ x 1))

(define (cont-frac num den) ; przy takiej dokladnosci dziala do 14, potem sie zapetla
  (define (iter A0 A1 B0 B1 f k)
      (define (close-enough? a b) 
    (< (abs(- a b)) 0.00001))

    (define Ak (+ (* (den k) A1) (* (num k) A0))) 
    (define Bk (+ (* (den k) B1) (* (num k) B0)))
    (define Fk (/ Ak Bk))
    
    (if (close-enough? f Fk)
        f
        (iter A1 Ak B1 Bk Fk (inc k))))
  (iter 1 0 0 1 0 1))


(define (arctg x)  ;;sprawdzam cw 8
  (/ x
     (+ 1
        (cont-frac (lambda (i) (square(* i x)))
                   (lambda (i) (inc(* 2.0 i)))))))

;testy
(display (arctg 10))
(newline)
(display (atan 10))
(newline)
(newline)
(display (arctg 5))
(newline)
(display (atan 5))
(newline)
(newline)
(display (arctg -3))
(newline)
(display (atan -3))
(newline)
(newline)


