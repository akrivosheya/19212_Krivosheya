import java.lang.RuntimeException;
import java.io.IOException;

public class ReaderInt implements Command{
	@Override
	public void execute(Context context){
		String text = null;
		try {
			text = context.getReader().readLine();
		} catch (IOException error){
			throw new RuntimeException("Can't read text");
		}
		int numb = 0;
		for(int i = 0; i < text.length(); ++i){
			char symb = text.charAt(i);
			if(!Character.isDigit(symb)){
				break;
			}
			numb = numb * 10 + Character.digit(symb, Character.MAX_RADIX);
		}
		context.push(numb);
		context.changePosition();
	}
}