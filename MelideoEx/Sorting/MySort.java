/*
 * My implementations of sorting algorythms. Increasing order!
 */

public class MySorts {
	
	public static void main(String[] a) {
		new MySorts().run();
	}

	public void run() {
		int[] sequence = new int[] { 9, -1, 7, 5, 4, 10, 2 };
		int []copy = new int[sequence.length];
		printarray(sequence);

//selection sort
		System.arraycopy(sequence, 0, copy, 0, sequence.length);
		selectionSort(copy); //SelectionSort
		System.out.print("\nOrdered SS: ");
		printarray(copy);

//inserction sort
		System.arraycopy(sequence, 0, copy, 0, sequence.length);
		inserctionsort_fromright(copy); //InserctionSort
		System.out.print("\nOrdered IS: ");
		printarray(copy);

//merge sort
		System.arraycopy(sequence, 0, copy, 0, sequence.length);
		inserctionsort_fromright(copy); //MergeSort
		System.out.print("\nOrdered MS: ");
		printarray(copy);

//quick sort
		System.arraycopy(sequence, 0, copy, 0, sequence.length);
		quicksort(copy); //QuickSort
		System.out.print("\nOrdered QS: ");
		printarray(copy);

/*
//merge sort (iterative)
		System.arraycopy(sequence, 0, copy, 0, sequence.length);
		mergesortIT(copy); //MergeSort (Iterative)
		System.out.print("\nOrdered MSit: ");
		printarray(copy);*/	

//heap sort
		System.arraycopy(sequence, 0, copy, 0, sequence.length);
		heapsort(copy); //HeapSort
		System.out.print("\nOrdered HS: ");
		printarray(copy);
	}

//SELECTION SORT
	/**
	 * In the non-ordered sequence I SELECT the MINOR ELEMENT and than put it at beginning of the ordered sequence
	 */
	public void selectionSort(int[] array) {
		for(int o = 0; o < array.length; o++) //left-limit of ordered sequence of array
		{
			int posMin = o;
			//Find minimum in non-ordered section
			for(int no = o; no < array.length; no++)
				if(array[posMin] > array[no])
					posMin = no;

			// Put minimum of non-ordered sequence at the top of ordered-sequence. Have to swap minimum
			int temp = array[o];
			array[o] = array[posMin];
			array[posMin] = temp;
		}
	}

//INSERCTION SORT
	/**
	 * In the non-ordered sequence I take the first element and, scrolling the ordered sequence FROM RIGHT to left, I find the right position
	 * of the element and INSERCT it there.
	 */
	public void inserctionsort_fromright(int [] array) {
		for(int o = 0; o < array.length; o++) //the ordered section begins from one to save a vacuum cycle.
			//find the right position scrolling ordered section from right to left
			for(int no = o; no > 0; no--)
				if (array[no] < array[no-1]) // 3 2 => swap
				{
					int temp = array[no];
					array[no] = array[no-1];
					array[no-1] = temp;
				}
	}

//MERGE SORT
	/**
	 * I recursevely divide array in two parts, possibly both of the same size. When I arrive to an array of size 1, I know that is ordered by
	 * definition. So I can go back to the caller function and now I have two divided ordered array and I have to orderly merge them.
	 */
	public void mergesort(int [] a) {
		divide(a, 0, a.length);
	}

	private void divide(int[] a, int i, int f) {
		if(f-i == 1)
			return;

		int m = (i+f) / 2;
		divide(a, i, m);
		divide(a, m, f);
		merge(a, i, m, f);
	}

	/*
	 * While one of the two parts of the array is not ended I select the minimum between the current element of the first part and the one of second part.
	 * I put the minimum in the current position of the whole array.
	 * Because this algorithm works in loco I do not have to copy the remaining part of the array in the original one.
	 */
	public void merge(int[] a, int i, int f1, int f2) {
		int c1 = i, c2 = f1; //cursors for both parts
		int gc = 0; //general cursor, the one of the whole array
		int swap = 0, min = 0;
		while(c1 != f1 && c2 != f2) {
			if(a[c1] < a[c2]) {
				min = c1;
				c1++;
			}
			else {
				min = c2;
				c2++;
			}
			
			swap = a[min];
			a[min] = a[gc];
			a[gc] = swap;
			gc++;
		}
	}

//QUICK SORT
	/*
	 * I make two partitions of the array: the first one contains elements less than the pivot (an element of the array); the second one contains elements
	 * more than the pivot. I recursively repeat this action on both the partitions until I can, ie until partition has size more than 1.
	 */
	public void quicksort(int a[]) {
		quicksort(a, 0, a.length);
	}

	private void quicksort(int a[], int i, int f) {
  //cannot do partitions on array which size is less than 1
  if (f <= 1) return; // old: (f - i <= 1)
  //partitioning:
  int m=0;
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

//MERGE SORT (ITERATIVE)
	/*
	 * From a computational point of view, recursive methods should be avoided because of their space use and because of the time needed to
	 * handle implicit activation stacks created for methods by programming languages.
	 * To implement Merge Sort as interative method you start considering the recursion tree bottom-up: at the beginning you have an array of size
	 * 1 which should be merged with another one of the same size; going on you have to merge two arrays of size 2; then of size 4; etc.
	 */
   public static void  mergesortIT(int[] x)
   { 
		int n=x.length;
		int[] aux = new int[n];
		System.arraycopy(x, 0, aux, 0, n);

  		int i,dim;
		for (dim=1; dim<n; dim=dim+dim)
           for (i=0; i<n-dim; i=i+dim+dim)
                merge(x,aux, i, i+dim-1, Math.min(i+dim+dim-1, n-1)); 
	}
	 
	/*
	 * Merge a[] from position l to m and from position m to r, using c as auxilium
	 */
   private static void merge(int[] a, int[] c, int l, int m, int r){
   		int c1 = l;
   		int c2 = m;
   		int cc = 0;
   		while(c1 != m && c2 != r) {
   			if(a[c1] < a[c2])
   				c[cc++] = a[c1++];
   			else
   				c[cc++] = a[c2++];
   		}

   		int beg = c2, end = r;
   		if(c1 != m)
   		{
   			beg = c1;
   			end = m;
   		}
   		while(beg != end)
   			c[cc++] = a[beg++];

   		cc = 0;
   		while(l != r)
   			a[l++] = c[cc++];
   }

//HEAP SORT
   /*
    * Build a max-heap through heapfy(), then I take root and put it at the last position of the heap. Decrease the size of the heap by 1 and then fixheap().
    * I repeat this action until the heap has dimension more than 1 (the last element is already ordered).
    * Attention: this function requires does not order the position 0 because it is discarted (this choice make the algorithm easier)!
    */
   public static void heapsort(int[] a) {
		int heapsize = a.length - 1;
		int swap;
		//make max-heap
		heapfy(a);
		//put root as the last element of the heap, decrease heap dimension, fixheap() and then repeat
		while(heapsize > 0) {
			swap = a[0];
			a[0] = a[heapsize];
			a[heapsize] = swap;
			heapsize--;
			//only root has changed
			fixheap(a, 0, heapsize);
		}
	}
	
	/*
	 * Build a max-heap from an array in loco.
	 * Starting from the bottom of the heap, create a left and a right heap. Then go on the superior level of the heap and do the same, until root is reached.
	 */
	public static void heapfy(int[] a) {
		int swap, leftchild, curnode, rightchild;
		
		for( curnode = (a.length-2) / 2; curnode >= 0; curnode-- ) { //1 4 5 -1 2 0
			leftchild = curnode * 2 + 1;
			rightchild = leftchild + 1;
			if(a[curnode] < a[leftchild])
			{
				swap = a[curnode];
				a[curnode] = a[leftchild];
				a[leftchild] = swap;
			}
			
			if(a[curnode] < a[leftchild+1]) { //rightchild
				swap = a[curnode];
				a[curnode] = a[rightchild];
				a[rightchild] = swap;
			}
		}
	}
	
	/*
	 * Fix the structure of a max-heap. In particular it sets at the correct place the element at position pos of the array. It works in loco.
	 */
	public static void fixheap(int[] a, int pos, int heapsize) {
		//if leftchild > a[pos] => swap and continue in the left subheap; if rightchild > a[pos] => swap and continue in the right subheap.
		//This is because a[] comes from a heapfy()
		int leftchild = pos * 2+1, swap;
		
		if(leftchild >= heapsize) return; //exit condition
		
		if( leftchild < a.length && a[leftchild] > a[pos] ) { //left child
			swap = a[leftchild];
			a[leftchild] = a[pos];
			a[pos] = swap;
		
			fixheap(a, leftchild, heapsize);
		}
		if( leftchild + 1 < a.length && a[leftchild+1] > a[pos] ) { //right child
			swap = a[leftchild+1];
			a[leftchild+1] = a[pos];
			a[pos] = swap;
			fixheap(a, leftchild+1, heapsize);
		}
	}
	
	public void printarray(int [] sequence) {
		for (int k : sequence)
			System.out.print(k + " ");
	}

}
