(*
Applicare f a tutti gli elementi di una lista
:: : 'a * 'a list -> 'a list
@ : 'a list * 'a list -> 'a list
*)

fun applicafallalista(f, nil) = nil; |
	applicafallalista(f, elem::lista) = f(elem)::applicafallalista(f, lista);

fun f(x) = x+1;

applicafallalista(f, [1,2,3]);