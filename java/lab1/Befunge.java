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
 	 * Prints message "Needs argument" if not to put argument.
 	 * Prints message "Can't find file <file name>" if can't find file for execution.
	 * Uses Factory and Context to execute the program.
	 * Uses property file for Factory configuration.
	 * If can't find properties file prints "Can't find file properties.txt".
	 * If can't configurate Factory prints "Can't configurate Factory".
	 * Prints "Can't use command <command name>" if file contains undefined command.
	 * If the command was executed with an error prints this error.
	 * @param argv - array that contains file name.
	*/
	public static void main(String[] argv) {
		if (argv.length < 1) {
			System.out.println("Needs argument");
			return;
		}
		Context context = null;
		try (Scanner scan = new Scanner(new File(argv[0]))) {
			context = new Context(scan);
		} catch (IOException e){
			System.out.println("Can't find file " + argv[0]);
			return;
		}
		InputStream in = Befunge.class.getClassLoader().getResourceAsStream("properties.txt");
		if (in == null) {
			System.out.println("Can't find file properties.txt");
			return;
		}
		if(!Factory.getInstance().configurate(in)) {
			System.out.println("Can't configurate Factory");
			return;
		}

		while(true) {
			Character key = context.getKey();
			Command command = (Command)Factory.getInstance().getCommand(key.toString());
			if(command == null){
				System.out.println("Can't use command " + key);
				return;
			}
			try {
				command.execute(context);
			} catch (RuntimeException error){
				System.out.println(error);
				return;
			}
			if (context.jobIsFinished()){
				break;
			}
		}
		return;
	}
}