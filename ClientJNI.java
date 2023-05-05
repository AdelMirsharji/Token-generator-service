public class ClientJNI{
    static{
        System.loadLibrary("tlib");
    }
    public static void main(String[] args){
        new ClientJNI().sayHello();
    }
    public native void sayHello();
}