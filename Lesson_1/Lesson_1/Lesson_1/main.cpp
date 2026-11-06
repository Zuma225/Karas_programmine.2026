#include <iostream>

int main() {
	setlocale(LC_ALL, "RU");
	/*

	int a, b;
	std::cout << "Введите переменную a: ";
	std::cin >> a;

	std::cout << "Введите переменную b: ";
	std::cin >> b;

	std::cout << "A: " << a << ". B: " << b;

	// Типыы данных
	short num1 = 7; // 2 byte / -32K до 32К
	int num2 = 5; // 4 byte / -2B  2B
	long num3 = 10; // 8 byte /

	unsigned short num1_1 = 7; // 2 byte / 64K
	unsigned int num2_1 = 5; // 4 byte / 4B
	unsigned long num3_1 = 10; // 8 byte /

	// Числа с точкой
	float num4 = 56.123f;
	double num5 = 73.454657f;

	// Хранение символа
	char sym = 'q';

	//
	bool isHappy = true;


	// Условия

	int num;
	std::cout << "Введите число: ";
	std::cin >> num;

	bool is_has_car = true;
	if (num >= 3 && is_has_car == true) {
		std::cout << "Число у нас больше 2\n";
		if (num == 5) {
			std::cout << "Число = 5";
		}
	}
	else if (num > 0) {
		std::cout << "Число < 3 и > 0";
	}
	else {
		std::cout << "Число у нас меньше 3\n";

	}
	*/

	int num;
	std::cin >> num;

	switch (num) {
	case 5:
		std::cout << "Num if 5";
		break;
	case 50:
		std::cout << "Num if 50";
		break;
	default:
		std::cout << "Нет подходящего значения";
		break;
	}

	return 0;