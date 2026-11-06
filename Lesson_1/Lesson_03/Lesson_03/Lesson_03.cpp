#include <iostream>

using namespace std;

int main() {
	setlocale(LC_ALL, "RU");

/*	// Цикл for
	for (int i = 100; i >= 10; i-= 15) {
		cout << "1. El: " << i << endl;
	}

	// Цикл while
	int j = 100;
	while (j >  60) {
			cout << "2. El: " << j << endl;
			j /= 1.5f;
	}

	// Цикл do while
	int k = 100;
	do {
		cout << "3. El: " << k << endl;
		k -= 10;
	} while (k < 10); */

/*	// Операторы в циклах
	for (int i = 1; i < 15; i++) {
		if (i == 10)
			break;

		if (i % 2 == 0)
			continue;

		cout << "El: " << i << endl;
	}*/

	// Практический пример
	srand(time(NULL));
	int rand_num = 1 + rand() % 15;
	bool stop = false;
	int user_input;
	

	do {
		cout << "Enter number: ";
		cin >> user_input;
		if (user_input != rand_num)
			cout << "Вы не угадали\n";
		else
			stop = true;
	} while (!stop);

	cout << "Вы угадали!";

	return 0;
}