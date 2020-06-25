#lang racket

;Praca grupowa Filip Komorowski, Maurycy Borkowski, Marcin Badowski, Piotr Piesiak


(define (inc n)
  (+ n 1))

;;; tagged lists
(define (tagged-list? len-xs tag xs)
  (and (list? xs)
       (= len-xs (length xs))
       (eq? (first xs) tag)))

;;; ordered elements
(define (make-elem pri val)
  (cons pri val))

(define (elem-priority x)
  (car x))

(define (elem-val x)
  (cdr x))

;;; leftist heaps (after Okasaki)

;; data representation
(define leaf 'leaf)

(define (leaf? h) (eq? 'leaf h))

(define (hnode? h)
  (and (tagged-list? 5 'hnode h)
       (natural? (caddr h))))

(define (make-hnode elem heap-a heap-b); ranga nowego to ranga prawego poddrzewa + 1
  (if (> (rank heap-b) (rank heap-a)) ;jesli b jest mniejszy rowny to znaczy ze jest prawy
      (list 'hnode elem (inc (rank heap-b)) heap-b heap-a)
      (list 'hnode elem (inc (rank heap-a)) heap-a heap-b)))

(define (hnode-elem h)
  (second h))

(define (hnode-left h)
  (fourth h))

(define (hnode-right h)
  (fifth h))

(define (hnode-rank h)
  (third h))

(define (hord? p h)
  (or (leaf? h)
      (<= p (elem-priority (hnode-elem h)))))

(define (heap? h)
  (or (leaf? h)
      (and (hnode? h)
           (heap? (hnode-left h))
           (heap? (hnode-right h))
           (<= (rank (hnode-right h))
               (rank (hnode-left h)))
           (= (rank h) (inc (rank (hnode-right h))))
           (hord? (elem-priority (hnode-elem h))
                  (hnode-left h))
           (hord? (elem-priority (hnode-elem h))
                  (hnode-right h)))))

(define (rank h)
  (if (leaf? h)
      0
      (hnode-rank h)))

;; operations

(define empty-heap leaf)

(define (heap-empty? h)
  (leaf? h))

(define (heap-insert elt heap)
  (heap-merge heap (make-hnode elt leaf leaf)))

(define (heap-min heap)
  (hnode-elem heap))

(define (heap-pop heap)
  (heap-merge (hnode-left heap) (hnode-right heap)))

(define (heap-merge h1 h2)
  (cond
   [(leaf? h1) h2]
   [(leaf? h2) h1]
   [else
    (let ([el1min (heap-min h1)]
          [el2min (heap-min h2)])
          (if (< (elem-priority el1min) (elem-priority el2min))
              (make-hnode el1min (hnode-left h1)
                         (heap-merge (hnode-right h1) h2))
              ;elem z h2 jest mniejszy
              (make-hnode el2min (hnode-left h2)
                         (heap-merge (hnode-right h2) h1))))]))

;;; check that a list is sorted (useful for longish lists)
(define (sorted? xs)
  (cond [(null? xs)              true]
        [(null? (cdr xs))        true]
        [(<= (car xs) (cadr xs)) (sorted? (cdr xs))]
        [else                    false]))

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

      
