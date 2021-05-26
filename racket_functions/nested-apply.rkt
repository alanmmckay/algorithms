#lang racket

(define nested-apply
  (lambda (func lst)
    (if (equal? 1 (length lst))
      (first lst)
      (func (nested-apply-exp func (first lst)) (nested-apply func (rest lst)))
    )
  )
)

(define nested-apply-exp
  (lambda (func exp)
    (if (list? exp)
      (nested-apply func exp)
      exp
    )
  )
)
