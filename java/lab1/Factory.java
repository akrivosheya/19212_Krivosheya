import java.util.*;
import java.lang.*;
import java.io.*;
import java.lang.reflect.InvocationTargetException;

public class Factory {
	private Factory(){
		commands = new HashMap<>();
		names = new Properties();
	}

	public Object getCommand(String key) {
		String name = null;
		if(commands.containsKey(key)){
			return commands.get(key);
		}
		if((name = names.getProperty(key)) == null){
			return null;
		}
		Class<?> cl = null;
		Object comm = null;

		try{
			cl = Class.forName(name);
		} catch (ClassNotFoundException error){
			throw new RuntimeException("Can't find class" + name);
		}

		try {
			comm = cl.getDeclaredConstructor().newInstance();
		} catch (NoSuchMethodException | InstantiationException |
				IllegalAccessException | InvocationTargetException error){
			throw new RuntimeException("Can't create an instance of the class" + name);
		}

		commands.put(key, cl);
		return comm;
	}

	public static Factory getInstance(){
		if(instance == null){
			instance = new Factory();
		}
		return instance;
	}

	public boolean configurate(InputStream reader) {
		try {
			names.load(reader);
		} catch (IOException error) {
			return false;
		}
		return true;
	}

	static Factory instance = null;
	private Map<String, Class<?>> commands;
	Properties names;
	private int EOF = -1;
	private int minLength = 1;
};
