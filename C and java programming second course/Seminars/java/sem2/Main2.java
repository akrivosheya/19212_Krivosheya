import java.util.*;
import java.util.concurrent.atomic.AtomicInteger;

public class Main2{
	static Object monitor = new Object();
	static int counter = 0;
	static final int THREADS_NUM = 1000;
	static final int ITER_NUM = 1000;

	static class SpinLock{
		//int flag = 0;
		AtomicInteger flag = new AtomicInteger();

		public void lock(){
			//while(1 == flag);
			while(!flag.compareAndSet(0, 1));
			//flag = 1;
		}
		public void unlock(){
			flag.set(0);
		}
	}

	static SpinLock lock = new SpinLock();

	public static void main(String[] argv) throws Exception{
		List<Thread> threads = new ArrayList<Thread>();
		for(int i = 0; i < THREADS_NUM; ++i){
			Thread t = new Thread(new Runnable(){
					@Override
					public void run(){
						for(int j = 0; j < ITER_NUM; ++j){
							/*synchronized(monitor) {
								++counter;
							}*/
							lock.lock();
							counter++;
							lock.unlock();
						}
					}
			});
			threads.add(t);
		}

		long team = System.currentTimeMillis();

		for(int i = 0; i < THREADS_NUM; ++i){
			threads.get(i).start();
		}
		for(int i = 0; i < THREADS_NUM; ++i){
			threads.get(i).join();
		}

		team = System.currentTimeMillis() - team;
		System.out.println(counter);
		System.out.println("time = " + team);
	}
}