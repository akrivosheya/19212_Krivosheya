/** Interface of platforms
 * @author Alexandr Krivosheya
 * @version 1.0
*/
public interface Platform {
	public boolean isMouse();
	public void move(int coordX, int coordY);
	public boolean conflictsUp(Platform platform);
	public boolean conflictsDown(Platform platform);
	public boolean conflictsLeft(Platform platform);
	public boolean conflictsRight(Platform platform);
	public int getLeftTopX();
	public int getLeftTopY();
	public int getRightBottomX();
	public int getRightBottomY();
	public int getHeight();
	public int getWidth();
	public Type getType();
	public enum Type{HORIZONTAL, VERTICAL};
}
