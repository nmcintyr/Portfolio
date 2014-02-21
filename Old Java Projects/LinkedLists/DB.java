//Name: Nick McIntyre-Wyma
//Program: This program is made to add, delete, or search a user-defined database of students using LinkedLists in Java.
import java.util.*;

public class DB {

 public static Scanner in = new Scanner (System.in);
 public static void main (String[] args)
{

  LinkedList L = new LinkedList();
  double t = 0;
  int forever = 0;
  while (forever <1)
  {
	  System.out.print ("What do you want to do? ");
  	  String s = in.nextLine();
  	 // in.nextLine();
	  if (s.compareTo("add") == 0 || s.compareTo("ADD") == 0) // Takes in the name and average and feeds it into the LL add method
		{
	   	  System.out.print ("What is the student's name? " );
		  s = in.nextLine();
		  System.out.print ("What is the student's course average? ");
		  t = in.nextDouble();
		  in.nextLine();
		  System.out.println ("Adding student....");
		  L.Add (s,t);
		}
	  else if (s.compareTo ("delete") == 0 || s.compareTo("DELETE") == 0)
	  {
		  System.out.print ("What student do you wish to delete from the list? ");
		  s = in.nextLine();
		  L.Delete(s);
		  System.out.println ("Deleting..... ");
	  }
	  else if (s.compareTo ("search") == 0 || s.compareTo("SEARCH") == 0)
	  {
		  System.out.print ("Who do you want to search for? ");
		  s = in.nextLine();
		  System.out.println ("Searching....");
		  L.Search(s);
	  }
	  else if (s.compareTo ("quit") == 0 || s.compareTo("QUIT") == 0){forever ++;}
	  else if (s.compareTo ("print") ==0 || s.compareTo("PRINT") == 0){L.print();}
		else;
  }
 }
}