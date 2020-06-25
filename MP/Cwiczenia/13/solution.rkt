#lang typed/racket
;; Praca grupowa Piotr Piesiak Filip Komorowski Maurycy Borkowski Marcin Badowski
(provide parse typecheck)
(define-type Expr (U const binop var-expr let-expr if-expr))
(define-type Value (U Number Boolean))
(define-type BinopSym (U '+ '- '* '/ '% '= '> '>= '< '<= 'and 'or))

(struct const ([val : Value]) #:transparent)
(struct binop ([op : BinopSym] [l : Expr] [r : Expr]) #:transparent)
(struct var-expr ([id : Symbol])  #:transparent)
(struct let-expr ([id : Symbol] [e1 : Expr] [e2 : Expr]) #:transparent)
(struct if-expr ([eb : Expr] [et : Expr] [ef : Expr]) #:transparent)

(define-predicate binop-sym? BinopSym)
(define-predicate expr? Expr)
(define-predicate value? Value)

;; -----------------  ;;
;; Składnia konkretna ;;
;; -----------------  ;;



(define-type LetConcr (List 'let (List Symbol Any) Any))
(define-type IfConcr (List 'if Any Any Any))

(define-predicate let-concr? LetConcr)
(define-predicate if-concr? IfConcr)

(: parse (-> Any Expr))
(define (parse q)
  (match q
    [_ #:when (value? q) (const q)]
    [_ #:when (eq? q 'true) (const true)]
    [_ #:when (eq? q 'false) (const false)]
    [(list op e1 e2)
     #:when (binop-sym? op)
     (binop op (parse e1) (parse e2))]
    [_ #:when (symbol? q) (var-expr q)]
    [(list l e1 e2)
     #:when (let-concr? q)
     (let-expr (first e1) (parse (second e1)) (parse e2))]
    [(list i eb et ef)
     #:when (if-concr? q)
     (if-expr (parse eb) (parse et) (parse ef))]))

(define test-syntax '(+ 2 (* 2 2)))

(define test-expr (parse test-syntax))

; ---------- ;
; Srodowiska ;
; ---------- ;

(struct environ ([xs : (Listof (Pairof Symbol Value))]) #:transparent)

(: env-empty environ)
(define env-empty (environ null))

(: env-add (-> Symbol Value environ environ))
(define (env-add x v env)
  (environ (cons (cons x v) (environ-xs env))))

(: env-lookup (-> Symbol environ Value))
(define (env-lookup x env)
  
  (: assoc-lookup (-> (Listof (Pairof Symbol Value)) Value))
  (define (assoc-lookup xs)
    (cond [(null? xs) (error "Unknown identifier" x)]
          [(eq? x (car (car xs))) (cdr (car xs))]
          [else (assoc-lookup (cdr xs))]))
  (assoc-lookup (environ-xs env)))

; --------------- ;
; Środowiska typow ;
; ---------------- ;

(define-type Etype (U 'real 'boolean))
(struct environT ([xs : (Listof (Pairof Symbol Etype))]) #:transparent)

(: env-emptyT environT)
(define env-emptyT (environT null))

(: env-addT (-> Symbol Etype environT environT))
(define (env-addT x v env)
  (environT (cons (cons x v) (environT-xs env))))

(: env-lookupT (-> Symbol environT Etype))
(define (env-lookupT x env)
  
  (: assoc-lookup (-> (Listof (Pairof Symbol Etype)) Etype))
  (define (assoc-lookup xs)
    (cond [(null? xs) (error "Unknown identifier" x)]
          [(eq? x (car (car xs))) (cdr (car xs))]
          [else (assoc-lookup (cdr xs))]))
  (assoc-lookup (environT-xs env)))


; --------- ;
; TYPECHECK ;
; --------- ;


(: typecheck (-> Expr (U Etype #f)))

(define (typecheck e)
  (typecheck-env e env-emptyT))

(: rt (-> Etype Etype (U 'real #f)))
(: rlt (-> Etype Etype (U 'boolean #f)))
(: lt (-> Etype Etype (U 'boolean #f)))

(define (rt l r)
  (if (or (eq? l 'boolean) (eq? r 'boolean))
      #f
      'real))
(define (rlt l r)
  (if (or (eq? l 'boolean) (eq? r 'boolean))
      #f
      'boolean))
(define (lt l r)
  (if (or (eq? l 'real) (eq? r 'real))
      #f
      'boolean))

(: typecheck-env (-> Expr environT (U Etype #f)))
(define (typecheck-env e env)
  (match e
    [(const n)
     (cond
       [(number? n) 'real]
       [(boolean? n) 'boolean])]
    [(var-expr x) (let ([n (env-lookupT x env)])
                    (cond
                      [(eq? n 'real) 'real]
                      [(eq? n 'boolean) 'boolean]
                      [else #f]))]

   [(let-expr x e1 e2)
    (let ((tmp (typecheck-env e1 env)))
      (cond
        [(eq? tmp #f) #f]
        [else (typecheck-env e2 (env-addT x tmp env))]))]
     
    [(if-expr eb et ef)
     (let ((condit (typecheck-env eb env)))
       (if (not (eq? condit 'boolean))
           #f
           (let ( [tr (typecheck-env et env)] [fa (typecheck-env ef env)] )
             (cond
               [(or (eq? tr #f) (eq? fa #f)) #f]
               [(and (eq? tr 'boolean) (eq? fa 'boolean))
                     'boolean]
               [(and (eq? tr 'real) (eq? fa 'real))
                     'real]
               [else #f]))))]
    
    [(binop op l r) (let ( [left (typecheck-env l env)] [rigth (typecheck-env r env)] )
                      (cond
                        [(or (eq? left #f) (eq? rigth #f)) #f]
                        [else 
                          (match op
                            ['+ (rt left rigth)] ['- (rt left rigth)] ['* (rt left rigth)]
                            ['/ (rt left rigth)] ['% (rt left rigth)] ['= (rlt left rigth)]
                            ['> (rlt left rigth)] ['>= (rlt left rigth)] ['< (rlt left rigth)]
                            ['<= (rlt left rigth)] ['and (lt left rigth)] ['or  (lt left rigth)])]))]))

(define test1
  (parse '(+ 1 ( + 1 #f) )))
(define test2
  (parse '(and false (> 2 3))))
(define test3
  (parse '(> 1 false)))
(define test4
  (parse '(> 1 2)))
(define test5
  (parse '(if (> 2 1) (+ 2 3) (let (x 3) (+ x 5)))))
(define test6
  (parse '(if (> 2 true) (+ 2 3) (+ 3 5))))
(define test7
  (parse '(if (> 2 1) true (+ 3 5))))
(define test8
  (parse '(let (x (if (> 2 1) true (< 1 2))) (let (x 2) (+ 3 x)))))
; --------- ;
; EWALUACJA ;
; --------- ;

(: mdl (-> Value Value Value))
(: e (-> Value Value Value))
(: g (-> Value Value Value))
(: ge (-> Value Value Value))
(: l (-> Value Value Value))
(: le (-> Value Value Value))
(: andl (-> Value Value Value))
(: orl (-> Value Value Value))

(: sum (-> Value Value Value))
(: subtract (-> Value Value Value))
(: multiply (-> Value Value Value))
(: divide (-> Value Value Value))

(define (mdl x y)
  (cond
    [(and (exact-integer? x) (exact-integer? y)) (modulo x y)]
    [else (error "wrong arguments:" x y 'in: '%)]))
(define (e x y)
  (cond
    [(and (real? x) (real? y)) (= x y)]
    [else (error "wrong arguments:" x y 'in: '=)]))
(define (g x y)
  (cond
    [(and (real? x) (real? y)) (> x y)]
    [else (error "wrong arguments:" x y 'in: '>)]))

(define (ge x y)
  (cond
    [(and (real? x) (real? y)) (>= x y)]
    [else (error "wrong arguments:" x y 'in: '>=)]))

(define (l x y)
  (cond
    [(and (real? x) (real? y)) (< x y)]
    [else (error "wrong arguments:" x y 'in: '<)]))

(define (le x y)
  (cond
    [(and (real? x) (real? y)) (<= x y)]
    [else (error "wrong arguments:" x y 'in: '<=)]))

(define (andl x y)
  (cond
    [(and (boolean? x) (boolean? y)) (and x y)]
    [else (error "wrong arguments:" x y 'in: 'andl)]))

(define (orl x y)
  (cond
    [(and (boolean? x) (boolean? y)) (or x y)]
    [else (error "wrong arguments:" x y 'in: 'orl)]))


(define (sum x y)
  (cond
    [(and (number? x) (number? y)) (+ x y)]
    [else (error "wrong arguments:" x y 'in: '+)]))

(define (subtract x y)
  (cond
    [(and (number? x) (number? y)) (- x y)]
    [else (error "wrong arguments:" x y 'in: '-)]))

(define (multiply x y)
  (cond
    [(and (number? x) (number? y)) (* x y)]
    [else (error "wrong arguments:" x y 'in: '*)]))

(define (divide x y)
  (cond
    [(and (number? x) (number? y)) (/ x y)]
    [else (error "wrong arguments:" x y 'in: '+)])) 

(: op->proc (-> BinopSym (-> Value Value Value)))
(define (op->proc op)
  (match op
    ['+ sum] ['- subtract] ['* multiply] ['/ divide]
    ['% mdl] ['= e] ['> g] ['>= ge] ['< l] ['<= le]
    ['and andl] ['or  orl]))

(: eval (-> Expr Value))
(define (eval e)
  (match e
    [(const n) n]
    [(binop op l r) ((op->proc op) (eval l) (eval r))]))


(define (test) (eval test-expr))