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
    public Type GetType();
    public enum Type{HORIZONTAL, VERTICAL};
}
