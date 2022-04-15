import java.lang.reflect.Method;
import java.lang.ClassLoader;

public class factory{
 public static void main(String[] args) throws Exception{
  if (args.length < 1){
   System.out.println("Give me an argument");
   return;
  }
		
  String className = args[0];
  System.out.println("Trying to load a class" + className);

  java.lang.Class<?> cl = null;
  try{
   cl = java.lang.Class.forName(className);
   System.out.println("loaded" + cl.getName());
  } catch (ClassNotFoundException e){
   System.err.println("Bad");
   return;
  }

  Object o = cl.getDeclaredConstructor().newInstance();
  System.out.println("object " + o);

  Method[] methods = cl.getDeclaredMethods();
  for(Method m : methods){
   System.out.println(m.getName());
   m.invoke(o);
  }
	
	String lol = args[1];
	java.io.InputStream inp = factory.class.getClassLoader().getResourceAsStream(lol);
	System.out.println((char)inp.read());
	System.out.println(inp.read());
 }
}