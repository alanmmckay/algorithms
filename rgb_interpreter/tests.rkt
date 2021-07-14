#lang racket

;; FILE: tests.rkt
;; AUTHOER: Alan McKay
;; Date: 04/15/20
;;; --- Unit Tests for Huey RGB language --- ;;;

(require rackunit)

(require "syntax-procs.rkt")
(require "interpreter.rkt")

;;; --- syntax-proc testing: --- ;;;

;; -- Constructors:

; - rgb-expressions:
(define rgbLow (make-rgb 0 0 0))
(define rgbMid (make-rgb 127 127 127))
(define rgbHigh (make-rgb 255 255 255))
(define rgbVaried (make-rgb 0 127 255))

(check-equal? rgbLow '(rgb 0 0 0))
(check-equal? rgbMid '(rgb 127 127 127))
(check-equal? rgbHigh '(rgb 255 255 255))
(check-equal? rgbVaried '(rgb 0 127 255))

; - unary-op-expressions
(define inverted-op (make-unary-op 'invert rgbVaried))
(define darker-op (make-unary-op 'darker rgbVaried))

(check-equal? inverted-op (list 'invert rgbVaried))
(check-equal? darker-op (list 'darker rgbVaried))

; - 2-color-op-expressions:

(define +-op1 (make-2color-op rgbHigh '+ rgbLow))
(define +-op2 (make-2color-op inverted-op '+ darker-op))

(define --op1 (make-2color-op rgbHigh '- rgbLow))
(define --op2 (make-2color-op inverted-op '- darker-op))

(define mix-op1 (make-2color-op rgbHigh 'mix rgbLow))
(define mix-op2 (make-2color-op inverted-op 'mix darker-op))

(check-equal? +-op1 (list rgbHigh '+ rgbLow))
(check-equal? +-op2 (list inverted-op '+ darker-op))

(check-equal? --op1 (list rgbHigh '- rgbLow))
(check-equal? --op2 (list inverted-op '- darker-op))

(check-equal? mix-op1 (list rgbHigh 'mix rgbLow))
(check-equal? mix-op2 (list inverted-op 'mix darker-op))

; - 1-color-op-expressions:

(define *-op1 (make-1color-op +-op1 '* 5))
(define *-op2 (make-1color-op +-op2 '* 5000))
(define shift-op1 (make-1color-op --op1 'shift .5))
(define shift-op2 (make-1color-op --op2 'shift .0005))

(check-equal? *-op1 (list +-op1 '* 5))
(check-equal? *-op2 (list +-op2 '* 5000))
(check-equal? shift-op1 (list --op1 'shift .5))
(check-equal? shift-op2 (list --op2 'shift .0005))

;; *** NOTE: may need to add checks in constructors to ensure they are recieving a color ;;

;; -- color? predicate:

; - True cases:
(check-equal? (color? rgbLow) #t)
(check-equal? (color? rgbMid) #t)
(check-equal? (color? rgbHigh) #t)
(check-equal? (color? rgbVaried) #t)

(check-equal? (color? inverted-op) #t)
(check-equal? (color? darker-op) #t)

(check-equal? (color? +-op1) #t)
(check-equal? (color? +-op2) #t)
(check-equal? (color? --op1) #t)
(check-equal? (color? --op2) #t)
(check-equal? (color? mix-op1) #t)
(check-equal? (color? mix-op2) #t)

(check-equal? (color? *-op1) #t)
(check-equal? (color? *-op2) #t)
(check-equal? (color? shift-op1) #t)
(check-equal? (color? shift-op2) #t)

; - False cases:
;; (check-equal? (color? 'expression) #f) ;; now evaluates to #t as it is a varref
(check-equal? (color? color?) #f)
(check-equal? (color? 255) #f)

;; -- Type checking:

; - rgb: #t
(check-equal? (rgb? rgbLow) #t)
(check-equal? (rgb? rgbMid) #t)
(check-equal? (rgb? rgbHigh) #t)

; -rgb: #f
(check-equal? (rgb? 'expression) #f) ;symbol
(check-equal? (rgb? rgb?) #f) ;function
(check-equal? (rgb? 255) #f) ;byte/number

(check-equal? (rgb? inverted-op) #f) ;unary
(check-equal? (rgb? +-op1) #f) ;2color
(check-equal? (rgb? *-op1) #f) ;1color

; - unary: #t
(check-equal? (unary-op? inverted-op) #t)
(check-equal? (unary-op? darker-op) #t)

; - unary: #f
(check-equal? (unary-op? 'expession) #f)
(check-equal? (unary-op? unary-op?) #f)
(check-equal? (unary-op? 255) #f)

(check-equal? (unary-op? rgbVaried) #f)
(check-equal? (unary-op? +-op1) #f)
(check-equal? (unary-op? *-op2) #f)

; - 2color: #t
(check-equal? (2color-op? +-op1) #t)
(check-equal? (2color-op? +-op2) #t)
(check-equal? (2color-op? --op1) #t)
(check-equal? (2color-op? --op2) #t)
(check-equal? (2color-op? mix-op1) #t)
(check-equal? (2color-op? mix-op2) #t)

; - 2color: #f
(check-equal? (2color-op? 'expression) #f)
(check-equal? (2color-op? 2color-op?) #f)
(check-equal? (2color-op? 255) #f)

(check-equal? (2color-op? rgbVaried) #f)
(check-equal? (2color-op? inverted-op) #f)
(check-equal? (2color-op? *-op1) #f)

; - 1color: #t
(check-equal? (1color-op? *-op1) #t)
(check-equal? (1color-op? *-op2) #t)
(check-equal? (1color-op? shift-op1) #t)
(check-equal? (1color-op? shift-op1) #t)

; - 1color: #f
(check-equal? (1color-op? 'expression) #f)
(check-equal? (1color-op? 1color-op?) #f)
(check-equal? (1color-op? 255) #f)

(check-equal? (1color-op? rgbVaried) #f)
(check-equal? (1color-op? inverted-op) #f)
(check-equal? (1color-op? +-op1) #f)

;; -- accessors:

; - rgb:
(check-equal? (rgb->first rgbLow) 0)
(check-equal? (rgb->first rgbMid) 127)
(check-equal? (rgb->first rgbHigh) 255)
(check-equal? (rgb->first rgbLow) 0)
(check-equal? (rgb->first rgbMid) 127)
(check-equal? (rgb->first rgbHigh) 255)

; - unary: 
(check-equal? (unary-op->operator inverted-op) 'invert)
(check-equal? (unary-op->color inverted-op) rgbVaried)

; - 2colored:
(check-equal? (2color-op->first +-op1) rgbHigh)
(check-equal? (2color-op->first --op2) inverted-op)
(check-equal? (2color-op->first mix-op1) rgbHigh)

(check-equal? (2color-op->second +-op1) rgbLow)
(check-equal? (2color-op->second --op2) darker-op)
(check-equal? (2color-op->second mix-op1) rgbLow)

(check-equal? (2color-op->operator +-op1) '+)
(check-equal? (2color-op->operator --op1) '-)
(check-equal? (2color-op->operator mix-op1) 'mix)

; - 1colored:
(check-equal? (1color-op->operator *-op1) '*)
(check-equal? (1color-op->operator shift-op1) 'shift)

(check-equal? (1color-op->color *-op2) +-op2)
(check-equal? (1color-op->color shift-op2) --op2)

(check-equal? (1color-op->factor *-op1) 5)
(check-equal? (1color-op->factor shift-op1) .5)

;; Todo: Expand tests for varref and local-var syntax-procs
;;; --- END SYNTAX PROC TESTS --- ;;;


;;; --- Preprocessor Tests: --- ;;;
;;; -- Need more of these -- ;;;

;; -- Provided by Dr. Wallingford:
(check-equal? (preprocess '(invert (rgb 150 99 42))) '(invert (rgb 150 99 42)))
(check-equal? (preprocess '(darker (rgb 150 99 42))) '((rgb 150 99 42) * 0.5))
(check-equal? (preprocess '((rgb 4 4 4) + ((rgb 150 99 42) mix (rgb 50 108 21))))
              '((rgb 4 4 4) + (((rgb 150 99 42) * 0.5) + ((rgb 50 108 21) * 0.5))))
; - New: HW11
(check-equal? (preprocess 'white) 'white)
(check-equal? (preprocess '((rgb 255 0 255) mix (rgb 0 255 0))) '(((rgb 255 0 255) * 0.5) + ((rgb 0 255 0) * 0.5)))
(check-equal? 
  (preprocess '(color purple = ((rgb 255 0 0) mix (rgb 0 0 255)) in (darker purple)))       '(color purple = (((rgb 255 0 0) * 0.5) + ((rgb 0 0 255) * 0.5))in (purple * 0.5))
)


;; -- rgb:
(check-equal? (preprocess rgbHigh) '(rgb 255 255 255)) ;pretty straight forward...

;; -- unary:

; - flat:
(check-equal? (preprocess inverted-op) (list 'invert rgbVaried))
(check-equal? (preprocess darker-op) (list rgbVaried '* 0.5))

; - nested:
(check-equal? (preprocess (list 'invert darker-op)) (list 'invert (list rgbVaried '* 0.5)))
(check-equal? (preprocess (list 'darker inverted-op)) (list inverted-op '* 0.5))

;; -- 2color:
(check-equal? (preprocess +-op1) +-op1)
(check-equal? (preprocess --op2) (list inverted-op '- (preprocess darker-op)))

;; -- 1color:
(check-equal? (preprocess *-op1) *-op1)

(define shift-op3 (make-1color-op rgbVaried 'shift 5))
(define shift-op4 (make-1color-op rgbVaried 'shift -5))
(check-equal? (preprocess shift-op3) (list rgbVaried '+ '(rgb 5 5 5)))
(check-equal? (preprocess shift-op4) (list rgbVaried '- '(rgb 5 5 5)))
(define +-op3 (make-2color-op rgbVaried '+ rgbVaried))
(define shift-op5 (make-1color-op +-op3 'shift 10))
(check-equal? (preprocess shift-op5) (list (preprocess +-op3) '+ (make-rgb 10 10 10)))

;;; --- Evaluation Tests --- ;;;
;; -- Need more of these -- ;;

;; -- Provided by Dr. Wallingford:
(check-equal? (eval-exp '(invert (rgb 150 99 42))) '(rgb 105 156 213))
(check-equal? (eval-exp '((rgb 150 99 42) + (rgb 50 18 241))) '(rgb 200 117 255))
(check-equal? (eval-exp '((rgb 255 0 255) mix ((rgb 0 255 0) + (rgb 4 4 4)))) '(rgb 129 127 129))
; - New: hw11
(check-equal? (eval-exp 'white) '(rgb 255 255 255))
(check-equal? (eval-exp '((rgb 255 0 255) mix (rgb 0 255 0))) '(rgb 127 127 127))
(check-equal? (eval-exp '(color pink = (white mix (rgb 255 0 0)) in (darker pink))) 
              '(rgb 127 63 63))
