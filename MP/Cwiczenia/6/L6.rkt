#lang racket

(struct node (data l r) #:transparent)
(struct leaf () #:transparent)

(define(height t)
  (cond[(leaf? t) 0]
       [(node? t) (+ 1 (max (height (node-l t))
                            (height (node-r t))))]))
(define(height-pm t)
  (match t [(leaf) 0]
          [(node d l r) (+ 1 (max (height-pm l)
                                  (height-pm r)))]))
(display "Node structs")
(node 2 (leaf) (leaf))

;===================================================
(struct const (val) #:transparent)
(struct binop (op l r) #:transparent)

(define 2+2*2 (binop '+ (const 2)
                     (binop '* (const 2)
                            (const 2))))
2+2*2
;===================================================
(define (expr? e)
  (match e
    [(const n) (number? n)]
    [(binop op l r) (and (symbol? op) (expr? l) (expr? r))]
    [_ #f]))
(define (value? v)
  (number? v))
;===================================================
(define (op->proc op)
  (match op ['+ +] ['- -] ['* *] ['/ /] ['^ expt] ['abs abs]))

(define (eval e)
  (match e
    [(const n) n]
    [(binop op l r) ((op->proc op) (eval l) (eval r))]
    [(unop op x) ((op->proc op) (eval x))]))
    
  
  


(display "eval")
(eval 2+2*2)
;===================================================
(define (rpn-expr? e)
  (and (list? e)
       (pair? e)
       (andmap (lambda (x) (or (number? x) (member x '(+ - *))))
               e)))
;====================================================
(struct stack (xs) #:transparent)

(define empty-stack (stack null))
(define (empty-stack? s) (null? (stack-xs s)))
(define (top s) (car (stack-xs s)))
(define (push a s) (stack (cons a (stack-xs s))))
(define (pop s) (stack (cdr (stack-xs s))))

(define stos (stack (list 1 2 3)))
(display "Stacks")
stos
(stack-xs stos)
;====================================================
(define (eval-am e s)
  (cond [(null? e)
         (top s)]
        [(number? (car e))
         (eval-am (cdr e) (push (car e) s))]
        [(symbol? (car e))
         (eval-am (cdr e)
                  (push ((op->proc (car e)) (top s) (top (pop s)))
                        (pop (pop s))))]))

(define (eval-rpn e) (define 2+2*2 (binop '+ (const 2)
                     (binop '* (const 2)
                            (const 2))))(eval-am e empty-stack))

(define (arith->rpn e)
  (match e
    [(const n) (list n)]
    [(binop op l r) (append (arith->rpn l)
                            (arith->rpn r)
                            (list op))]))
(display "eval-rpn")
(eval-rpn (arith->rpn 2+2*2))
(display "eval-am")
(eval-am (list 10 2 '* 2 '+) empty-stack)
;==================================================
(define (parse q)
  (cond [(number? q) (const q)]
        [(and (list? q) (eq? (length q) 3) (symbol? (first q)))
         (binop (first q) (parse (second q)) (parse (third q)))]))

(eval (parse '(+ (* 2 3) (* 4 5))))


;===================================================
;Z1

;(a) skladnia konkretna
(+ (+ (/ 8 (+ 2 3)) 10) 1)
;Skladnia abstakcyjna
(eval (binop '+ (binop '+ (binop '/ (const 8) (binop '+ (const 2) (const 3))) (const 10)) (const 1)))

;Z2================================================================

(define (cont-frac-expr num den k)
  (define (go acc i)
    (if (= i 0)
        acc
        (go (binop '/ (const (num i)) (binop '+ (const (den 1)) acc)) (- i 1))))
  (go (const 0) k))

(define (pi-expr k)
  (binop '+
         (const 3.0)
         (cont-frac-expr
          (lambda (n) (sqr (- (* 2 n) 1)))
          (lambda _ 6)
          k)))

(eval (pi-expr 100))

;Z3================================================================


(struct unop (op x) #:transparent)

(define (parse-op proc)
  (cond [(eq? proc 'expt) '^]
        [else proc]))












