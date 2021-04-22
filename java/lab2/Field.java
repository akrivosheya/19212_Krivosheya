import java.util.ArrayList;
import java.util.List;

public class Field {
	public Field(int initLeftTopX, int initLeftTopY, int initRightBotX,
		int initRightBotY, List<Platform> platforms){
		leftTopCornerX = initLeftTopX;
		leftTopCornerY = initLeftTopY;
		rightBottomCornerX = initRightBotX;
		rightBottomCornerY = initRightBotY;
		tabOfDependence = new ArrayList<>();
		for(int i = 0; i < platforms.size(); ++i){
			Platform.Type typeOfPlatform = platforms.get(i).getType();
			for(int j = 0; j < platforms.size(); ++j){
				if(i == j){
					tabOfDependence.add(i * platforms.size() + j, false);
				}
				else if(typeOfPlatform != platforms.get(j).getType()){
					tabOfDependence.add(i * platforms.size() + j, true);
				}
				else if((typeOfPlatform == Platform.Type.HORIZONTAL && 
						platforms.get(i).getLeftTopX() == platforms.get(j).getLeftTopX()) ||
						(typeOfPlatform == Platform.Type.HORIZONTAL && 
						platforms.get(i).getLeftTopY() == platforms.get(j).getLeftTopY())){
					tabOfDependence.add(i * platforms.size() + j, true);
				}
				else{
					tabOfDependence.add(i * platforms.size() + j, false);
				}
			}
		}
		/*for(int i = 0; i < platforms.size(); ++i){
			for(int j = 0; j < platforms.size(); ++j){
				System.out.print(tabOfDependence.get(i * platforms.size() + j) + " ");
			}
			System.out.println();
		}*/
	}

	public boolean checkMove(int index, int coordX, int coordY, List<Platform> platforms){
		Platform.Type typeOfPlatform = platforms.get(index).getType();
		for(int i = 0; i < platforms.size(); ++i){
			if(tabOfDependence.get(index * platforms.size() + i)){
				if(typeOfPlatform == Platform.Type.VERTICAL){
					if(coordY > 0 && (platforms.get(i).conflictsUp(platforms.get(index)) ||
 						leftTopCornerY == platforms.get(index).getLeftTopY())){
						return false;
					}
					if(coordY < 0 && (platforms.get(i).conflictsDown(platforms.get(index)) ||
						platforms.get(index).getRightBottomY() == rightBottomCornerY)){
						return false;
					}
				}
				if(typeOfPlatform == Platform.Type.HORIZONTAL){
					if(coordX > 0 && (platforms.get(i).conflictsRight(platforms.get(index)) ||
						(rightBottomCornerX == platforms.get(index).getRightBottomX() &&
						!platforms.get(index).isMouse()))){
						return false;
					}
					if(coordX < 0 && (platforms.get(i).conflictsLeft(platforms.get(index)) ||
						platforms.get(index).getLeftTopX() == leftTopCornerX)){
						return false;
					}
				}
			}
		}
		return true;
	}

	public boolean isFinish(Platform platform){
		return platform.getRightBottomX() == rightBottomCornerX && platform.isMouse();
	}

	private int leftTopCornerX;
	private int leftTopCornerY;
	private int rightBottomCornerX;
	private int rightBottomCornerY;
	private List<Boolean> tabOfDependence;
}
