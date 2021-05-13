/** Class platform-mouse
 * @author Alexandr Krivosheya
 * @version 1.0
*/
public class Mouse implements Platform{
	/** 
	 * Creates mouse.
	 * @param initLeftTopX - x coordinate of left top corner of mouse.
	 * @param initLeftTopY - y coordinate of left top corner of mouse.
	 * @param initRightBotX - x coordinate of rigth bottom corner of mouse.
	 * @param initRigthBotY - y coordinate of right bottom corner of mouse.
	 * @param platforms - list of platforms of current level.
	*/
    public Mouse(int initLeftTopX, int initLeftTopY, int initRightBotX, int initRightBotY){
        leftTopCornerX = initLeftTopX;
        leftTopCornerY = initLeftTopY;
        rightBottomCornerX = initRightBotX;
        rightBottomCornerY = initRightBotY;
    }
	
	
	/** 
	 * @return Returns x coordinate of left top corner.
	*/
    @Override
    public int getLeftTopX(){
        return leftTopCornerX;
    }
	
	/** 
	 * @return Returns y coordinate of left top corner.
	*/
    @Override
    public int getLeftTopY(){
        return leftTopCornerY;
    }
	
	/** 
	 * @return Returns x coordinate of right bottom corner.
	*/
    @Override
    public int getRightBottomX(){
        return rightBottomCornerX;
    }
	
	/** 
	 * @return Returns y coordinate of right bottom corner.
	*/
    @Override
    public int getRightBottomY(){
        return rightBottomCornerY;
    }

	/** 
	 * @return Returns height.
	*/
	@Override
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
	 * Checks if platform is mouse.
	 * @return Always returns true.
	*/
    @Override
    public boolean isMouse(){
        return isMouse;
    }

	/** 
	 * @return Returns type of platform (only horizontal).
	*/
    @Override
    public Type getType(){
        return Type.HORIZONTAL;
    }

	/** 
	 * Checks if platform when it moves down conflicts with mouse.
	 * @param platform - platform that is moving.
	 * @return Returns true if platform conflicts with mouse and false else.
	*/
    @Override
    public boolean conflictsDown(Platform platform){
        return (platform.getLeftTopY() > leftTopCornerY) && 
		(platform.getRightBottomY() == leftTopCornerY) &&
                (platform.getRightBottomX() > leftTopCornerX) &&
                (platform.getLeftTopX() < rightBottomCornerX);
    }
	
	/** 
	 * Checks if platform when it moves up conflicts with mouse.
	 * @param platform - platform that is moving.
	 * @return Returns true if platform conflicts with mouse and false else.
	*/
    @Override
    public boolean conflictsUp(Platform platform){
        return (rightBottomCornerY > platform.getRightBottomY()) &&
		(rightBottomCornerY == platform.getLeftTopY()) &&
            	(platform.getRightBottomX() > leftTopCornerX) &&
                (platform.getLeftTopX() < rightBottomCornerX);
    }
	
	/** 
	 * Checks if platform when it moves right conflicts with mouse.
	 * @param platform - platform that is moving.
	 * @return Returns true if platform conflicts with mouse and false else.
	*/
    @Override
    public boolean conflictsRight(Platform platform){
        return (leftTopCornerX > platform.getLeftTopX()) &&
		 (leftTopCornerX == platform.getRightBottomX()) &&
                (platform.getRightBottomY() < leftTopCornerY) &&
                (platform.getLeftTopY() > rightBottomCornerY);
    }
	
	/** 
	 * Checks if platform when it moves left conflicts with mouse.
	 * @param platform - platform that is moving.
	 * @return Returns true if platform conflicts with mouse and false else.
	*/
    @Override
    public boolean conflictsLeft(Platform platform){
        return (platform.getRightBottomX() > rightBottomCornerX) &&
		(platform.getLeftTopX() == rightBottomCornerX) &&
                (platform.getRightBottomY() < leftTopCornerY) &&
                (platform.getLeftTopY() > rightBottomCornerY);
    }

	/** 
	 * Changes coordinates of mouse.
	 * @param coordX - moving in coordinate x.
	 * @param coordY - moving in cooridinate y.
	*/
    @Override
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
	 * Flag if platform is mouse (always true).
	*/
    private boolean isMouse = true;
}
