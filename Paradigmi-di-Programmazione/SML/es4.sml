(*
Applicare f a tutti gli elementi di un albero
:: : 'a * 'a list -> 'a list
@ : 'a list * 'a list -> 'a list
*)

datatype tree = foglia of int |
                left of int * tree |
                right of int * tree |
                nodo of int * tree * tree;
                
fun f(elem) = elem+1;

fun ftotree(f,nil) = nil |
    ftotree(f,foglia(x)) = f(x) |
    ftotree(f,left(x,tree)) = 
    
val alb1a = node(4,node(3,leaf(1),leaf(2)),node(5,leaf(6),leaf(7)));
val alb1b = left(4,node(3,leaf(1),leaf(2)));
val alb1c = right(4,node(5,leaf(6),leaf(7)));
val alb1d = left(4,right(3,leaf(2)));
val alb1e = right(4,left(5,leaf(6)));
val alb1f = right(4,leaf(5));
val alb1g = left(4,leaf(3));
val alb1h = leaf(4);
