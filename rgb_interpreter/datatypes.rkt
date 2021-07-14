#lang racket

(require "utilities.rkt")

(provide make-bindings bind var-exists? look-up cell cell-value cell-set!)

(define make-bindings
  (lambda ()
    '()
  )
)

(define bind
  (lambda (name value bindings)
    (append (list (cons name value)) bindings)
      
  )
)

(define var-exists?
  (lambda (name bindings)
    (if (null? bindings)
      #f
      (if (eq? name (car (first bindings)))
        #t
        (var-exists? name (rest bindings))
      )
    )
  )
)

(define look-up
  (lambda (name bindings)
    (if (null? bindings)
      (error "environment: undefined variable --" name)
      (if (eq? name (car (first bindings)))
        (cdr (first bindings))
        (look-up name (rest bindings))
      )
    )
  )
)

(define cell
  (lambda (val)
    (list
      (lambda ()
        val
      )
      (lambda (new)
        (set! val new)
      )
    )
  )
)

(define cell-value 
  (lambda (cell)
    ((first cell))
  )
)

(define cell-set!
  (lambda (inputcell newval)
    ((second inputcell) newval)
    newval
  )
)
