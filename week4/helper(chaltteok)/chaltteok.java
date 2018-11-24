import java.util.Scanner;
import java.util.ArrayList;
import java.util.List;
import java.util.Iterator;

public class chaltteok {
	static Scanner sc;

	static int pack(List<Integer> M) {
		System.out.print("?");
		System.out.print(" " + M.size());
		Iterator it = M.iterator();
		while(it.hasNext()){
			System.out.print(" " + it.next());
		}
		System.out.println();
		System.out.flush();
		int line = sc.nextInt();
		if(line == -202){
			System.exit(0);	
		}
		return line;
	}

	static void report(List<Integer> M) {
		System.out.print("!");
		Iterator it = M.iterator();
		while(it.hasNext()){
			System.out.print(" " + it.next());
		}
		System.out.println();
		System.out.flush();
	}

	public static void main(String[] args) {
		sc = new Scanner(System.in);

		int N = sc.nextInt();

		/* IMPLEMENT HERE */
		/* IMPLEMENT HERE */
		/* IMPLEMENT HERE */
		/* IMPLEMENT HERE */
		// Below is an example.
		// Don't forget to initialize all global variables.

		List<Integer> sel = new ArrayList<Integer>();
		List<Integer> ans = new ArrayList<Integer>();
		
		int turn = 0;
		while(turn < 3){
			sel.clear();
			for(int i = 1; i <= N; i++){
				sel.add(i);
			}
			int ret = pack(sel);
			turn++;
		}
		for(int i = 1; i <= N; i++) {
			ans.add(i);	
		}
		report(ans);
	}
};
