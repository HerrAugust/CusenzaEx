; Scrivere una funzione "conta-pari-e-dispari" che presa una lista di numeri naturali
; non negativi ritorna una lista di due elementi che rappresentano rispettivamente
; il numeri di numeri pari e il numero di dispari nella lista in ingresso.
; Ad esempio, (conta-pari-e-dispari '(3 5 6 7 9 21 44 657 9)) viene valutata a '(2 7).

;NB: cons: list*list -> list

;SBAGLIATO: vedi il tipo di cons
;(define conta-pari-e-dispari(lambda (list) (
;                                        cond( #t (cons (conta-pari list 0) (conta-dispari list 0)) )
;                                        )))
;ESEMPIO PIÙ SEMPLICE (vedi "per capire"):
;(cons 2 7) non funziona: 2 non è lista
;VS
;(cons (cons 2 '()) (cons 7 '()))

(define conta-pari-e-dispari(lambda (list) (
                                        cond( #t (cons (cons (conta-pari list 0) '()) (cons (conta-dispari list 0) '())) )
                                        ))) ;NOTA: (cons (conta-pari list 0) '()) permette di creare una lista (vedi "percapire.rkt")

;conta i numeri pari della lista
(define conta-pari (lambda (lista npari) (
                                    cond( (eq? lista '()) npari )
                                        ( (is-pari (car lista)) (conta-pari (cdr lista) (+ npari 1)) )
                                        ( #t (conta-pari (cdr lista) npari) )
                                    )))

;conta i numeri dispari della lista
(define conta-dispari (lambda (lista ndispari) (
                                    cond( (eq? lista '()) ndispari )
                                        ( (is-pari (car lista)) (conta-dispari (cdr lista) ndispari) )
                                        ( #t (conta-dispari (cdr lista) (+ ndispari 1))  )
                                    )))

;n è pari?
(define is-pari (lambda (n) (
                             cond( (eq? n 0) #t )
                                 ( (eq? n 1) #f )
                                 ( #t (is-pari (- n 2)) )
                             )))

;Prove
(conta-pari-e-dispari '())
(conta-pari-e-dispari '(0))
(conta-pari-e-dispari '(1))
(conta-pari-e-dispari '(3 5 6 7 9 21 44 657 9))
