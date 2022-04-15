import java.util.*;

public class Threadpool{
	Queue<Runnable> queue = new ArrayDeque<>();
	List<Thread> threads = new ArrayList<>();

	class Worker implements Runnable{
		@Override
		public void run(){
			while(true){
				if(Thread.currentThread().isInterrupted()){
					return;
				}
				synchronized(queue){
					while(queue.isEmpty()){
						try{
							queue.wait();
						} catch (InterruptedException e){
							System.out.println("Interrupted while wait()");
							return;
						}
					}
					Runnable task = queue.poll();
					task.run();
				}
			}	
		}
	}

	Threadpool(int numTasks){
		for(int i = 0; i < numTasks; ++i){
			Thread t = new Thread(new Worker());
			threads.add(t);
			t.start();
		}
	}
	
	public void addTask(Runnable task){
		synchronized(queue){
			queue.add(task);
			queue.notify();
		}
	}

	public void stop(){
		System.out.println(Thread.currentThread().isInterrupted());
	}
}