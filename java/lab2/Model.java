import java.util.ArrayList;
import java.util.List;

public class Model {
    public Model(){
        //InitializePlatforms
        field = new Field(0,0,100,100, platforms);//default, change
    }

    public boolean move(int index, int coordX, int coordY){
        if(field.checkMove(index, coordX, coordY, platforms)){
            platforms.get(index).move(coordX, coordY);
        }
        return field.isFinish(platforms.get(index));
    }

    private Field field;
    private List<Platform> platforms = new ArrayList<>();
}
