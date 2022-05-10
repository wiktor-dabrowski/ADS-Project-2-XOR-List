#include <iostream>
#include <string>
#include "XOR_List.h"

using namespace std;

int main() {
	XOR_List list;
	string x;
	int n;
	while (cin >> x) {
		if (x == "ACTUAL")
			list.actual();
		else if (x == "NEXT")
			list.next();
		else if (x == "PREV")
			list.prev();

		else if (x == "ADD_BEG") {
			cin >> n;
			list.add_beg(n);
		}
		else if (x == "ADD_END") {
			cin >> n;
			list.add_end(n);
		}
		else if (x == "ADD_ACT") {
			cin >> n;
			list.add_act(n);
		}

		else if (x == "DEL_BEG")
			list.del_beg();
		else if (x == "DEL_END")
			list.del_end();
		else if (x == "DEL_ACT")
			list.del_act();
		else if (x == "DEL_VAL") {
			cin >> n;
			list.del_val(n);
		}

		else if (x == "PRINT_FORWARD")
			list.print_forward();
		else if (x == "PRINT_BACKWARD")
			list.print_backward();

		else if (x == "Q")
			break;
	}

	return 0;
}