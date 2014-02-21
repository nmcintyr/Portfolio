//Name: Nick McIntyre-Wyma
//Project: RMI testing using Java instead of C++

public class RemoteObject extends java.rmi.server.UnicastRemoteObject
  implements RemoteInterface{
  public RemoteObject() throws java.rmi.RemoteException{
  }
  public java.util.Date askTime() throws java.rmi.RemoteException{
    System.out.println("RemoteObject.askTime called" + new java.util.Date() + "\n");
    return new java.util.Date();
  }
  public void tellTime(java.util.Date d) throws java.rmi.RemoteException{
    System.out.println("RemoteObject.tellTime called" + d + "\n");
  }
}
