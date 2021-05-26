#lang racket

(define map
  (lambda (func lst)
    (if (null? lst)
      '()
      (cons (func (first lst)) (map func (rest lst)))
    )
  )
)

(provide map)

