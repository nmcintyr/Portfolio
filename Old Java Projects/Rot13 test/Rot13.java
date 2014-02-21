// Name: Nick McIntyre-Wyma
// Program: This program was made to do simple encoding/decoding of a string put in by the user.
import java.util.*;

public class Rot13 {

 public static Scanner in = new Scanner (System.in);

 public static void main (String[] args)
 {
	 String s;
     System.out.print ("Please enter a string:  ");
     s = in.nextLine();
     s = Encode (s); // Runs the Encode method, which does the actual encoding/decoding
     System.out.println ("Your encoded/decoded phrase is:  "+s);
 }


 public static String Encode (String s) // This does the actual encoding of the user's string.
 {
  String e =""; // Setting e as a empty string to be filled up.
  for (int i = 0; i<s.length();i++)
  	{
		char a = s.charAt(i);
		if      (a >= 'a' && a <= 'm') // All lowercase letters between a and m moved up 13
			a += 13;
		else if (a >= 'n' && a <= 'z')// All lowercase letters between n and z moved down 13
			a -= 13;
		else if (a >= 'A' && a <= 'M') // All uppercase letters between A and M moved up 13
			a += 13;
		else if (a >= 'N' && a <= 'Z')// All lowercase letters between N and Z moved down 13
			a -= 13;
		 e += a;
    }
  return e;
   }
}