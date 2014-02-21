//Name: Nick McIntyre-Wyma
//Program: Tribonacci is a simple program that spits out the tribonacci sequence according to the user input number.
import java.util.*;

public class Tribonacci {

 public static Scanner in = new Scanner (System.in);

 public static void main (String[] args)
 {
  System.out.print ("Enter an integer:  ");
  int n = Integer.parseInt (in.nextLine());
   System.out.println (tribonacci (n));
 }

 public static long tribonacci (int n) {

  if (n<3)
  {
         if (n==0) return 0;
         else return 1;
  }
  return tribonacci (n-1) + tribonacci (n-2)+ tribonacci (n-3);
 }
}
