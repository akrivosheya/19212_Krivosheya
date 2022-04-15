import java.io.*;
import java.util.*;

class TestClosable implements AutoCloseable{
	public void doSome(){
		System.out.println("do");
	}

	@Override
	public void close(){
		System.out.println("close");
	}
}

class Finally{
	
	public static void main(String[] args){
		try (TestClosable t = new TestClosable()){
			t.doSome();
		}
/*		try (BufferedReader reader = new BufferedReader(new FileReader(fileName))){
//TestClosable не сработает если не переопределить close
			String line = null;
			while((line = reader.readLine()) != null){
				System.out.println(line);
			}
		}
		catch(IOException e){
			e.printStackTrace();
		}
*/

		try (Scanner sc = new Scanner(new File(args[0]))){
			System.out.println(sc.hasNextByte());
			System.out.println(sc.next() == "\n");
			System.out.println(sc.hasNextLine());
		}
		catch (IOException e){
			System.out.println("fuck");
		}

		List<Integer> list = new ArrayList<Integer>();
		list.add(1);
	}

}

//RAII