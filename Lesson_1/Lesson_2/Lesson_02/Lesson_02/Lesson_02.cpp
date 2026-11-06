#include <iostream>
#include <time.h>

using namespace std; // std используется автоматом

int main() {
	setlocale(LC_ALL, "RU");

	srand(time(NULL));

	int result = 1 + rand() % 20;
	cout << result << endl;

	float num1, num2, res;
	cout << "Enter num1: ";
	cin >> num1;

	cout << "Enter num2: ";
	cin >> num2;

	char math;
	cout << "Enter math symbol: ";
	cin >> math;

	/*if (math == '+')
		res = num1 + num2;
	else if (math == '-')
		res = num1 - num2;
	else if (math == '*')
		res = num1 * num2;
	else if (math == '/')
		res = num1 / num2;*/

	switch (math) {
	case '+': res = num1 + num2; break;
	case '-': res = num1 - num2; break;
	case '*': res = num1 * num2; break;
	case '/': res = num1 / num2; break;
	default:
		res = 0;
		cerr << "Error";
		break;
	}

	cout << "Result: " << res << endl;

	// ---------
	int a = 10, b = 3, z;
	z = a % b;
	cout << z;

	// Сокращённые операции
	a += 5;
	a++; // Добавляем один
	a--; // Вычитаем единицу

	// Пространство имён



	return 0;
}