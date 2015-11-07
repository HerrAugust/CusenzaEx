; Scrivere una funzione che data una lista di numeri naturali positivi restituisce la sottolista fatta solo dai numeri primi ordinati in senso decrescente.
; Ad esempio, (estrai-primi-ordinati '(6 3 5 8 9 64 45 32 4 77 89)) viene valutata '(89 5 3)

(define estrai-primi-ordinati (lambda (l) (
                                           cond(#t (decrescente (primi l)))
                                           )))

;estrae i primi da una lista
(define primi (lambda (l) (
                           cond((eq? l '()) '())
                               ((isPrimo (car l)) (cons (car l) (primi (cdr l))))
                               (#t (primi (cdr l)))
                           )))

;un numero è primo se divisibile per uno e se stesso
(define isPrimo (lambda (n) (
                             cond((eq? n 2) #f)
                                 ((eq? n 1) #t)
                                 (#t (isPrimo_aux n 2))
                             )))

(define isPrimo_aux (lambda (n div) (
                                     cond((eq? div n) #t)
                                         ((eq? (myModulo n div) 0) #f)
                                         (#t (isPrimo_aux n (+ div 1)))
                                     )))

;n % div
(define myModulo (lambda (n div) (
                              cond((eq? n 0) 0)
                                  ((< n 0) n)
                                  (#t (myModulo (- n div) div))
                              )))

;ordina una lista in ordine decrescente (da più piccolo al più grande)
(define decrescente (lambda (l) (
                                 cond((eq? l '()) '())
                                      (#t (cons (maggiore l) (decrescente (rimuovi l (maggiore l) #f))))
                                 )))

;trova il maggiore di una lista
(define maggiore (lambda (l) (
                              cond(#t (maggiore_aux l -1))
                              )))

(define maggiore_aux (lambda (l maggioreCorrente) (
                                                   cond((eq? l '()) maggioreCorrente)
                                                       ((> (car l) maggioreCorrente) (maggiore_aux (cdr l) (car l)))
                                                       (#t (maggiore_aux (cdr l) maggioreCorrente))
                                                   )))


;rimuove un numero dalla lista
(define rimuovi (lambda (l n trovato) (
                               cond((eq? l '()) '())
                                    ((and (eq? (car l) n) (eq? trovato #f)) (rimuovi (cdr l) n #t))
                                    (#t (cons (car l) (rimuovi (cdr l) n #f)))
                               )))

;prove di esecuzione
(estrai-primi-ordinati '(6 3 5 8 9 64 45 32 4 77 89)) ;output verificato: (list 89 5 3) => ok
(estrai-primi-ordinati '(6 3 5 8 9 64 45 32 4 77 89)) ;output verificato: (list 89 5 5 3) => ok
(estrai-primi-ordinati '(6 2 4 2)) ;output verificato: '() => ok
