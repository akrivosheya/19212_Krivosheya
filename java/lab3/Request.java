public class Request{
	public Request(){}
	
	public void setPiece(int piece){
		this.piece = piece;
	}
	
	public void setText(byte[] text){
		this.text = text;
	}
	
	public void setMode(char mode){
		this.mode = mode;
	}
	
	public void setOffset(int offset){
		this.offset = offset;
	}
	
	public void setBlockLength(int blockLength){
		this.blockLength = blockLength;
	}
	
	public int getPiece(){
		return piece;
	}
	
	public char getMode(){
		return mode;
	}
	
	public int getOffset(){
		return offset;
	}
	
	public int getBlockLength(){
		return blockLength;
	}
	
	public byte[] getText(){
		return text;
	}

	private char mode;
	private int piece;
	private int offset;
	private int blockLength;
	private byte[] text;
}