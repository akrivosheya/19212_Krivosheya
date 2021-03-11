/**
 * Class for with empty command. Implements from the Command interface
 * @author Alexandr Krivosheya
 * @version 1.0
*/
public class Space implements Command{
	/**
	 * Empty command. Does nothing.
	 * @param context - special object that contains stack and other attributes.
	*/
	@Override
	public void execute(Context context){
		context.changePosition();
	}
}