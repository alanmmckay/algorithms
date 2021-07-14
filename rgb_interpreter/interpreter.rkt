#lang racket

;; FILE: interpreter.rkt
;; AUTHOR: Alan McKay
;; Date: 04/29/20
;;; --- A preprocessor and evaluator for the following language : --- ;;;
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
;;; ----------------------------------------------------------------- ;;;
;; Going to explicitly define the previously implicit definition of number:
;; <number> ::= <sign><natural-number>
;; <sign> ::= - | e

(require "syntax-procs.rkt")
(require "utilities.rkt")
(require "datatypes.rkt")
(provide preprocess eval-exp run-huey)

;; --- The Preprocessor breaks the following expressions down their core forms:
;; --- --- (darker <color>) -> (<color> * 0.5)
;; --- --- (<color> mix <color>) -> ((<color> * 0.5) + (<color> * 0.5))
;; --- --- (<color> shift <number>) -> 
;; --- --- --- (<color> <sign> 
;; --- --- --- --- (rgb <natural-number> <natural-number> <natural-number>))

;; Made the design choice to not define the mix operation in terms of the...
;; ... darker operation as the behavior of mix may be later changed.

(define preprocess
  (lambda (sugared-exp)
    (cond
      ((varref? sugared-exp) sugared-exp)
      ((rgb? sugared-exp) sugared-exp)
      (
        (unary-op? sugared-exp) 
        (cond
          ( ;; darker operation:
            (eq? 'darker (unary-op->operator sugared-exp))
            (make-1color-op (preprocess (unary-op->color sugared-exp)) '* 0.5)
          )
          (else
            (list 
              (unary-op->operator sugared-exp) 
              (preprocess (unary-op->color sugared-exp))
            )
          )
        )
      )
      (
        (2color-op? sugared-exp) 
        (cond 
          ( ;; mix operation:
            (eq? 'mix (2color-op->operator sugared-exp))
            (preprocess 
              (make-2color-op (make-1color-op (2color-op->first sugared-exp) '* 0.5)
                              '+
                              (make-1color-op (2color-op->second sugared-exp) '* 0.5)
              )
            )
          )
          (else  
            (list 
              (preprocess (2color-op->first sugared-exp)) 
              (2color-op->operator sugared-exp) 
              (preprocess (2color-op->second sugared-exp))
            )
          )
        )
      )
      (
        (1color-op? sugared-exp)
        (cond
          ( ;; shift operation:
            (eq? 'shift (1color-op->operator sugared-exp))
            (make-2color-op 
              (preprocess (1color-op->color sugared-exp)) 
              (get-shift-operation (1color-op->factor sugared-exp)) 
              (make-rgb 
                (inexact->exact (floor (abs (1color-op->factor sugared-exp)))) 
                (inexact->exact (floor (abs (1color-op->factor sugared-exp))))
                (inexact->exact (floor (abs (1color-op->factor sugared-exp)))) ;; need a function here
              )
            )
          )
          (else
            (list 
              (preprocess (1color-op->color sugared-exp))
              (1color-op->operator sugared-exp) 
              (1color-op->factor sugared-exp)
            )
          )
        )
      )
      (
        (local-var? sugared-exp)
        (list 'color (local-var->name sugared-exp) '= (preprocess (local-var->def sugared-exp)) 'in (preprocess (local-var->region sugared-exp)))
      )
      (
        (assignment? sugared-exp)
        (list (preprocess (assignment->var sugared-exp)) '<= (preprocess (assignment->color sugared-exp)))
      )
      (
        (do? sugared-exp)
        (cons 'do
          (if (eq? 0 (length (do->assignments sugared-exp)))
            (list (preprocess (do->color sugared-exp)))
            (append (map preprocess (do->assignments sugared-exp)) (list (preprocess (do->color sugared-exp))))
          )
        )
      )
      (else (error "illegal expression --" sugared-exp))
    )
  )
)

;;; ----------------------------------------------------------------- ;;;

;; -- The evaluator currently evaluates +, -, *, and invert operations:
;; -- -- (Should always produce an rgb-expression.)

(define variable-table 
  (bind 'black (cell (list 'rgb 0 0 0)) (bind 'white (cell (list 'rgb 255 255 255)) (make-bindings))))

(define eval-exp
  (lambda (exp)
    (if (color? exp)
      (eval-exp-helper (preprocess exp) variable-table)
      (error "illegal expression --" exp)
    )
  )
)

(define eval-exp-helper
  (lambda (preprocessed-exp env)
    (cond
      (
        (2color-op? preprocessed-exp)
        (cond
          ( ;; + operation:
            (eq? '+ (2color-op->operator preprocessed-exp))
            (append '(rgb) 
                  (map byte-limiter (map + (rgb->bytes (eval-exp-helper (2color-op->first preprocessed-exp) env)) (rgb->bytes (eval-exp-helper (2color-op->second preprocessed-exp) env))))
            )
          )
          ( ;; - operation:
            (eq? '- (2color-op->operator preprocessed-exp))
            (append '(rgb) 
                  (map byte-limiter (map - (rgb->bytes (eval-exp-helper (2color-op->first preprocessed-exp) env)) (rgb->bytes (eval-exp-helper (2color-op->second preprocessed-exp) env))))
            )
          )
        )
      )
      (
        (unary-op? preprocessed-exp)
        (cond
          ( ;; invert operation:
            (eq? 'invert (unary-op->operator preprocessed-exp))
            (append '(rgb) (map abs (map - (rest (eval-exp-helper (unary-op->color preprocessed-exp) env)) '(255 255 255))))
          )
        )
      )
      (
        (1color-op? preprocessed-exp)
        (cond
          ( ;; * operation:
            (eq? '* (1color-op->operator preprocessed-exp))
            (append '(rgb) (map (multiplier (1color-op->factor preprocessed-exp)) (rest (eval-exp-helper (1color-op->color preprocessed-exp) env))))
          )
        )
      )
      ((rgb? preprocessed-exp) preprocessed-exp)
      (
        (varref? preprocessed-exp)
        (if (var-exists? preprocessed-exp env)
          (eval-exp-helper (cell-value (look-up preprocessed-exp env)) env)
          (error "undefined variable --" preprocessed-exp)
        )
      )
      (
        (local-var? preprocessed-exp)
        (eval-exp-helper (local-var->region preprocessed-exp) 
            (bind (local-var->name preprocessed-exp) (cell (eval-exp-helper (local-var->def preprocessed-exp) env)) env)
        )
      )
      (else (error "illegal expression --" preprocessed-exp))
    )
  )
)

;;; ----------------------------------------------------------------- ;;;

;; -- Read Evaluate Print Loop mechanism. Call run-huey to input RGB
;; --- expressions through stdin.

(define run-huey
  (lambda ()
    (display "--- huey interpreter ---")
    (newline)
    (display "Implementation by Alan McKay")
    (newline)
    (display "--- Work in Progress ---")
    (newline)
    (run-huey-helper)
  )
)

(define run-huey-helper
  (lambda ()
    (display "--> Input RGB expression: ")
    (let ((color (eval-exp (read))))
    (display "R:")
    (write (rgb->first color))
    (display " G:")
    (write (rgb->second color))
    (display " B:")
    (write (rgb->third color))
    )
    (newline)
    (run-huey-helper)
  )
)
;;; ----------------------------------------------------------------- ;;;

                           
