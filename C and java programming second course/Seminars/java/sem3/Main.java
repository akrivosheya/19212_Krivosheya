import java.util.Random;

public class Main{
	public static void main(String[] argv) throws InterruptedException{
		Threadpool tp = new Threadpool(10);

		for(int i = 0; i < 10000; ++i){
			tp.addTask(() -> {
				System.out.println("AAAAA!" + Thread.currentThread().getId());
				
			});
		}

		Thread.sleep(1000);
		tp.stop();
	}
}