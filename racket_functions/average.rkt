#lang racket

;;a function which takes a list of integers and returns the average

;;recall that a cond is a set of expressions which are composed of 
;;a conditional and a return

(define (get-sum number-list)
  (cond 
    (
      (> (length number-list) 1)
      (+ (first number-list) (get-sum (rest number-list) ) )
    )
    (else (first number-list))
  )
)

(define (average number-list)
  (/ (get-sum number-list) (length number-list))
)

(provide average)
