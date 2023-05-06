public class ClientJNI{
    static{
        System.loadLibrary("tlib");
    }

    public native void request_token(String ip_addr);
    
    public static void main(String[] args){
        if(args.length == 1){
            new ClientJNI().request_token(args[0]);
        }
        else{
            System.out.println("Please enter only [ip:port]\n");
        }
    }
}