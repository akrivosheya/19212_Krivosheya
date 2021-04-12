import java.util.ArrayList;
import java.util.List;

public class Model {
	public Model(List<Platform> initPlatforms){
		platforms = initPlatforms;
		field = new Field(0, 600, 600, 0, platforms);//default, change
	}

	public int move(int index, double coordX, double coordY){
		for(Platform platform : platforms){
			if(platforms.get(index) == platform){
				continue;
			}
			if(!field.checkMove(index, coordX, coordY, platforms)){
				return CANT_MOVE;
			}
		}
		int type;
		if(platforms.get(index).getType() == Platform.Type.HORIZONTAL){
			coordY = 0;
			type = MOVE_HORIZONTAL;
		}else{
			coordX = 0;
			type = MOVE_VERTICAL;
		}
		platforms.get(index).move(coordX, coordY);
        	return (field.isFinish(platforms.get(index))) ? IS_FINISH : type;
	}

	public List<Platform> getPlatforms(){
		return platforms;
	}

	private Field field;
	private List<Platform> platforms;
	private int CANT_MOVE = 1;
	private int IS_FINISH = 2;
	private int MOVE_HORIZONTAL = 3;
	private int MOVE_VERTICAL = 4;
}
