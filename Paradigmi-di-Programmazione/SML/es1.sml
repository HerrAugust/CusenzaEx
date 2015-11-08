(*
Verify if a list contains a certain object
Please feed to MoscowML command line. Tested.
*)

fun listcontains(nil, what) = false |
	listcontains(x::list, what) = if x = what then true else listcontains(list, what); //:: : 'a * 'a list -> 'a list

array = [1,2,3,3];
listcontains(array, 2);
listcontains(array, 0);
