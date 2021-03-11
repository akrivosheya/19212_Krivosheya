import java.io.*;

/**
 * Class that contains interfacese for reading and writing.
*/
public class ContextIO{
	/**
	 * Inintializes reader and writer.
	*/
	public ContextIO() {
		Reader ir = new InputStreamReader(System.in);
		reader = new BufferedReader(ir);
		Writer ow = new OutputStreamWriter(System.out);
		writer = new PrintWriter(ow, true);
	}
	
	/**
	 * Prints number.
	 * @param numb - number for printing.
	*/
	public void printInt(int numb) {
		writer.println(numb);
	}
	
	/**
	 * Prints text.
	 * @param text - text for printing.
	*/
	public void println(String text) {
		writer.println(text);
	}

	/**
	 * Prints character.
	 * @param symb - character for printing.
	*/
	public void printChar(char symb){
		writer.println(symb);
	}

	/**
	 * Reads next entered line. 
	 * @throws RuntimeException If reading ended with an error.
	 * @return Returns entered line.
	*/
	public String readLine() {
		String text = null;
		try {
			text = reader.readLine();
		} catch (IOException error) {
			throw new RuntimeException("Can't read text");
		}
		return text;
	}

	/**
	 * Reads next entered character. 
	 * @throws RuntimeException If reading ended with an error.
	 * @return Returns entered character.
	*/
	public char read() {
		char symb;
		try {
			symb = (char)reader.read();
		} catch (IOException error) {
			throw new RuntimeException("Can't read text");
		}
		return symb;
	}
	
	/**
	 * Object for reading.
	*/
	private BufferedReader reader;
	/**
	 * Object for writing.
	*/
	private PrintWriter writer;
}