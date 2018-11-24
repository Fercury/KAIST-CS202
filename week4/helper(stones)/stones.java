import java.util.Scanner;
import java.util.ArrayList;
import java.util.List;
import java.util.Iterator;

public class stones {
	static Scanner sc;

	static char weigh (int x, int y) {
		System.out.println("? " + x + " " + y);
		System.out.flush();
		String line = sc.next();
		if(line.compareTo("-202") == 0) {
			System.exit(0);
		}
		return line.charAt(0);
	}

	static void report(List<Integer> minPos, List<Integer> maxPos) {
		System.out.println("!");
		System.out.flush();

		System.out.print(minPos.size());
		Iterator it = minPos.iterator();
		while (it.hasNext()) {
			System.out.print(" " + it.next());
		}
		System.out.println();
		System.out.flush();
		
		System.out.print(maxPos.size());
		it = maxPos.iterator();
		while (it.hasNext()) {
			System.out.print(" " + it.next());
		}
		System.out.println();
		System.out.flush();
	}

	public static void main(String[] args) {
		sc = new Scanner(System.in);

		int T = sc.nextInt();
		for(int test_case_id = 1; test_case_id <= T; test_case_id++) {
			int N = sc.nextInt();
			if(N < 0) {
				return;
			}

			/* IMPLEMENT HERE */
			/* IMPLEMENT HERE */
			/* IMPLEMENT HERE */
			/* IMPLEMENT HERE */
			// Below is an example solution that requires N(N-1) weighings.
			// Don't forget to initialize all global variables.

			List<Integer> minPos = new ArrayList<Integer>();
			List<Integer> maxPos = new ArrayList<Integer>();
			for(int i = 1; i <= N; i++) {
				int cnt_smaller = 0, cnt_larger = 0;
				for(int j = 1; j <= N; j++) {
					if(i != j) {
						switch(weigh(i, j)) {
							case '>': cnt_smaller += 1; break;
							case '<': cnt_larger += 1; break;
						}
					}
				}

				if(cnt_smaller == 0) {
					minPos.add(i);
				}
				if(cnt_larger == 0) {
					maxPos.add(i);
				}
			}

			report(minPos, maxPos);
			/* IMPLEMENT HERE */
			/* IMPLEMENT HERE */
			/* IMPLEMENT HERE */
			/* IMPLEMENT HERE */
			/* IMPLEMENT HERE */
			/* IMPLEMENT HERE */

		}
	}
};