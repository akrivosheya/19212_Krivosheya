import java.util.*;

public class Main{
	public static void main(String[] argv){
		if(argv.length < 1){
			System.out.println("No arguments. Usage: java Main [place]");
			return;
		}
		List<Place> places = PlacesMaster.getPlaces(argv[0]);
		for(Place place : places){
			place.print();
			System.out.println("\n");
		}
	}
}