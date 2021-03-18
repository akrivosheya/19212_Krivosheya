import java.util.*;
import java.io.*;
import java.lang.RuntimeException;

/**
 * Befunge language interpreter.
 * @author Alexandr Krivosheya
 * @version 1.0
*/
public class Befunge{
 	/**
	 * Accepts text in the befunge language and executes it.
	 * @param argv - array that contains file name.
	*/
	public void interpret(String[] argv, ContextIO contIO) {
		if (argv.length < 1) {
			contIO.println("Needs argument");
			return;
		}
		context = null;
		try (Scanner scan = new Scanner(new File(argv[0]))) {
			context = new Context(scan, contIO);
		} catch (IOException e){
			contIO.println("Can't find file " + argv[0]);
			return;
		}
		InputStream in = Befunge.class.getClassLoader().getResourceAsStream("properties.txt");
		if (in == null) {
			contIO.println("Can't find file properties.txt");
			return;
		}
		if(!Factory.getInstance().configurate(in)) {
			contIO.println("Can't configurate Factory");
			try {
				in.close();
			}
			catch (IOException error) {
				throw new RuntimeException();
			}
			return;
		}
		try {
			in.close();
		}
		catch (IOException error) {
			throw new RuntimeException();
		}

		while(true) {
			Character key = context.getKey();
			Command command = (Command)Factory.getInstance().getCommand(key.toString());
			if(command == null){
				contIO.println("Can't use command " + key);
				return;
			}
			try {
				command.execute(context);
			} catch (RuntimeException error){
				contIO.println(error.toString());
				return;
			}
			if (context.jobIsFinished()){
				break;
			}
		}

		return;
	}

	public int getForTest() {

		return context.get();
	}

	public void popForTest() {
		context.pop();
	}

	public boolean jobIsFinishedForTest() {
		return context.jobIsFinished();
	}


	public int sizeForTest() {
		return context.size();
	}
	/**
	 * Special object that contains stack and field.
	 */
	private Context context;
}