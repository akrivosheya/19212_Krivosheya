import java.util.*;
import java.io.*;
import java.lang.RuntimeException;
import java.util.logging.Logger;

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
			log.info(argv.length + " arguments");
			contIO.println("Needs argument");
			return;
		}
		context = null;
		try (Scanner scan = new Scanner(new File(argv[0]))) {
			context = new Context(scan, contIO);
		} catch (IOException error){
			log.throwing("Befunge", "interpret", error);
			contIO.println("Can't find file " + argv[0]);
			return;
		} catch (RuntimeException error) {
			log.throwing("Befunge", "interpret", error);
			contIO.println(error.toString());
			return;
		}
		try(InputStream in = Befunge.class.getClassLoader().getResourceAsStream("properties.txt")){
			if (in == null) {
				log.info("in == null");
				contIO.println("Can't find file properties.txt");
				return;
			}
			if(!Factory.getInstance().configurate(in)) {
				contIO.println("Can't configurate Factory");
			}
		}
		catch (IOException error) {
			log.throwing("Befunge", "interpret", error);
			contIO.println(error.toString());
			return;
		}

		while(true) {
			Character key = context.getKey();
			Command command = (Command)Factory.getInstance().getCommand(key.toString());
			if(command == null){
				log.info("Wrong command " + command);
				contIO.println("Can't use command " + key);
				return;
			}
			try {
				command.execute(context);
			} catch (RuntimeException error){
				log.throwing("Befunge", "interpret", error);
				contIO.println(error.toString());
				return;
			}
			if (context.jobIsFinished()){
				break;
			}
		}
		log.info("Job is finished");
		return;
	}

	public int getForTest() {
		log.info("return " + context.get());
		return context.get();
	}

	public void popForTest() {
		log.info("Pop element");
		context.pop();
	}

	public boolean jobIsFinishedForTest() {
		log.info("return " + context.jobIsFinished());
		return context.jobIsFinished();
	}


	public int sizeForTest() {
		log.info("return " + context.size());
		return context.size();
	}
	/**
	 * Special object that contains stack and field.
	 */
	private Context context;
	static final Logger log = Logger.getLogger(Befunge.class.getName());
}
