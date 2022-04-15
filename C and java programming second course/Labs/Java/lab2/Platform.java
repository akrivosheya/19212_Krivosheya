/** Class platform
 * @author Alexandr Krivosheya
 * @version 1.0
*/
public class Platform{
	/** 
	 * Creates platform.
	 * @param initLeftTopX - x coordinate of left top corner of platform.
	 * @param initLeftTopY - y coordinate of left top corner of platform.
	 * @param initRightBotX - x coordinate of rigth bottom corner of platform.
	 * @param initRigthBotY - y coordinate of right bottom corner of platform.
	*/
    public Platform(int initLeftTopX, int initLeftTopY, int initRightBotX,
                   int initRightBotY, Type initType, boolean initIsMouse){
        leftTopCornerX = initLeftTopX;
        leftTopCornerY = initLeftTopY;
        rightBottomCornerX = initRightBotX;
        rightBottomCornerY = initRightBotY;
        type = initType;
		isMouse = initIsMouse;
    }
	
	/** 
	 * @return Returns x coordinate of left top corner.
	*/
    public int getLeftTopX(){
        return leftTopCornerX;
    }
	
	/** 
	 * @return Returns y coordinate of left top corner.
	*/
    public int getLeftTopY(){
        return leftTopCornerY;
    }
	
	/** 
	 * @return Returns x coordinate of right bottom corner.
	*/
    public int getRightBottomX(){
        return rightBottomCornerX;
    }
	
	/** 
	 * @return Returns y coordinate of right bottom corner.
	*/
    public int getRightBottomY(){
        return rightBottomCornerY;
    }

	/** 
	 * @return Returns height.
	*/
	public int getHeight(){
		return leftTopCornerY - rightBottomCornerY;
	}

	/** 
	 * @return Returns width.
	*/
	public int getWidth(){
		return rightBottomCornerX - leftTopCornerX;
	}

	/** 
	 * Checks if platform when it moves down conflicts with current platform.
	 * @param platform - platform that is moving.
	 * @return Returns true if platform conflicts with current platform and false else.
	*/
    public boolean conflictsDown(Platform platform){
        return (platform.getLeftTopY() > leftTopCornerY) && 
		(platform.getRightBottomY() == leftTopCornerY) &&
                (platform.getRightBottomX() > leftTopCornerX) &&
                (platform.getLeftTopX() < rightBottomCornerX);
    }
	
	/** 
	 * Checks if platform when it moves up conflicts with current platform.
	 * @param platform - platform that is moving.
	 * @return Returns true if platform conflicts with current platform and false else.
	*/
    public boolean conflictsUp(Platform platform){
        return (rightBottomCornerY > platform.getRightBottomY()) &&
		(rightBottomCornerY == platform.getLeftTopY()) &&
            	(platform.getRightBottomX() > leftTopCornerX) &&
            	(platform.getLeftTopX() < rightBottomCornerX);
    }
	
	/** 
	 * Checks if platform when it moves right conflicts with current platform.
	 * @param platform - platform that is moving.
	 * @return Returns true if platform conflicts with current platform and false else.
	*/
    public boolean conflictsRight(Platform platform){
        return (leftTopCornerX > platform.getLeftTopX()) &&
		 (leftTopCornerX == platform.getRightBottomX()) &&
                (platform.getRightBottomY() < leftTopCornerY) &&
                (platform.getLeftTopY() > rightBottomCornerY);
    }
	
	/** 
	 * Checks if platform when it moves left conflicts with current platform.
	 * @param platform - platform that is moving.
	 * @return Returns true if platform conflicts with current platform and false else.
	*/
    public boolean conflictsLeft(Platform platform){
        return (platform.getRightBottomX() > rightBottomCornerX) &&
		(platform.getLeftTopX() == rightBottomCornerX) &&
                (platform.getRightBottomY() < leftTopCornerY) &&
                (platform.getLeftTopY() > rightBottomCornerY);
    }

	/** 
	 * Checks if platform is mouse.
	 * @return Return true if platform is mouse and false else.
	*/
    public boolean isMouse(){
        return isMouse;
    }

	/** 
	 * @return Returns type of platform.
	*/
    public Type getType(){
        return type;
    }

	/** 
	 * Changes coordinates of platform.
	 * @param coordX - moving in coordinate x.
	 * @param coordY - moving in cooridinate y.
	*/
    public void move(int coordX, int coordY){
        leftTopCornerX += coordX;
        rightBottomCornerX += coordX;
        leftTopCornerY += coordY;
        rightBottomCornerY += coordY;
    }

    /** 
	 * X coordinate of left top corner.
	*/
	private int leftTopCornerX;
	/** 
	 * Y coordinate of left top corner.
	*/
	private int leftTopCornerY;
	/** 
	 * X coordinate of right bottom corner.
	*/
	private int rightBottomCornerX;
	/** 
	 * Y coordinate of right bottom corner.
	*/
	private int rightBottomCornerY;
	/** 
	 * Type of platform.
	*/
    private Type type;
	/** 
	 * Flag if platform is mouse (always false).
	*/
    private boolean isMouse;
	/** 
	 * Types of platform.
	*/
	public enum Type{HORIZONTAL, VERTICAL};
}
