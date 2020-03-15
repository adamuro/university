#lang racket

(define (compose f g)
  (lambda (x) (f (g x))))

;; ((compose square inc) 5)
;; 36
;; ((compose inc square) 5)
;; 25

(define (repeated p n)
  (if (= n 0)
      identity
      (compose p (repeated p (- n 1)))))

(define (product val inc start end)
  (if (> start end)
      1
      (* (val start) (product val inc (inc start) end))))

(define (accumulate combiner null-value term a next b)
  (if(> a b)
     null-value
     (combiner (term a) (accumulate combiner null-value term (next a) next b))))

(define (square x)
  (* x x))

(define (cont-frac num den k)
  (define (cont-frac-iter num den i k)
    (if(= i k)
       0
       (/ (num i) (+ (den i) (cont-frac-iter num den (+ i 1) k)))))
  (cont-frac-iter num den 1 k))

(define (arctan x)
  (/ x (+ 1 (cont-frac (lambda (i) (square(* i x))) (lambda (x) (+ (* x 2) 1)) 10000))))








