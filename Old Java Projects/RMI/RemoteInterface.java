//Name: Nick McIntyre-Wyma
//Project: RMI testing using Java instead of C++

public interface RemoteInterface extends java.rmi.Remote{
  public java.util.Date askTime() throws java.rmi.RemoteException;
  public void tellTime(java.util.Date d) throws java.rmi.RemoteException;
}
