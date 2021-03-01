import java.util.*;
import java.lang.Class;
import java.io.InputStream;

public class Factory {
	private Factory(){
		commands = new HashMap<>();
		names = new HashMap<>();
	}

	public Object getObject(char symb) throws Exception{
		if(!names.containsKey(symb)){
			System.out.println("Wrong command: " + symb);
			return null;
		}
		if(commands.containsKey(names.get(symb))){
			return commands.get(names.get(symb));
		}
		Class<?> cl = null;
		Object comm = null;
			try{
				cl = Class.forName(names.get(symb));
				comm = cl.getDeclaredConstructor().newInstance();
			} catch (ClassNotFoundException error){
				System.err.println("Can't find class " + names.get(symb));
				return null;
			}
		commands.put(names.get(symb), cl);
		return comm;
	}

	public Factory getInstance(){
		if(instance == null){
			instance = new Factory();
		}
		return instance;
	}

	public boolean configurate(InputStream reader) throws Exception{
		String line = null;
		char command;
		int codeOfSymb = 0;
		while(codeOfSymb != EOF){
			line = "";
			codeOfSymb = reader.read();
			if(codeOfSymb == EOF){
				return false;
			}
			command = (char)codeOfSymb;
			codeOfSymb = reader.read();
			if(codeOfSymb == EOF || codeOfSymb != '='){
				return false;
			}
			codeOfSymb = reader.read();
			while(codeOfSymb != EOF && codeOfSymb != '\n'){
				line += (char)codeOfSymb;
			}
			if(line.length() < minLength){
				return false;
			}
			names.put(command, line);
		}
		return true;
	}

	static Factory instance = null;
	private HashMap<String, Class<?>> commands;
	private HashMap<Character, String>  names;
	private static int EOF = -1;
	private static int minLength = 1;
};
