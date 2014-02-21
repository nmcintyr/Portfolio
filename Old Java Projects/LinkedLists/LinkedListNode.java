public class LinkedListNode {

 private String Name = "";
 private double avg = 0;
 private LinkedListNode next = null;

 public String getName () {return Name;}
 public void setName (String n) {Name = n;}

 public LinkedListNode getnext () {return next;}
 public void setnext (LinkedListNode n) {next = n;}


 public LinkedListNode (String N, double T, LinkedListNode n)
 {
 Name = N;
 next = n;
 avg = T;
 }

 public void Add (String s, double t)
 {
   if (next==null) next = new LinkedListNode (s,t,null);
   else next.Add(s,t);
 }


 public void print ()
  {
   if (next==null)
    {
    System.out.println (Name+" and his/her average is: "+avg);
    return;
   }
  System.out.println (Name+" and his/her average is: "+avg);
  next.print();
 }

 public LinkedListNode Delete (String s) //Actually deletes the value
 {
  if (s.compareTo(Name)==0) return next;
  else if (next==null) return this;
  next = next.Delete(s);
  return this;
 }

public void Search (String s) //Searches for the user through the LL
	{

		if (s.compareTo(Name) ==0)
		{
			System.out.println (Name+" has a class average of: "+avg);
			return;
		}
		else if (next == null && Name.compareTo(s)<0){System.out.println (s+" was not found but it would be after "+Name+".");}
		else if (next == null && Name.compareTo(s)>0){System.out.println (s+" was not found but it would be before "+Name+".");}
		else if (next.getName().compareTo(s)>0){System.out.println (s+" wasn't found but it would be located between "+Name+" and "+next.getName()+".");}
		else if (next.getnext() == null){System.out.println (s+" wasn't found but it would be located after "+next.getName()+".");}
		else if (next.getName().compareTo(s)>0 && Name.compareTo(s)>0){System.out.println(s+" wasn't found but it would be before "+Name+".");}
	    else if (next != null)
	    {
			next.Search(s);
	    	return;
		}
	else return;
	}
}
