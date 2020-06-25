#lang racket

(provide nth-root)
(provide dumpings)

(define (average-damp f)
  (lambda (x) (/ (+ x (f x)) 2)))

(define (dec x) (- x 1))

(define (compose f g)
  (lambda (x) (f (g x))))

(define (repeated p n)
  (if (= n 0)
      (identity p)
      (compose p (repeated p (- n 1)))))

(define (fixed-point f x0)
  (define (close-enough? a b)
    (< (abs(- a b)) 0.0000001))
  (let ((x1 (f x0)))
    (if(close-enough? x0 x1)
       x0
       (fixed-point f x1))))

(define (dumpings n x level)
  (define (avg y) (/ x (expt y (dec n))))
    (fixed-point ((repeated average-damp (dec level)) avg) 1.0))

;testy stopnia tłumienia
(dumpings 2 4 1)
(dumpings 3 27 1)
(dumpings 4 81 2) ; tu zwiekszam stopien
(dumpings 5 32 2)
(dumpings 6 64 2)
(dumpings 7 128 2)
(dumpings 8 256 3) ; tu zwiekszam
(dumpings 9 512 3)
(dumpings 10 1024 3)
(dumpings 11 2048 3)
(dumpings 12 4096 3)
(dumpings 13 8192 3)
(dumpings 14 16384 3)
(dumpings 15 32768 3)
(dumpings 16 65536 4) ; tu zwiekszam
;Wyglada na to ze musze zwiekszyc dla kazdego pierwiastka stopnia bedacego kolejna potega 2
;czyli dla n-root bedziemy musieli tłumić floor(log(n)) razy

(define (nth-root n x)
  (define stopien
    (truncate (log n 2)))
  (dumpings n x stopien))

(display "test finalnej funkcji\n")

(nth-root 10 10000000000)