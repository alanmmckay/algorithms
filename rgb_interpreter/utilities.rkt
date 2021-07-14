#lang racket

;; FILE: utilities.rkt
;; AUTHOR: Alan McKay
;; DATE: 04/15/20
;;; --- Utilities for Huey RGB language --- ;;;

(require "syntax-procs.rkt")
(provide rgb->bytes byte-limiter get-shift-operation multiplier element-of-list?)

;; A sugared means of grabbing all three of an RGB expression's parameters
(define rgb->bytes
  (lambda (rgb-expression)
    (list (rgb->first rgb-expression) (rgb->second rgb-expression) (rgb->third rgb-expression))
  )
)

;; A means to ensure a number stays a byte after arithmetic is performed.
(define byte-limiter
  (lambda (number)
    (cond
      ((< number 0) 0)
      ((> number 255) 255)
      (else number)
    )
  )
)

;; Used for the shift operation during preprocessing.
(define get-shift-operation
  (lambda (shift-factor)
    (if (positive? shift-factor)
      '+
      '-
    )
  )
)

;; Used to evaluate the 1-color-operation '*'
;; Proud of this one! First time I've found a good...
;; ... use of currying a function on my own volition.
(define multiplier
  (lambda (factor)
    (lambda (value)
      (inexact->exact (floor (* factor value)))
    )
  )
)

(define element-of-list?
  (lambda (entity lst)
    (if (null? lst)
      #f
      (if (eq? entity (first lst))
        #t
        (element-of-list? entity (rest lst))
      )
    )
  )
)

