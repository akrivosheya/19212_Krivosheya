import java.net.*;
import java.util.*;
import java.io.*;
import java.time.LocalTime;
import java.nio.charset.Charset;
import com.google.protobuf.InvalidProtocolBufferException;

import snakes.*;

public class Online{
	public boolean canWork(){
		return canWork;
	}
	
	public void begin(){
		try{
			socket = new MulticastSocket(PORT);
			InetAddress multicastAddress = InetAddress.getByName(MULTICAST_ADDRESS);
			group = new InetSocketAddress(multicastAddress, PORT);
		}
		catch(IOException exception){
			System.err.println(exception);
			return;
		}
		if(SUCCESS != configSocket(socket, group)){
			System.err.println("Can't config socket");
			return;
		}
		Random random = new Random();
		myCode = random.nextInt();
		while(myCode < 0){
			myCode = random.nextInt();
		}
		System.out.println(myCode);
		Thread thread = new Thread(new Reciever());
		thread.start();
		int generationTime = 0;
		byte[] type = new byte[1];
		byte[] byteCode = getByteArray(myCode);
		DatagramPacket message;
		try{
			while(true){
				switch(role){
					case PLAYER :
						if(generationTime > MAX_GENERATION_TIME_PLAYER){
							checkPeers();
							generationTime = 0;
							currentGeneration = !currentGeneration;
							if(role != Role.PLAYER){
								continue;
							}
						}
						if(master != null){
							type[0] = KEEP_ALIVE;
							byte[] byteMessage = new byte[type.length + byteCode.length];
							byteMessage[0] = type[0];
							copyRange(byteMessage, byteCode, TYPE_SIZE);
							message = new DatagramPacket(byteMessage, byteMessage.length, master.address, PORT);
							socket.send(message);
						}
						break;
					case SPARE :
						if(generationTime > MAX_GENERATION_TIME){
							checkPeers();
							generationTime = 0;
							currentGeneration = !currentGeneration;
							if(role != Role.SPARE){
								continue;
							}
						}
						if(master != null){
							type[0] = KEEP_ALIVE;
							byte[] byteMessage = new byte[type.length + byteCode.length];
							byteMessage[0] = type[0];
							copyRange(byteMessage, byteCode, TYPE_SIZE);
							message = new DatagramPacket(byteMessage, byteMessage.length, master.address, PORT);
							socket.send(message);
						}
						break;
					case MASTER :
						if(generationTime > MAX_GENERATION_TIME){
							checkPeers();
							generationTime = 0;
							currentGeneration = !currentGeneration;
						}
						/*if(spare != null && alivePeers.containsKey(spare.code)){
							type[0] = NEW_SPARE;
						}
						else{*/
							type[0] = KEEP_ALIVE;
						//}
						byte[] byteMessage = new byte[type.length + byteCode.length];
						byteMessage[0] = type[0];
						copyRange(byteMessage, byteCode, TYPE_SIZE);
						message = new DatagramPacket(byteMessage, byteMessage.length, group.getAddress(), PORT);
						socket.send(message);
						break;
				}
				Thread.sleep(TIMEOUT);
				++generationTime;
			}
		}
		catch(IOException | InterruptedException exception){
			System.out.println(exception);
		}
	}
	
	public void changeDirection(int newDirection){
		switch(role){
			case PLAYER :
			case SPARE :
				if(null == master){
					return;
				}
				byte[] type = {CHANGE_DIRECTION};
				byte[] byteCode = getByteArray(myCode);
				byte[] byteDirection = {(byte)newDirection};
				byte[] byteMessage = new byte[type.length + byteCode.length + byteDirection.length];
				byteMessage[0] = type[0];
				copyRange(byteMessage, byteCode, TYPE_SIZE);
				copyRange(byteMessage, byteDirection, TYPE_SIZE + INT_SIZE);
				DatagramPacket message = new DatagramPacket(byteMessage, byteMessage.length, master.address, PORT);
				try{
					socket.send(message);
				}
				catch(IOException exception){
					System.err.println(exception);
					canWork = false;
				}
				break;
			case MASTER :
				if(UP == newDirection){
					snakes.changeDirection(myCode, Player.Direction.UP);
				}
				else if(DOWN == newDirection){
					snakes.changeDirection(myCode, Player.Direction.DOWN);
				}
				else if(LEFT == newDirection){
					snakes.changeDirection(myCode, Player.Direction.LEFT);
				}
				else if(RIGHT == newDirection){
					snakes.changeDirection(myCode, Player.Direction.RIGHT);
				}
		}
	}
	
	private void sendScene(){
		if(Role.MASTER == role){
			if(spare != null){
				SnakesProto.Builder protoSnakes = SnakesProto.newBuilder();
				protoSnakes.setX(6);
				protoSnakes.setY(6);
				for(Unit unit : snakes.getUnits()){
					UnitProto.Builder protoUnit = UnitProto.newBuilder();
					protoUnit.setCode(unit.getCode());
					protoUnit.setPoints(unit.getPoints());
					Player.Direction currentDirection = unit.getDirection();
					if(Player.Direction.UP == currentDirection){
						protoUnit.setDirection(UnitProto.Direction.UP);
					}
					else if(Player.Direction.DOWN == currentDirection){
						protoUnit.setDirection(UnitProto.Direction.DOWN);
					}
					else if(Player.Direction.LEFT == currentDirection){
						protoUnit.setDirection(UnitProto.Direction.LEFT);
					}
					else if(Player.Direction.RIGHT == currentDirection){
						protoUnit.setDirection(UnitProto.Direction.RIGHT);
					}
					for(DataSegment segment : unit.getSegments()){
						SegmentProto.Builder protoSegment = SegmentProto.newBuilder();
						protoSegment.setX(segment.getX());
						protoSegment.setY(segment.getY());
						protoSegment.setIsHead(segment.isHead());
						protoUnit.addSegments(protoSegment);
					}
					protoSnakes.addUnits(protoUnit);
				}
				byte[] type = {NEW_UNITS};
				byte[] byteCode = getByteArray(myCode);
				byte[] byteSnakes = protoSnakes.build().toByteArray();
				byte[] byteSize = getByteArray(byteSnakes.length);
				byte[] byteMessage = new byte[type.length + byteCode.length + byteSnakes.length + byteSize.length];
				byteMessage[0] = type[0];
				copyRange(byteMessage, byteCode, TYPE_SIZE);
				copyRange(byteMessage, byteSize, TYPE_SIZE + INT_SIZE);
				copyRange(byteMessage, byteSnakes, TYPE_SIZE + 2 * INT_SIZE);
				DatagramPacket message = new DatagramPacket(byteMessage, byteMessage.length, spare.address, PORT);
				try{
					socket.send(message);
				}
				catch(IOException exception){
					System.err.println(exception);
					canWork = false;
				}
			}
			String scene = snakes.getScene();
			System.out.println(scene);
			byte[] byteScene = new byte[0];
			try{
				byteScene = scene.getBytes("UTF-8");
			}
			catch(UnsupportedEncodingException exception){
				System.out.println(exception);
				canWork = false;
			}
			byte[] type = {NEW_SCENE};
			byte[] byteCode = getByteArray(myCode);
			byte[] byteSize = getByteArray(byteScene.length);
			byte[] byteMessage = new byte[type.length + byteCode.length + byteScene.length + byteSize.length];
			byteMessage[0] = type[0];
			copyRange(byteMessage, byteCode, TYPE_SIZE);
			copyRange(byteMessage, byteSize, TYPE_SIZE + INT_SIZE);
			copyRange(byteMessage, byteScene, TYPE_SIZE + 2 * INT_SIZE);
			DatagramPacket message = new DatagramPacket(byteMessage, byteMessage.length, group.getAddress(), PORT);
			try{
				socket.send(message);
			}
			catch(IOException exception){
				System.err.println(exception);
				canWork = false;
			}
		}
	}
	
	private boolean configSocket(MulticastSocket socket, InetSocketAddress group){
		try{
			NetworkInterface netIf = NetworkInterface.getByName(LOOP_BACK_INTERFACE);
			socket.joinGroup(group, netIf);
			socket.setReuseAddress(REUSING_ADDRESS);
			socket.setOption(StandardSocketOptions.IP_MULTICAST_IF, NetworkInterface.getByName(LOOP_BACK_INTERFACE));
		}
		catch(IOException exception){
			System.err.println(exception);
			return !SUCCESS;
		}
		return SUCCESS;
	}
	
	private byte[] getByteArray(int value){
		byte byteCode[] = {(byte)(value & 0xFF), (byte)(value >> 8 & 0xFF), (byte)(value >> 16 & 0xFF), (byte)(value >> 24 & 0xFF)};
		return byteCode;
	}
	
	private int getInt(byte byteArray[]){
		return (byteArray[0] & 0xFF) | (byteArray[1] << 8 & 0xFF00) | (byteArray[2] << 16 & 0xFF0000) | (byteArray[3] << 24 & 0xFF000000);
	}
	
	private String getScene(byte byteArray[]){
		try{
			return new String(byteArray, "UTF-8");
		}
		catch(UnsupportedEncodingException exception){
			System.err.println(exception);
			canWork = false;
			return "Can't get scene";
		}
	}
	
	class Reciever implements Runnable{
		public Reciever(){}
		
		@Override
		public void run(){
			byte[] buf = new byte[MAX_SIZE];
			DatagramPacket recv;
			int size;
			String scene = "";
			recv = new DatagramPacket(buf, buf.length);
			try{
				while(true){
					socket.receive(recv);
					if(recv.getLength() < TYPE_SIZE + INT_SIZE){
						continue;
					}
					int type = recv.getData()[0];
					int code = getInt(getSubrange(recv.getData(), TYPE_SIZE, INT_SIZE));
					if(code != myCode){
						switch(role){
							case PLAYER:
								if(NEW_SCENE == type){
									size = getInt(getSubrange(recv.getData(), INT_SIZE + TYPE_SIZE, 2 * INT_SIZE));
									if(size % 2 != 1 && size < MAX_SIZE - TYPE_SIZE - INT_SIZE){
										scene = getScene(getSubrange(recv.getData(), 2 * INT_SIZE + TYPE_SIZE, size + 2 * INT_SIZE));
									}
									System.out.println(scene);
								}
								else if(NEW_SPARE == type){
									setIsAlive(code, recv.getAddress());
									role = Role.SPARE;
									snakes = new snakes.Snakes(6, 6);
								}
								else if(KEEP_ALIVE == type){
									setIsAlive(code, recv.getAddress());
								}
								break;
							case SPARE :
								if(KEEP_ALIVE == type){
									setIsAlive(code, recv.getAddress());
								}
								else if(NEW_UNITS == type){
									setIsAlive(code, recv.getAddress());
									size = getInt(getSubrange(recv.getData(), INT_SIZE + TYPE_SIZE, 2 * INT_SIZE));
									SnakesProto newSnakes = SnakesProto.parseFrom(getSubrange(recv.getData(), 2 * INT_SIZE + TYPE_SIZE, size + 2 * INT_SIZE));
									List<Unit> units = getUnits(newSnakes);
									snakes.reset(units);
									scene = snakes.getScene();
									System.out.println(scene);
								}
								else if(NEW_SCENE == type){
									setIsAlive(code, recv.getAddress());
								}
								break;
							case MASTER :
								if(KEEP_ALIVE == type){
									setIsAlive(code, recv.getAddress());
								}
								if(CHANGE_DIRECTION == type){
									int direction = recv.getData()[TYPE_SIZE + INT_SIZE];
									setIsAlive(code, recv.getAddress());
									System.out.println(direction);
									if(UP == direction){
										snakes.changeDirection(code, Player.Direction.UP);
									}
									else if(DOWN == direction){
										snakes.changeDirection(code, Player.Direction.DOWN);
									}
									else if(LEFT == direction){
										snakes.changeDirection(code, Player.Direction.LEFT);
									}
									else if(RIGHT == direction){
										snakes.changeDirection(code, Player.Direction.RIGHT);
									}
								}
								break;
						}
					}
				}
			}
			catch(IOException exception){
				System.err.println(exception);
				canWork = false;
			}
		}
	}
	
	private List<Unit> getUnits(SnakesProto newSnakes){
		List<Unit> units = new ArrayList<Unit>();
		for(UnitProto protoUnit : newSnakes.getUnitsList()){
			List<DataSegment> segments = new ArrayList<DataSegment>();
			for(SegmentProto protoSegment : protoUnit.getSegmentsList()){
				segments.add(new DataSegment(protoSegment.getX(), protoSegment.getY(), protoSegment.getIsHead()));
			}
			UnitProto.Direction currentDirection = protoUnit.getDirection();
			if(currentDirection == UnitProto.Direction.UP){
				units.add(new Unit(protoUnit.getCode(), protoUnit.getPoints(), segments, Player.Direction.UP));
			}
			else if(currentDirection == UnitProto.Direction.DOWN){
				units.add(new Unit(protoUnit.getCode(), protoUnit.getPoints(), segments, Player.Direction.DOWN));
			}
			else if(currentDirection == UnitProto.Direction.LEFT){
				units.add(new Unit(protoUnit.getCode(), protoUnit.getPoints(), segments, Player.Direction.LEFT));
			}
			else if(currentDirection == UnitProto.Direction.RIGHT){
				units.add(new Unit(protoUnit.getCode(), protoUnit.getPoints(), segments, Player.Direction.RIGHT));
			}
		}
		return units;
	}
	
	private void setIsAlive(int code, InetAddress address){
		switch(role){
			case PLAYER:
				if(master == null){
					master = new Pair(code, address, currentGeneration);
				}
				else if(code == master.code){
					master.generation = currentGeneration;
				}
				firstInvoking = false;
				break;
			case SPARE :
				if(master == null){
					master = new Pair(code, address, currentGeneration);
				}
				else if(code == master.code){
					master.generation = currentGeneration;
				}
				break;
			case MASTER :
				if(alivePeers.containsKey(code)){
					alivePeers.remove(code);
				}
				else{
					snakes.putNewPlayer(code);
				}
				alivePeers.put(code, new Pair(code, address, currentGeneration));
				break;
		}
	}
	
	private void checkPeers(){
		try{
			switch(role){
				case PLAYER :
					if((master == null || master.generation != currentGeneration) && firstInvoking){
						role = Role.MASTER;
						snakes = new snakes.Snakes(6, 6);
						snakes.putNewPlayer(myCode);
						start();
					}
					break;
				case SPARE :
					if(master == null || master.generation != currentGeneration){
						role = Role.MASTER;
						start();
					}
				case MASTER : 
					List<Integer> peersToDestroy = new ArrayList<Integer>();
					alivePeers.forEach((Integer code, Pair data) -> {
						if(data.generation != currentGeneration){
							peersToDestroy.add(code);
						}
					});
					for(Integer code : peersToDestroy){
						alivePeers.remove(code);
					}
					if((spare == null || !alivePeers.containsKey(spare.code)) && !alivePeers.isEmpty()){
						int newSpareCode = ((Pair)(alivePeers.values().toArray()[0])).code;
						spare = alivePeers.get(newSpareCode);
						byte[] type = {NEW_SPARE};
						byte[] byteCode = getByteArray(myCode);
						byte[] byteMessage = new byte[type.length + byteCode.length];
						byteMessage[0] = type[0];
						copyRange(byteMessage, byteCode, TYPE_SIZE);
						DatagramPacket message = new DatagramPacket(byteMessage, byteMessage.length, spare.address, PORT);
						socket.send(message);
					}
					break;
			}
		}
		catch(IOException exception){
			System.err.println(exception);
			canWork = false;
		}
	}
	
	private void copyRange(byte to[], byte from[], int firstIndex){
		for(int i = 0; i < from.length; ++i){
			to[i + firstIndex] = from[i];
		}
	}
	
	private byte[] getSubrange(byte source[], int firstIndex, int lastIndex){
		byte[] newBytes = new byte[lastIndex - firstIndex + 1];
		try{
		for(int i = 0; i < newBytes.length; ++i){
			newBytes[i] = source[i + firstIndex];
		}
		}
		catch(RuntimeException exception){
			System.out.println("It is here");
		}
		return newBytes;
	}
	
	private void start(){
		timer.schedule(new SnakesUpdater(), DELAY);
	}
	
	class SnakesUpdater extends TimerTask{
		@Override
		public void run(){
			if(Role.MASTER == role){
				snakes.update();
				sendScene();
				timer.schedule(new SnakesUpdater(), DELAY);
			}
		}
	}
	
	private enum Role{MASTER, SPARE, PLAYER};
	
	class Pair{
		public Pair(int init_code, InetAddress init_address, boolean init_generation){
			code = init_code;
			address = init_address;
			generation = init_generation;
		}
		
		public int code;
		public InetAddress address;
		public boolean generation;
	}
	
	private int TIMEOUT = 25;
	private int PORT = 4321;
	private int TYPE_SIZE = 1;
	private int INT_SIZE = 4;
	private int CHAR_SIZE = 2;
	private int MAX_SIZE = 180;
	private int MAX_GENERATION_TIME = 5;
	private int MAX_GENERATION_TIME_PLAYER = 10;
	private byte KEEP_ALIVE = 0;
	private byte NEW_SPARE = 1;
	private byte CHANGE_DIRECTION = 2;
	private byte NEW_UNITS = 3;
	private byte NEW_SCENE = 4;
	private int UP = 0;
	private int DOWN = 1;
	private int LEFT = 2;
	private int RIGHT = 3;
	private  String LOOP_BACK_INTERFACE = "lo";
	private String MULTICAST_ADDRESS = "224.0.0.1";
	private boolean SUCCESS = true;
	private boolean REUSING_ADDRESS = true;
	private MulticastSocket socket;
	private int myCode;
	private boolean currentGeneration = false;
	private Map<Integer, Pair> alivePeers = new HashMap<Integer, Pair>();
	private Pair master = null;
	private Pair spare = null;
	private snakes.Snakes snakes = null;
	private Role role = Role.PLAYER;
	private boolean firstInvoking = true;
	private boolean canWork = true;
	private InetSocketAddress group;
	private Timer timer = new Timer();
	private long DELAY = 1000;
}