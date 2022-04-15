import java.util.ArrayList;
import java.util.List;

/** Class that contains information about field of current level.
 * @author Alexandr Krivosheya
 * @version 1.0
*/
public class Field {
	/** 
	 * Constructs Field.
	 * @param initLeftTopX - x coordinate of left top corner of field.
	 * @param initLeftTopY - y coordinate of left top corner of field.
	 * @param initRightBotX - x coordinate of rigth bottom corner of field.
	 * @param initRigthBotY - y coordinate of right bottom corner of field.
	 * @param platforms - list of platforms of current level.
	*/
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
				else if((typeOfPlatform == Platform.Type.VERTICAL && 
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
	}

	/** 
	 * Check if moving is possible.
	 * @param index - index of current platform.
	 * @param coordX - moving in x coordinate.
	 * @param coordY - moving in y coordinate.
	 * @param platforms - list of platforms of current level.
	 * @return Returns true if moving is possible and false else.
	*/
	public boolean checkMove(int index, int coordX, int coordY, List<Platform> platforms){
		Platform.Type typeOfPlatform = platforms.get(index).getType();
		for(int i = 0; i < platforms.size(); ++i){
			if(tabOfDependence.get(index * platforms.size() + i)){
				if(typeOfPlatform == Platform.Type.VERTICAL){
					if(coordY > 0 && platforms.get(i).conflictsUp(platforms.get(index))){
						return false;
					}
					if(coordY < 0 && platforms.get(i).conflictsDown(platforms.get(index))){
						return false;
					}
				}
				if(typeOfPlatform == Platform.Type.HORIZONTAL){
					if(coordX > 0 && platforms.get(i).conflictsRight(platforms.get(index))){
						return false;
					}
					if(coordX < 0 && platforms.get(i).conflictsLeft(platforms.get(index))){
						return false;
					}
				}
			}
			if(typeOfPlatform == Platform.Type.VERTICAL){
				if(coordY > 0 && leftTopCornerY == platforms.get(index).getLeftTopY()){
					return false;
				}
				if(coordY < 0 && (platforms.get(i).conflictsDown(platforms.get(index)) ||
					platforms.get(index).getRightBottomY() == rightBottomCornerY)){
					return false;
				}
			}
			if(typeOfPlatform == Platform.Type.HORIZONTAL){
				if(coordX > 0 && rightBottomCornerX == platforms.get(index).getRightBottomX()){
					return false;
				}
				if(coordX < 0 && platforms.get(index).getLeftTopX() == leftTopCornerX){
					return false;
				}
			}
		}
		return true;
	}

	/** 
	 * Checks if level is finished.
	 * @param platform - last moved platform.
	 * @return Returns true if level is finished and false else.
	*/
	public boolean isFinish(Platform platform){
		return platform.getRightBottomX() == rightBottomCornerX && platform.isMouse();
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
	 * Tab with information which platform conflicts with another platform.
	*/
	private List<Boolean> tabOfDependence;
}
