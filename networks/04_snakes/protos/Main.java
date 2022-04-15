import com.google.protobuf.InvalidProtocolBufferException;

public class Main{
	public static void main(String argv[]) throws InvalidProtocolBufferException{
		SnakesProto.Builder snakes = SnakesProto.newBuilder();
		snakes.setX(6);
		snakes.setY(6);
		for(int i = 0; i < 3; ++i){
			UnitProto.Builder unit = UnitProto.newBuilder();
			unit.setCode(i * 10);
			unit.setPoints(i * 283);
			unit.setDirection((i % 2 == 1) ? UnitProto.Direction.UP : UnitProto.Direction.DOWN);
			for(int j = 0; j < 3; ++j){
				SegmentProto.Builder segment = SegmentProto.newBuilder();
				segment.setX(j + i);
				segment.setY(j - i);
				segment.setIsHead((j == 0) ? true : false);
				unit.addSegments(segment);
			}
			snakes.addUnits(unit);
		}
		System.out.println(SnakesProto.parseFrom(snakes.build().toByteArray()));
	}
}