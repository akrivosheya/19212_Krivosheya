import java.util.*;

public class Main {
	public static void main(String[] args){
		
	}
	
	static <E extends Comparable<? super E>> E findMax(Collection<E> c){//в библ Collection<? extends E>, чтобы возвращался обёект выше в иерархии, ещё <E extends Object & ..> для старой java, что если не Comparable то что-то там возвращ
		Object o;
		return null;
	}
	
	static <E> E findMax(Collection<E> c, Comparator<? super E> cmp){
		return null;
	}
	
	void f(){
		class MyCmp implements Comparator<Number> {
			@Override
			public int compare(Number n1, Number n2){
				return 0;
			}
		}
		
		List<Integer> li = Arrays.asList(1, 2, 3);
		List<Double> ld = Arrays.asList(1., 2., 3.);
		
		findMax(li, new MyCmp());
		findMax(ld, new MyCmp());
	}
}