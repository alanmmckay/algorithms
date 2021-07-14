#lang racket

;; FILE: syntax-procs.rkt
;; AUTHOR: Alan McKay
;; DATE: 04/29/20
;;; --- A set of syntax procedures for the following language : --- ;;;
;;
;; <color> ::= (rgb <byte> <byte> <byte>)
;;           | <varref>
;;           | (<unary-op> <color>)
;;           | (<color> <2color-op> <color>)
;;           | (<color> <1color-op> <number>)
;;           | ( color <var> = <color> in <color> )
;;           | ( do <assignment>* <color> )
;;
;; <unary-op> ::= invert | darker
;; <2color-op> ::= + | - | mix
;; <1color-op> ::= * | shift
;; <assignment> ::= ( <varref> <= <color> )
;;; ----------------------------------------------------------------;;;

(provide color?      varref?
         rgb?        make-rgb        rgb->first          rgb->second       rgb->third          
         unary-op?   make-unary-op   unary-op->operator  unary-op->color     
         2color-op?  make-2color-op  2color-op->operator 2color-op->first  2color-op->second
         1color-op?  make-1color-op  1color-op->operator 1color-op->color  1color-op->factor
         local-var?  make-local-var  local-var->name     local-var->def    local-var->region
         assignment? make-assignment assignment->var     assignment->color
         do?         do->assignments do->color)
         
         
;; ----------------------------------------------------------------;;

(define color?
  (lambda (exp)
      (or (rgb? exp)
      (varref? exp)
      (unary-op? exp) 
      (2color-op? exp) 
      (1color-op? exp)
      (local-var? exp)
      (do? exp)
      )
  )
)

;; ----------------------------------------------------------------;;

(define rgb?
  (lambda (exp)
    (and (list? exp) 
    (eq? (length exp) 4) 
    (eq? (first exp) 'rgb) 
    (byte? (second exp)) 
    (byte? (third exp)) 
    (byte? (fourth exp)))
  )
)

(define make-rgb
  (lambda (byte1 byte2 byte3)
    (if (and (byte? byte1) (byte? byte2) (byte? byte3))
      (list 'rgb byte1 byte2 byte3)
      (error "make-rgb")
    )
  )
)
;; 
(define rgb->first
  (lambda (exp)
    (second exp)
  )
)

(define rgb->second
  (lambda (exp)
    (third exp)
  )
)

(define rgb->third
  (lambda (exp)
    (fourth exp)
  )
)

;; ----------------------------------------------------------------;;

(define unary-op?
  (lambda (exp)
    (and 
    (list? exp)
    (eq? (length exp) 2)
    (or (eq? (first exp) 'invert) (eq? (first exp) 'darker)) 
    (color? (second exp)))
  )
)

(define make-unary-op
  (lambda (operator color)
    (list operator color)
  )
)

(define unary-op->operator
  (lambda (exp)
    (first exp)
  )
)

(define unary-op->color
  (lambda (exp)
    (second exp)
  )
)

;; ----------------------------------------------------------------;;

(define 2color-op?
  (lambda (exp)
    (and (list? exp)
    (eq? (length exp) 3)
    (color? (first exp)) 
    (or (eq? (second exp) '+) (eq? (second exp) '-) (eq? (second exp) 'mix)) 
    (color? (third exp)))
  )
)

(define make-2color-op
  (lambda (color1 operator color2)
    (list color1 operator color2)
  )
)

(define 2color-op->operator
  (lambda (exp)
    (second exp)
  )
)

(define 2color-op->first
  (lambda (exp)
    (first exp)
  )
)

(define 2color-op->second
  (lambda (exp)
    (third exp)
  )
)

;; ----------------------------------------------------------------;;

(define 1color-op?
  (lambda (exp)
    (and 
    (list? exp)
    (eq? (length exp) 3)
    (color? (first exp)) 
    (or (eq? (second exp) '*) (eq? (second exp) 'shift)) 
    (number? (third exp)))
  )
)

(define make-1color-op
  (lambda (color operator number)
    (list color operator number)
  )
)

(define 1color-op->operator
  (lambda (exp)
    (second exp)
  )
)

(define 1color-op->color
  (lambda (exp)
    (first exp)
  )
)

(define 1color-op->factor
  (lambda (exp)
    (third exp)
  )
)

;; ----------------------------------------------------------------;;

(define keywords '(rgb color = in))

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

(define local-var?
  (lambda (exp)
    (and
      (list? exp)
      (eq? 6 (length exp))
      (eq? 'color (first exp))
      (symbol? (second exp))
      (not (element-of-list? (second exp) keywords))
      (eq? '= (third exp))
      (color? (fourth exp))
      (eq? 'in (fifth exp))
      (color? (sixth exp))
    )
  )
)

(define local-var->name
  (lambda (exp)
    (second exp)
  )
)

(define local-var->def
  (lambda (exp)
    (fourth exp)
  )
)

(define local-var->region
  (lambda (exp)
    (sixth exp)
  )
)

(define varref?
  (lambda (exp)
    (and
      (symbol? exp)
      (not (element-of-list? exp keywords))
    )
  )
)

(define make-local-var
  (lambda (var definition region)
    (list 'color var '= definition 'in region)
  )
)

;; ----------------------------------------------------------------;;

(define assignment?
  (lambda (exp)
    (and
      (list? exp)
      (eq? 3 (length exp))
      (varref? (first exp))
      (eq? '<= (second exp))
      (color? (third exp))
    )
  )
)

(define assignment->var
  (lambda (exp)
    (first exp)
  )
)

(define assignment->color
  (lambda (exp)
    (third exp)
  )
)

(define make-assignment
  (lambda (var color)
    (list var '<= color)
  )
)

;; ----------------------------------------------------------------;;

(define do?
  (lambda (exp)
    (and
      (list? exp)
      (eq? 'do (first exp))
      (color? (last exp))
    )
  )
)

(define do->assignments
  (lambda (exp)
    (if (eq? 1 (rest exp))
      '()
      (do->assignments-helper (rest exp))
    )
  )
)

(define do->assignments-helper
  (lambda (exp)
    (if (= 1 (length exp))
      '()
      (cons (first exp) (do->assignments-helper (rest exp)))
    )
  )
)

(define do->color
  (lambda (exp)
    (last exp)
  )
)

