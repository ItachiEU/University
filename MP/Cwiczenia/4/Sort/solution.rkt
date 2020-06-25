#lang racket

;Praca grupowa Filip Komorowski, Maurycy Borkowski, Marcin Badowski, Piotr Piesiak

(require "leftist.rkt")
(provide heapsort)

;;sort

(define (heapsort l)
  (define (policz kopiec)
    (if (heap-empty? kopiec)
        null
        (cons (cdr (heap-min kopiec))(policz (heap-pop kopiec)))))
  (define (skopcuj lista)
    (define (iter h lista)
      (if (null? lista)
          h
          (iter (heap-insert (make-elem (car lista) (car lista)) h) (cdr lista))))
    (iter empty-heap lista))
  (policz (skopcuj l)))
