public class LinkedList {

 private LinkedListNode head = null;

 public LinkedListNode gethead () {return head;}

 public void Add (String s, double t)
 	{
	 if (head != null) head.Add(s,t);
	 else head = new LinkedListNode (s,t, null);
	}

 public void print () //Prints the nothing if its empty, goes to LLN if its not.
 {
	 if (head != null) head.print();
	 System.out.println ();
 }

 public void Delete (String s) //Returns an error if there is no one to delete; else it goes to LLN delete.
 {
	 if (head != null) head = head.Delete (s);
	 else System.out.println ("ERROR: THERE IS NOTHING TO DELETE!");
 }

 public void Search (String s)// Returns nothing if its empty, else goes to LLN to search.
 {
	 if (head != null) head.Search(s);
	 if (head == null) System.out.println (s+" wasn't found but would be at the beginning of the list.");
	 System.out.println();
}
}