public class Barrier implements Platform{
    public Barrier(double initLeftTopX, double initLeftTopY, double initRightBotX,
                   double initRightBotY, Type initType){
        leftTopCornerX = initLeftTopX;
        leftTopCornerY = initLeftTopY;
        rightBottomCornerX = initRightBotX;
        rightBottomCornerY = initRightBotY;
        type = initType;
    }
    @Override
    public double getLeftTopX(){
        return leftTopCornerX;
    }
    @Override
    public double getLeftTopY(){
        return leftTopCornerY;
    }
    @Override
    public double getRightBottomX(){
        return rightBottomCornerX;
    }
    @Override
    public double getRightBottomY(){
        return rightBottomCornerY;
    }

	@Override
	public double getHeight(){
		return leftTopCornerY - rightBottomCornerY;
	}

	public double getWidth(){
		return rightBottomCornerX - leftTopCornerX;
	}

    @Override
    public boolean conflictsDown(Platform platform){
        return (platform.getLeftTopY() > leftTopCornerY) && 
		(platform.getRightBottomY() - leftTopCornerY < MIN) &&
                (platform.getRightBottomX() > leftTopCornerX + MIN) &&
                (platform.getLeftTopX() + MIN < rightBottomCornerX);
    }
    @Override
    public boolean conflictsUp(Platform platform){
        return (rightBottomCornerY > platform.getRightBottomY()) &&
		(rightBottomCornerY - platform.getLeftTopY() < MIN) &&
            	(platform.getRightBottomX() > leftTopCornerX + MIN) &&
            	(platform.getLeftTopX() + MIN < rightBottomCornerX);
    }
    @Override
    public boolean conflictsRight(Platform platform){
        return (leftTopCornerX > platform.getLeftTopX()) &&
		 (leftTopCornerX - platform.getRightBottomX() < MIN) &&
                (platform.getRightBottomY() + MIN < leftTopCornerY) &&
                (platform.getLeftTopY() > rightBottomCornerY + MIN);
    }
    @Override
    public boolean conflictsLeft(Platform platform){
        return (platform.getRightBottomX() > rightBottomCornerX) &&
		(platform.getLeftTopX() - rightBottomCornerX < MIN) &&
                (platform.getRightBottomY() + MIN < leftTopCornerY) &&
                (platform.getLeftTopY() > rightBottomCornerY + MIN);
    }

    @Override
    public boolean isMouse(){
        return isMouse;
    }

    @Override
    public Type getType(){
        return type;
    }

    @Override
    public void move(double coordX, double coordY){
        leftTopCornerX += coordX;
        rightBottomCornerX += coordX;
        leftTopCornerY += coordY;
        rightBottomCornerY += coordY;
    }

    private double leftTopCornerX;
    private double leftTopCornerY;
    private double rightBottomCornerX;
    private double rightBottomCornerY;
    private Type type;
    private boolean isMouse = false;
    private int MIN = 2;
}
