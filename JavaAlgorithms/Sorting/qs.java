public class qs {
private static void quicksort(int a[], int i, int f) {
  //cannot do partitions on array which size is less than 1
  if (f <= 1) return; // old: (f - i <= 1)
  //partitioning:
  int m=i + f/2; // m = (i+f) / 2; se f < i m e' errata
  int pivot = a[m];
  int inf = i, sup = i + f - 1; //inf = 0, sup = f - 1;

  while(true) {
    //select elements which are not in the correct set
    while(a[inf] < pivot) inf++;
    while(a[sup] > pivot) sup--;
    if(inf >= sup) break;
    //swap these elements
    int swap = a[inf];
    a[inf] = a[sup];
    a[sup] = swap;
  }

  /** eliminato **
  a[m] = a[sup];
  a[sup] = pivot;
  **/

  quicksort(a, i, sup-i); // quicksort(a, i, sup - 1);
  quicksort(a, sup + 1, i + f - 1 - sup );  // quicksort(a, sup + 1, f);
}

public static void main(String[] m) {
	int[] a = new int[] { 1,2,3,-1,0,0 };
	quicksort(a,0,a.length-1);
	for(int e : a)
		System.out.print(e + " ");
}
}
