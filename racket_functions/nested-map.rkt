#lang racket

(define nested-map
  (lambda (func lst)
    (if (null? lst)
      '()
      (cons (nested-map-exp func (first lst)) (nested-map func (rest lst)))
    )
  )
)

(define nested-map-exp
  (lambda (func exp)
    (if (list? exp)
      (nested-map func exp)
      (func exp)
    )
  )
)

(provide nested-map)
