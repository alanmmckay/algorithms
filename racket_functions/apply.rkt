#lang racket

(define apply
  (lambda (func lst)
    (if (equal? 1 (length lst))
      (first lst)
      (func (first lst) (apply func (rest lst)))
    )
  )
)

(provide apply)
