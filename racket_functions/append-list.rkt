#lang racket

(define append-list
  (lambda (lst1 lst2) 
    (if (null? lst1)
      lst2
      (cons (first lst1) (append-list (rest lst1) lst2))
    )
  )
)

(provide append-list)
