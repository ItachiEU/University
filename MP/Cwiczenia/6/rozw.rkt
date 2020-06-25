#lang racket

(require "arith.rkt")

(struct const (val)  #:transparent )
(struct binop (op l r) #:transparent )

(define 2+2*2 (binop '+ (const 2)
                     (binop '* (const 2)
                            (const 2))))