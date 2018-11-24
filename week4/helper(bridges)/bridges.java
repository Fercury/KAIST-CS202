import java.util.Scanner;
import java.util.ArrayList;
import java.util.List;
import java.util.Iterator;

public class bridges {
	static Scanner sc;

	static int sail (int a, int b) {
		System.out.println("? " + a + " " + b);
		System.out.flush();
		int ret = sc.nextInt();
		if(ret == -202) {
			System.exit(0);
		}
		return ret;
	}

	static void report(List<Integer> p, List<Integer> q) {
		// WARNING: p.size() == q.size() should hold.

		System.out.println("!");
		System.out.flush();

		System.out.println(p.size());
		System.out.flush();

		Iterator it1 = p.iterator();
		Iterator it2 = q.iterator();
		while (it1.hasNext()) {
			System.out.println(it1.next() + " " + it2.next());
			System.out.flush();
		}
	}

	public static void main(String[] args) {
		sc = new Scanner(System.in);

		int N = sc.nextInt();

		/* IMPLEMENT HERE */
		/* IMPLEMENT HERE */
		/* IMPLEMENT HERE */
		/* IMPLEMENT HERE */
		// Below is WRONG. It assumes every bridge connects (i, i).

		List<Integer> p = new ArrayList<Integer>();
		List<Integer> q = new ArrayList<Integer>();
		for(int i = 1; i <= N; i++) {
			if(sail(i, i) == -1) {
				p.add(i);
				q.add(i);
			}
		}

		report(p, q);
		/* IMPLEMENT HERE */
		/* IMPLEMENT HERE */
		/* IMPLEMENT HERE */
		/* IMPLEMENT HERE */
		/* IMPLEMENT HERE */
		/* IMPLEMENT HERE */
	}
};