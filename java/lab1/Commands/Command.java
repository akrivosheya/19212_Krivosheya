/**
 * Interface for commands of befunge language interpret.
 * @author Alexandr Krivosheya
 * @version 1.0
*/
public interface Command {
	/** 
	 * Executes. Has to be overrided.
	 * @param context - special Object for execution.
	*/
	public void execute(Context context);
}