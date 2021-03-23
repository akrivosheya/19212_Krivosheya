public class Barrier implements Platform{
    public Barrier(int initLeftTopX, int initLeftTopY, int initRightBotX,
                   int initRightBotY, Type initType){
        leftTopCornerX = initLeftTopX;
        leftTopCornerY = initLeftTopY;
        rightBottomCornerX = initRightBotX;
        rightBottomCornerY = initRightBotY;
        type = initType;
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
    public boolean conflictsDown(Platform platform){
        return !((platform.getRightBottomY() - leftTopCornerY > MIN) &&
                (platform.getRightBottomX() > leftTopCornerX) &&
                (platform.getLeftTopX() < rightBottomCornerX));
    }
    @Override
    public boolean conflictsUp(Platform platform){
        return !((rightBottomCornerY - platform.getLeftTopY() > MIN) &&
                (platform.getRightBottomX() > leftTopCornerX) &&
                (platform.getLeftTopX() < rightBottomCornerX));
    }
    @Override
    public boolean conflictsLeft(Platform platform){
        return !((leftTopCornerX - platform.getRightBottomX() > MIN) &&
                (platform.getRightBottomY() < leftTopCornerY) &&
                (platform.getLeftTopY() > rightBottomCornerY));
    }
    @Override
    public boolean conflictsRight(Platform platform){
        return !((platform.getLeftTopX() - rightBottomCornerX > MIN) &&
                (platform.getRightBottomY() < leftTopCornerY) &&
                (platform.getLeftTopY() > rightBottomCornerY));
    }

    @Override
    public boolean isMouse(){
        return isMouse;
    }

    @Override
    public Type GetType(){
        return type;
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
    private Type type;
    private boolean isMouse = false;
    private int MIN = 1;
}
