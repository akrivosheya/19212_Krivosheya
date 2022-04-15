import java.util.concurrent.*;
import java.net.http.*;
import java.net.URI;
import java.util.function.*;
import java.util.*;
import javax.json.*;
import javax.json.stream.JsonParser;
import javax.json.stream.JsonParser.Event;
import java.math.BigDecimal;
import java.io.StringReader;
import java.time.Duration;

public class PlacesMaster{
	private PlacesMaster(){}
	
	public static List<Place> getPlaces(String place){
		HttpClient client = HttpClient.newHttpClient();
		HttpRequest requestCoordsAndTitles = HttpRequest.newBuilder()
			.uri(URI.create(scheme + "graphhopper.com/api/1/geocode?q=" + place + "&locale=de&debug=true&key=" + keyCoordsAndTitles))
			.header("Content-Type", "application/json")
			.timeout(timeout)
			.build();
		CompletableFuture<String> namesAndCoordsJson = client.<String>sendAsync(requestCoordsAndTitles,
			HttpResponse.BodyHandlers.ofString())
			.thenApply(HttpResponse::body);
		CompletableFuture<List<Place> > places = 
		namesAndCoordsJson.thenApply((String text)->{
			return parseList(text, client).join();
		});
		return places.join();
	}
	
	private static CompletableFuture<List<Place> > parseList(String nameAndCoordsJson, HttpClient client){
		List<CompletableFuture<Place> > places = new ArrayList<CompletableFuture<Place> >();
		try(JsonParser parser = Json.createParser(new StringReader(nameAndCoordsJson))){
			String key = null;
			String name = null;
			Event event = null;
			while (parser.hasNext()) {
				event = parser.next();
				if(event == Event.KEY_NAME) {
					key = parser.getString();
					if(key.equals(placeCoords)){
						do{
							event = parser.next();
						}while(event != Event.KEY_NAME || !parser.getString().equals(firstCoord));
						event = parser.next();
						BigDecimal lat = parser.getBigDecimal();
						event = parser.next();
						event = parser.next();
						BigDecimal lng = parser.getBigDecimal();
						do{
							event = parser.next();
						} while(event != Event.KEY_NAME || !parser.getString().equals(placeName));
						event = parser.next();
						name = parser.getString();
						CompletableFuture<Place> place = makePlace(name, lat, lng, client);
						places.add(place);
					}
				}
			}
		} catch (RuntimeException ex){
			System.err.println("Problem with parsing places:\n" + ex);
			return null;
		}
		return listOfFuturesToList(places);
	}
	
	private static CompletableFuture<List<String> > parseEnvironments(String environmentsJson, HttpClient client){
		List<CompletableFuture<String> > environmentsFutures = new ArrayList<CompletableFuture<String> >();
		try(JsonParser parser = Json.createParser(new StringReader(environmentsJson))){
			String key = null;
			Event event = null;
			while (parser.hasNext()) {
				event = parser.next();
				if(event == Event.KEY_NAME) {
					key = parser.getString();
					if(key.equals(placeXid)){
						event = parser.next();
						String xid = parser.getString();
						do{
							event = parser.next();
						} while(event != Event.KEY_NAME || !parser.getString().equals(placeName));
						event = parser.next();
						String name = parser.getString();
						if(name.length() > 0){
							CompletableFuture<String> environment = makeEnvironment(name, xid, client);
							environmentsFutures.add(environment);
						}
					}
				}
			}
		} catch (RuntimeException ex){
			System.out.println("Problem with parsing environments:\n" + ex);
			return null;
		}
		return listOfFuturesToList(environmentsFutures);
	}
	
	private static String parseDescription(String descriptionJson){
		try(JsonParser parser = Json.createParser(new StringReader(descriptionJson))){
			String key = null;
			Event event = null;
			while (parser.hasNext()) {
				event = parser.next();
				if(event == Event.KEY_NAME) {
					key = parser.getString();
					if(key.equals(descriptionText)){
						event = parser.next();
						String description = parser.getString();
						return description;
					}
				}
			}
		} catch (RuntimeException ex){
			System.err.println("Problem with parsing description:\n" + ex);
			return "No description";
		}
		return "No description";
	}
	
	private static String parseWeather(String weatherJson){
		try(JsonParser parser = Json.createParser(new StringReader(weatherJson))){
			String key = null;
			Event event = null;
			String description = null;
			BigDecimal temperature = null;
			while (parser.hasNext()) {
				event = parser.next();
				if(event == Event.KEY_NAME) {
					key = parser.getString();
					if(key.equals(weatherDescription)){
						event = parser.next();
						description = parser.getString();
					}
					else{
						continue;
					}
					do{
						event = parser.next();
					}while(event != Event.KEY_NAME || !parser.getString().equals(weatherTemperature));
					event = parser.next();
					temperature = parser.getBigDecimal();
					return description + "; temperature: " + temperature;
				}
			}
		} catch (RuntimeException ex){
			System.err.println("Problem with parsing weather:\n" + ex);
			return null;
		}
		return "No weather";
	}
	
	private static CompletableFuture<String> makeEnvironment(String name, String xid, HttpClient client){
		HttpRequest requestDescription = HttpRequest.newBuilder()
			.uri(URI.create(scheme + "api.opentripmap.com/0.1/ru/places/xid/" + xid + "?apikey=" + keyEnvironments))
			.header("Content-Type", "application/json")
			.timeout(timeout)
			.build();
		CompletableFuture<String> descriptionJson = client.<String>sendAsync(requestDescription,
			HttpResponse.BodyHandlers.ofString())
			.thenApply(HttpResponse::body);
		CompletableFuture<String> environmentJson = descriptionJson.thenApply(PlacesMaster::parseDescription);
		
		CompletableFuture<String> environment = environmentJson.thenApply((String description) -> {
			return name + ":\n\t\t" + description;
		});
		return environment;
	}
	
	private static CompletableFuture<Place> makePlace(String name, BigDecimal lat, BigDecimal lng, HttpClient client){
		HttpRequest requestEnvironments = HttpRequest.newBuilder()
			.uri(URI.create(scheme + "api.opentripmap.com/0.1/ru/places/radius?radius=1000&lon=" + lng + "&lat=" + lat + "&apikey=" + keyEnvironments))
			.header("Content-Type", "application/json")
			.timeout(timeout)
			.build();
		CompletableFuture<String> environmentsJson = client.<String>sendAsync(requestEnvironments,
			HttpResponse.BodyHandlers.ofString())
			.thenApply(HttpResponse::body);
		CompletableFuture<List<String> > environments = 
		environmentsJson.thenApply((String text) -> {
			return parseEnvironments(text, client).join();
		});
		
		HttpRequest requestWeather = HttpRequest.newBuilder()
			.uri(URI.create(scheme + "api.openweathermap.org/data/2.5/weather?lat=" + lat + "&lon=" + lng + "&appid=" + keyWeather))
			.header("Content-Type", "application/json")
			.timeout(timeout)
			.build();
		CompletableFuture<String> weatherJson = client.<String>sendAsync(requestWeather,
			HttpResponse.BodyHandlers.ofString())
			.thenApply(HttpResponse::body);
		CompletableFuture<String> weather = weatherJson.thenApply(PlacesMaster::parseWeather);
		
		CompletableFuture<Place> place = CompletableFuture.allOf(environments, weather).thenApply((Void v) -> {
			try{
				return new Place(name, lat, lng, weather.get(), environments.get());
			}
			catch(InterruptedException | ExecutionException ex){
				System.err.println("Can't make place:\n" + ex);
				return new Place(null, null, null, null, null);
			}
		});
		return place;
	}
	
	private static <T> CompletableFuture<List<T> > listOfFuturesToList(List<CompletableFuture<T> > listOfFutures){
		List<T> normalList = new ArrayList<T>();
		CompletableFuture<List<T> > futureList = new CompletableFuture<List<T> >();
		for(CompletableFuture<T> future : listOfFutures){
			future.thenAccept((T completed)->{
				synchronized(normalList){
					normalList.add(completed);
					if(normalList.size() == listOfFutures.size()){
						futureList.complete(normalList);
					}
				}
			});
		}
		if(listOfFutures.size() == 0){
			futureList.complete(normalList);
		}
		return futureList;
	}
	
	private static String keyCoordsAndTitles = "85c7a27f-d268-4638-b18c-a3da54682961";
	private static String keyEnvironments = "5ae2e3f221c38a28845f05b67764a970f1b815284c7f811a2d326b9e";
	private static String keyWeather = "b8e622681a240f24f29522be30f04cdd";
	private static String scheme = "https://";
	private static String placeName = "name";
	private static String placeCoords = "point";
	private static String placeExtent = "extent";
	private static String descriptionText = "text";
	private static String weatherDescription = "description";
	private static String weatherTemperature = "temp";
	private static String firstCoord = "lat";
	private static String secondCoord = "lng";
	private static String placeXid = "xid";
	private static int extentSize = 4;	
	private static int lon_minIndx = 0;
	private static int lat_minIndx = 1;
	private static int lon_maxIndx = 2;
	private static int lat_maxIndx = 3;
	private static Duration timeout = Duration.ofSeconds(10);
	private static long waiting = 1000;
}