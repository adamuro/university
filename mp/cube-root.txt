#lang racket

(define (square x)
  (* x x))

(define (cube x)
  (* x x x))

(define (dist x y)
  (abs (- x y)))

(define (abs x)
  (if (< x 0)
      (- x)
      x))

(define (cube-root x)
  (define (improve guess)
    (/ (+ (/ x (square guess)) (* 2 guess)) 3))
  (define (good-enough? g)
    (< (dist x (cube g))
       0.0001))
  (define (iter guess)
    (if (good-enough? guess)
        guess
        (iter (improve guess))))
  
  (iter 1.0))

(provide cube-root)