; Scrivere una funzione "ripeti" che presa una lista di numeri naturali non negativi ritorna una lista con gli stessi elementi della lista in
; ingresso ma ripetuti un numero di volte pari al loro valore.
; Ad esempio, (ripeti '(6 3 5 1 8)) viene valutata a '(6 6 6 6 6 6 3 3 3 5 5 5 5 5 1 8 8 8 8 8 8 8 8)

; wrong because aux is a list "nil" === '(), hence (cons (cons aux (car lista)) (ripeti_aux lista aux (+ 1 nripetizioni))) cannot be performed!!!
; In fact you are trying, through (cons aux (car lista)), to add a reference to (car lista) as the second field of a cons cell that refers to no memory address.
; So interpreter cannot write the reference into memory.
; (define ripeti(lambda (lista) (
;                                    cond(#t (ripeti_aux lista '() 0))
;                                )))
; 
; (define ripeti_aux(lambda (lista aux nripetizioni) (
;                                        cond((eq? lista nil) nil)
;                                            ((eq? nripetizioni (car lista)) (ripeti_aux (cdr lista) aux 0))
;                                            (#t (cons (cons aux (car lista)) (ripeti_aux lista aux (+ 1 nripetizioni))))
;                                        )))


(define ripeti (lambda (lista) (
                                cond(#t (ripeti_aux lista 0))
                                )))

(define ripeti_aux (lambda (lista nrepet) (
                                           cond((eq? lista '()) '()) ;Important conceptual note: '() equivalent nil, i.e. not referring to memory address!!
                                               ((eq? (car lista) nrepet) (ripeti_aux (cdr lista) 0))
                                               (#t (cons (car lista) (ripeti_aux lista (+ 1 nrepet))))
                                           )))

;Prove
(ripeti '(6 3 5 1 8))
(ripeti '(0 1 2))
(ripeti '(1))
