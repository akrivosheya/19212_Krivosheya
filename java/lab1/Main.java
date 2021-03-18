import java.lang.*;

public class Main{
	public static void main(String[] argv){
		if (argv.length < 1) {
			System.out.println("Needs argument");
			return;
		}
		Befunge bef = new Befunge();
		bef.interpret(argv, new ContextIO());
	}
}
