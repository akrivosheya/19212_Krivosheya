public class Mouse implements Platform{
    public Mouse(int initLeftTopX, int initLeftTopY, int initRightBotX, int initRightBotY){
        leftTopCornerX = initLeftTopX;
        leftTopCornerY = initLeftTopY;
        rightBottomCornerX = initRightBotX;
        rightBottomCornerY = initRightBotY;
    }
    @Override
    public int getLeftTopX(){
        return leftTopCornerX;
    }
    @Override
    public int getLeftTopY(){
        return leftTopCornerY;
    }
    @Override
    public int getRightBottomX(){
        return rightBottomCornerX;
    }
    @Override
    public int getRightBottomY(){
        return rightBottomCornerY;
    }

	@Override
	public int getHeight(){
		return leftTopCornerY - rightBottomCornerY;
	}

	public int getWidth(){
		return rightBottomCornerX - leftTopCornerX;
	}

    @Override
    public boolean isMouse(){
        return isMouse;
    }

    @Override
    public Type getType(){
        return Type.HORIZONTAL;
    }

    @Override
    public boolean conflictsDown(Platform platform){
        return (platform.getLeftTopY() > leftTopCornerY) && 
		(platform.getRightBottomY() == leftTopCornerY) &&
                (platform.getRightBottomX() > leftTopCornerX) &&
                (platform.getLeftTopX() < rightBottomCornerX);
    }
    @Override
    public boolean conflictsUp(Platform platform){
        return (rightBottomCornerY > platform.getRightBottomY()) &&
		(rightBottomCornerY == platform.getLeftTopY()) &&
            	(platform.getRightBottomX() > leftTopCornerX) &&
                (platform.getLeftTopX() < rightBottomCornerX);
    }
    @Override
    public boolean conflictsRight(Platform platform){
        return (leftTopCornerX > platform.getLeftTopX()) &&
		 (leftTopCornerX == platform.getRightBottomX()) &&
                (platform.getRightBottomY() < leftTopCornerY) &&
                (platform.getLeftTopY() > rightBottomCornerY);
    }
    @Override
    public boolean conflictsLeft(Platform platform){
        return (platform.getRightBottomX() > rightBottomCornerX) &&
		(platform.getLeftTopX() == rightBottomCornerX) &&
                (platform.getRightBottomY() < leftTopCornerY) &&
                (platform.getLeftTopY() > rightBottomCornerY);
    }

    @Override
    public void move(int coordX, int coordY){
        leftTopCornerX += coordX;
        rightBottomCornerX += coordX;
        leftTopCornerY += coordY;
        rightBottomCornerY += coordY;
    }

    private int leftTopCornerX;
    private int leftTopCornerY;
    private int rightBottomCornerX;
    private int rightBottomCornerY;
    private boolean isMouse = true;
}
