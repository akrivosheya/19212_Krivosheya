import java.util.*;
import java.math.BigDecimal;

class Place{
	public Place(String init_name, BigDecimal init_coordLat, BigDecimal init_coordLng, 
	String init_weather, List<String> init_environment){
		if(init_name == null){
			name = defaultName;
		}
		else{
			name = init_name;
		}
		if(init_coordLat == null){
			coordLat = defaultCoord;
		}
		else{
			coordLat = init_coordLat;
		}
		if(init_coordLng == null){
			coordLng = defaultCoord;
		}
		else{
			coordLng = init_coordLng;
		}
		if(init_weather == null){
			weather = defaultWeather;
		}
		else{
			weather = init_weather;
		}
		if(init_environment == null){
			environments = new ArrayList<String>();
			environments.add(defaultEnvironments);
		}
		else{
			environments = init_environment;
		}
	}
	
	public void print(){
		System.out.println(name + " with coordinates: ");
		System.out.println("\tlat: " + ((coordLat.equals(defaultCoord) ? "NO_FOUND_LAT" : coordLat)) + ", lng: " + ((coordLng.equals(defaultCoord) ? "NO_FOUND_LNG" : coordLng)));
		System.out.println("\t weather: " + weather);
		System.out.println("Environments:");
		for(String env : environments){
			System.out.println("\t" + env);
		}
	}
	
	public void putEnvironments(List<String> newEnvironments){
		environments = newEnvironments;
	}
	
	private String name = null;
	private BigDecimal coordLat = null;
	private BigDecimal coordLng = null;
	private String weather = null;
	private List<String> environments = null;
	private String defaultName = "NO_FOUND_NAME";
	private BigDecimal defaultCoord = new BigDecimal(-1);
	private String defaultWeather = "NO_FOUND_WEATHER";
	private String defaultEnvironments = "NO_FOUND_ENVIRONMENTS";
}