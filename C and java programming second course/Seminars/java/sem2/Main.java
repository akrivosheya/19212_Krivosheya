public class Main{
	public static void main(String[] argv){
		Thread t = new Thread(new MyRunnable());
		Thread v = new Thread(new MyRunnable());
		v.start();
		t.start();
	}
}