import java.lang.RuntimeException;
import java.io.IOException;

public class ReaderChar implements Command{
	@Override
	public void execute(Context context){
		char symb;
		try {
			symb = (char)context.getReader().read();
		} catch (IOException error){
			throw new RuntimeException("Can't read text");
		}
		context.push((int)symb);
		context.changePosition();
	}
}