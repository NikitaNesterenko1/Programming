#include <iostream>
using namespace std;

const int k = 12;
const int NUMBERS = 37;
const int COLORS[] = { 0,1,0,1,0,1,0,1,0,1,0,0,1,0,1,0,1,0,1,1,0,1,0,1,0,1,0,1,0,0,1,0,1,0,1,0,1 };

int main() {
	int count[NUMBERS];
	int last_round[NUMBERS];
	for (int b = 0; b < NUMBERS; b++)
		count[b] = last_round[b] = 0;

	int input;
	int round_now = 0;
	int blacks = 0, reds = 0;
	while (++round_now) {
		cin >> input;
		if (input < 0)
			break;

		count[input]++;
		// когда выпало
		last_round[input] = round_now;

		// выпадавших больше всего
		int highest_number = -1;
		for (int b = 0; b < NUMBERS; b++)
			if (count[b] > highest_number)
				highest_number = count[b];

		for (int b = 0; b < NUMBERS; b++)
			if (count[b] == highest_number)
				cout << b << " ";
		cout << endl;

		// не выпавшие или выпавшие более 12 игр назад
		for (int b = 0; b < NUMBERS; b++)
			if (last_round[b] == 0 || (round_now - last_round[b] > k))
				cout << b << " ";
		cout << endl;

		if (input > 0) {
			if (COLORS[input] == 1)
				++reds;
			else
				++blacks;
		}

		cout << reds << " " << blacks << endl << endl;
	}
}