import java.util.*;
import java.io.*;
import java.lang.RuntimeException;

public class Befunge{
	public static int main(String[] argv){
		if (argv.length < 1){
			System.out.println("Needs argument");
			return 0;
		}
		Context context = null;
		try (Scanner scan = new Scanner(new File(argv[0]))){
			context = new Context(scan);
		} catch (IOException e){
			System.out.println("Can't find file " + argv[0]);
			return 0;
		}
		InputStream in = Befunge.class.getClassLoader().getResourceAsStream("properties.txt");
		if (in == null){
			System.out.println("Can't find file properties.txt");
			return 0;
		}
		if(!Factory.getInstance().configurate(in)){
			System.out.println("Can't configurate Factory");
			return 0;
		}

		while(true){
			Character key = context.getKey();
			Command command = (Command)Factory.getInstance().getCommand(key.toString());
			if(command == null){
				System.out.println("Can't use command " + key);
				return 0;
			}
			try {
				command.execute(context);
			} catch (RuntimeException error){
				System.out.println(error);
				return 0;
			}
			if (context.jobIsFinished()){
				break;
			}
		}
		return 0;
	}
}
