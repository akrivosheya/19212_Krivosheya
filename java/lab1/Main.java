import java.lang.*;

public class Main{
	public static void main(String[] argv){
		if (argv.length < 1) {
			System.out.println("Needs argument");
			return;
		}
		Befunge bef = new Befunge();
		StringBuilder string = new StringBuilder("");
		String[] buf = {"4", "6"};
		bef.interpret(argv, new ContextIOForTest(string, buf));
		//bef.interpret(argv, new ContextIO());
		System.out.printf(string.substring(0));
	}
}
