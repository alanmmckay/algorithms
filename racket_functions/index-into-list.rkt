#lang racket

;;a function which takes a list as the first parameter
;;and indexes into it using the second parameter
;;The first element of a list is index 0


(define index-into-list
  (lambda (list index)
    (cond ;switch 1
      ( ;case 1a
      (> (length list) index)
        (cond ;switch 2 
          ((= 0 index) (first list)) ;case 2a
          (else (index-into-list (rest list) (- index 1))) ;case 2b
        ) ;end switch 2
      ) ;end case 1a
    (else #f) ;case 1b
    ) ;end switch 1
  )
)

(provide index-into-list)
