import java.util.ArrayList;
import java.util.List;

public class Field {
    public Field(int initLeftTopX, int initLeftTopY, int initRightBotX,
                 int initRightBotY, List<Platform> platforms){
        leftTopCornerX = initLeftTopX;
        leftTopCornerY = initLeftTopY;
        rightBottomCornerX = initRightBotX;
        rightBottomCornerY = initRightBotY;
        tabOfDependence = new ArrayList<>(platforms.size() * platforms.size());
        for(int i = 0; i < platforms.size(); ++i){
            Platform.Type typeOfPlatform = platforms.get(i).GetType();
            for(int j = 0; j < platforms.size(); ++j){
                if(typeOfPlatform == platforms.get(j).GetType()){
                    tabOfDependence.add(i * platforms.size() + j, true);
                }
                else{
                    tabOfDependence.add(i * platforms.size() + j, false);
                }
            }
        }
    }

    public boolean checkMove(int index, int coordX, int coordY, List<Platform> platforms){
        Platform.Type typeOfPlatform = platforms.get(index).GetType();
        for(int i = 0; i < platforms.size(); ++i){
            if(tabOfDependence.get(index * platforms.size() + i)){
                if(typeOfPlatform == Platform.Type.HORIZONTAL){
                    if(coordY > 0 && platforms.get(i).conflictsUp(platforms.get(index)) &&
                            leftTopCornerY - platforms.get(index).getLeftTopY() > MIN){
                        return false;
                    }
                    if(coordY < 0 && platforms.get(i).conflictsDown(platforms.get(index)) &&
                            platforms.get(index).getRightBottomY() - rightBottomCornerY > MIN){
                        return false;
                    }
                }
                if(typeOfPlatform == Platform.Type.VERTICAL){
                    if(coordX > 0 && platforms.get(i).conflictsRight(platforms.get(index))){
                        return false;
                    }
                    if(coordX < 0 && platforms.get(i).conflictsLeft(platforms.get(index))&&
                            platforms.get(index).getLeftTopX() - leftTopCornerX > MIN){
                        return false;
                    }
                }
            }
        }
        return true;
    }

    public boolean isFinish(Platform platform){
        return platform.getRightBottomX() >= rightBottomCornerX;
    }

    private int leftTopCornerX;
    private int leftTopCornerY;
    private int rightBottomCornerX;
    private int rightBottomCornerY;
    private List<Boolean> tabOfDependence;
    private int MIN = 1;
}
