#include <iostream>
using namespace std;

int main() {
	int month, day;
	scanf("%d-%d", &month, &day);
	switch(month){
		case 8:
			if (day == 31)
				cout << "YES";
			else
				cout << "NO";
			break;
		case 9:
			if (day == 7 || day == 14 || day ==28)
				cout << "YES";
			else
				cout << "NO";
			break;
		case 10:
			if (day == 5 || day == 12 || day ==26)
				cout << "YES";
			else
				cout << "NO";
			break;
		case 11:
			if (day == 9 || day == 16 || day == 23 || day == 30)
				cout << "YES";
			else
				cout << "NO";
			break;
		default:
			cout << "NO";
	}
	return 0;
}