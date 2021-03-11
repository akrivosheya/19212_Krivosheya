import java.util.*;
import java.lang.*;
import java.io.*;
import java.lang.reflect.InvocationTargetException;

/**
 * Class for creating commands
 * @author Alexandr Krivosheya
 * @version 1.0
*/
public class Factory {
	/**
	 * Private constructor for creating only one object.
	*/
	private Factory(){
		commands = new HashMap<>();
		names = new Properties();
	}

	/**
	 * Retruns object of command by symbol of this command.
	 * Buffers used classes of commands.
	 * @throws RuntimeException If Can't load class of command or create object throws .
	 * @param key - symbol of commmand.
	 * @return Returns object of command. If symbol is not real command returns null.
	*/
	public Object getCommand(String key) {
		String name = null;
		if((name = names.getProperty(key)) == null) {
			return null;
		}
		Class<?> cl = null;
		Object comm = null;
		if(commands.containsKey(key)) {
			cl = commands.get(key);
		}
		else {
			try {
				cl = Class.forName(name);
			} catch (ClassNotFoundException error) {
				throw new RuntimeException("Can't find class" + name);
			}
		}

		try {
			comm = cl.getDeclaredConstructor().newInstance();
		} catch (NoSuchMethodException | InstantiationException |
				IllegalAccessException | InvocationTargetException error) {
			throw new RuntimeException("Can't create an instance of the class" + name);
		}

		commands.put(key, cl);
		return comm;
	}

	/**
	 * @return object of class Factory.
	*/
	public static Factory getInstance(){
		if(instance == null){
			instance = new Factory();
		}
		return instance;
	}

	/**
	 * Configurable by text of file.
	 * @param reader - stream for reading file.
	 * @return Returns true if configuration finished successfully. Else returns false.
	*/
	public boolean configurate(InputStream reader) {
		try {
			names.load(reader);
		} catch (IOException error) {
			return false;
		}
		return true;
	}

	/**
	 * Only one object of class.
	*/
	static Factory instance = null;
	/**
	 * Buffered commands.
	*/
	private Map<String, Class<?>> commands;
	/**
	 * All used commands, their symbols and full names.
	*/
	Properties names;
	/**
	 * End Of File.
	*/
	private int EOF = -1;
};