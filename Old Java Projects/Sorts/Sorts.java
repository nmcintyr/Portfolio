// Name: Nick McIntyre-Wyma   Class: CS122
// Program: This program was made to sort an array of strings using two types of sorts,
//and then print out the results and which one was faster.
import java.util.*;

public class Sorts {

 public static Scanner in = new Scanner (System.in);

 public static void main (String[] args)
 {
     int n = 0, counter = 0;
     int counterr = 0;
     System.out.print ("Enter how many strings: ");
     n = in.nextInt();
     in.nextLine();
     String[] A = new String[n];
     String[] B = new String[n];
     for (int i=0; i<A.length; i++)
     {
	  System.out.print ("Enter a string: ");
	  A[i] = in.nextLine();					//entering amounts into the initial array
	  B[i] = A[i];							//Mirroring the values of A[] into another array
  	  }
  	  System.out.println ("Sorting...");
  	  System.out.println ("Printing out BubbleSort...");
  	  counter = BubbleSort(A);
  	  Print (A);  // Print method to print out every item in the array after it is sorted.
  	  System.out.println ("Sorting...");
  	  System.out.println ("Printing out MergeSort...");
  	  counterr = MergeSort(B);
  	  Print (B);        // // Print method to print out every item in the array after it is sorted.
  	  System.out.println ("BubbleSort checked "+counter+" times, but Mergesort checked "+counterr+" times!");
 	 if (counter<counterr)
 	   	System.out.println ("Then obviously BubbleSort is faster!");
 	  else if (counter>counterr)
 	  	System.out.println ("Then obviously MergeSort is faster!");
	  else if (counter == counterr)
	  	System.out.println ("Woh, they tied! Thats wierd!");
 }



 public static int BubbleSort (String A[])
 {
	 int counter = 0;
     int a = A.length;
	 for (int i=a; i>0;i--)
	 	{
		 for (int z=0; z<i-1; z++)
		 {
		 int k = z+1;
			counter ++;
			if (A[z].compareTo(A[k])>0)
				{
				  String t = A[k];
				  A[k] = A[z];
				  A[z] = t;
				  }
	      }
	    }
	 return counter;
	}

 public static int MergeSort (String B[])
 {
	 String[] L = new String[(B.length+1)/2]; // Setting two new arrays to hold half of the original
	 String[] H = new String[(B.length)-(L.length)];
	 int k = L.length;
	 int j = 0;
	 for (int i=0; i<k;i++)	// Setting each array to hold half of the array each, effectively splitting it
	   {
		   L[i] = B[i];
	   }
	 for (int i=k;i<B.length;i++)
	 {
	 	H[j] = B[i];
	 	j++;
	 }
	 int ct = BubbleSort(L) + BubbleSort (H); // Putting both arrays into BubbbleSort and then adding up the counter from both returns.
	 ct += merge(L,H,B);

	return ct;
	}

public static void Print (String[] A)
{
	for (int i=0;i<A.length; i++)
		System.out.println (A[i]);
}

public static int merge (String[] L, String[] H, String[] B) //This method merges the arrays from BubbleMergeSort - I didn't think it would constitute its own method
{                                                            //but soon the amount of code I put into it forced me to put it in a different method.
	int lpos = 0;
	int hpos = 0;
	int bpos = 0;
	int counter = 0;
	while (lpos < L.length && hpos < H.length) // Does basic compares until one of the two sorted arrays runs out
 	{
	    if (L[lpos].compareTo(H[hpos])<0)
	    {
			B[bpos] = L[lpos];
			lpos++;
			counter++;
	    }
	    else {B[bpos] = H[hpos];hpos++;counter++;}
	    bpos++;
	}

	String[] temp;
	int temppos=0;
	if (lpos >= L.length) {temp = H; temppos = hpos;} //Fills up a temporary array with what is left of the leftover array
	else{temp = L;temppos = lpos;}
	for (int i=temppos; i<temp.length; i++) //Sets original array to it.
	{
	    B[bpos] = temp[i];
	    bpos++;
	}
	return counter; //returns the amount of times that things were compared, which is important.
    }
}