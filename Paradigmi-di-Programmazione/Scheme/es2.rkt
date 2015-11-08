;; The first three lines of this file were inserted by DrRacket. They record metadata
;; about the language level of this file in a form that our tools can easily process.
#reader(lib "htdp-beginner-abbr-reader.ss" "lang")((modname es2) (read-case-sensitive #t) (teachpacks ()) (htdp-settings #(#t constructor repeating-decimal #f #t none #f () #f)))
;scrivere una funzione che data una lista di numeri natuali positivi restituisce una lista
;composta dai numeri della lista in input dove i pari e i dispari sono disposti in modo alternato.
;per esempio, (alterna '(6 3 5 1 8 7 2 4)) restituisce '(6 3 8 5 2 1 4 7)

(define alterna (lambda (l) (
                             cond(#t (alterna_aux l #f))
                             )))

(define alterna_aux (lambda (l precedenteISpari) (
                                 cond((eq? l '()) '())
                                     ((eq? precedenteISpari #f) (cons (trovaPari l) (alterna_aux (rimuovi l (trovaPari l)) #t)))
                                     (#t (cons (trovaDispari l) (alterna_aux (rimuovi l (trovaDispari l)) #f)))
                                 )))

;trova il primo numero pari della lista l
(define trovaPari (lambda (l) (
                               cond((eq? l '()) '())
                                ((eq? (isPari (car l)) #t) (car l))
                                   (#t (trovaPari (cdr l)))
                               )))

;determina se n è pari
(define isPari (lambda (n) (
                            cond((eq? n 0) #t)
                                ((eq? n 1) #f)
                                (#t (isPari (- n 2)))
                            )))

;rimuove un elemento dalla lista
(define rimuovi (lambda (l n) (
                               cond((eq? l '()) '())
                                   ((eq? (car l) n) (cdr l))
                                   (#t (cons (car l) (rimuovi (cdr l) n)))
                               )))

;trova il primo dispari della lista l
(define trovaDispari (lambda (l) (
                                  cond((eq? l '()) '())
                                   ((eq? (isPari (car l)) #f) (car l))
                                      (#t (trovaDispari (cdr l)))
                                  )))

;Prove
(alterna '(3)) ;output verificato: 3 => ok
(alterna '(6 3 5 1 8 7 2 4)) ;output verificato: (list 6 3 8 5 2 1 4 7) => ok
