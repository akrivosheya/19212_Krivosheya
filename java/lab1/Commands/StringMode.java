import java.lang.RuntimeException;
import java.io.*;

public class StringMode implements Command{
	@Override
	public void execute(Context context){
		String text = "";
		context.changePosition();
		while(context.getKey() != '"'){
			text += context.getKey();
			context.changePosition();
		}
		context.getWriter().println(text);
		context.changePosition();
	}
}