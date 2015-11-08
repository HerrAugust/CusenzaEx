(*
reverse of a list
:: : 'a * 'a list -> 'a list
@ : 'a list * 'a list -> 'a list
*)

fun reversearray(nil) = nil |
	reversearray(element::list) = reversearray(list)::(element::nil); (* cannot use @ to concat element with a list (see @ types); moreover, it is wrong to write reversearray(list)::[element::nil] because [] : 'a * 'a * ... * 'a -> 'a list and :: : 'a * 'a list -> 'a list. So analyze [element::nil]: :: return 'a list, which is passed to [], and [] returns 'a list list (simply replace "'a" in [] with "'a list", which is the argument) *)

reversearray([1]);
reversearray([1,2,3,4,5,6]);
