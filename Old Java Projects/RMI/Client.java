//Name: Nick McIntyre-Wyma
//Project: RMI testing using Java instead of C++
public class Client{
  public static void main(String[] args){
    RemoteInterface s=null;
    try{
      s=(RemoteInterface)java.rmi.Naming.lookup("rmi://euclid.nmu.edu:5099/count");
      s.tellTime(new java.util.Date());
      System.out.println(s.askTime());
    }catch (Exception x){x.printStackTrace();}
  }
}
