import java.lang.*;
import java.util.logging.*;

public class Main{
	public static void main(String[] argv){
		try{
			LogManager.getLogManager().readConfiguration(Main.class.getResourceAsStream("log.properties"));
		} catch (java.io.IOException error){
			log.throwing("Main", "main", error);
		}
		if (argv.length < 1) {
			log.info("Didn't get file");
			System.out.println("Needs argument");
			return;
		}
		Befunge bef = new Befunge();
		bef.interpret(argv, new ContextIO());
		log.info("Finished successfully");
	}
	static final Logger log = Logger.getLogger(Main.class.getName());
}
