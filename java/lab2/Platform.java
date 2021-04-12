public interface Platform {
	public boolean isMouse();
	public void move(double coordX, double coordY);
	public boolean conflictsUp(Platform platform);
	public boolean conflictsDown(Platform platform);
	public boolean conflictsLeft(Platform platform);
	public boolean conflictsRight(Platform platform);
	public double getLeftTopX();
	public double getLeftTopY();
	public double getRightBottomX();
	public double getRightBottomY();
	public double getHeight();
	public double getWidth();
	public Type getType();
	public enum Type{HORIZONTAL, VERTICAL};
}
