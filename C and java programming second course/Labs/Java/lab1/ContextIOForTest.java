import java.io.*;
import java.util.logging.LogManager;
import java.util.logging.Logger;

/**
 * Class that contains interfacese for reading and writing. Is used for testing.
 * Extends from ContextIO.
*/
public class ContextIOForTest extends ContextIO{
	/**
	 * Inintializes string.
	*/
	public ContextIOForTest(String[] initBuf) {
		string = new StringBuilder("");
		buf = initBuf;
		log.info("Initialized string and buf");
	}
	
	/**
	 * Puts numb in string.
	 * @param numb - number putting.
	*/
	@Override
	public void printInt(int numb) {
		log.info("Appends " + numb + " to string");
		string.append(numb);
	}
	
	/**
	 * Puts text in string.
	 * @param text - text for printing.
	*/
	@Override
	public void println(String text) {
		log.info("Appends " + text + " to string");
		string.append(text);
	}

	/**
	 * Puts character in string.
	 * @param symb - character for printing.
	*/
	@Override
	public void printChar(char symb){
		log.info("Appends " + symb + " to string");
		string.append(symb);
	}

	/**
	 * @return Returns element of buf.
	*/
	@Override
	public String readLine() {
		log.info("return " + buf[i]);
		return buf[i++];
	}

	/**
	 * @return Returns element of buf.
	*/
	@Override
	public char read() {
		log.info("return " + buf[i].charAt(0));
		return buf[i++].charAt(0);
	}

	public String getString(){
		return string.toString();
	}
	
	/**
	 * Contains output.
	*/
	private StringBuilder string;
	/**
	 * Buffer for input.
	*/
	private String[] buf;
	/**
	 * Current position in buf.
	*/
	private int i = 0;
	static final Logger log = Logger.getLogger(ContextIOForTest.class.getName());
}
