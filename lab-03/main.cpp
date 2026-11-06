// ЛР №3. Вариант 8. Условия и циклы.

#include <iostream>
#include <windows.h>

int main()
{
    SetConsoleOutputCP(65001);

    std::cout << "=== Лабораторная работа N3. Вариант 8 ===\n";

    // ---------- Ч1. Логика и short-circuit ----------
    std::cout << "\n=== CH1. Логика и short-circuit ===\n";
    int a, b, c;
    std::cout << "Введите три целых числа (a b c): ";
    if (!(std::cin >> a >> b >> c)) { std::cerr << "Ошибка ввода\n"; return 1; }

    bool allPositive = (a > 0) && (b > 0) && (c > 0);
    bool anyNegative = (a < 0) || (b < 0) || (c < 0);
    bool notAllEqual = !(a == b && b == c);

    std::cout << "Все положительные? " << (allPositive ? "да" : "нет") << "\n";
    std::cout << "Есть отрицательное? " << (anyNegative ? "да" : "нет") << "\n";
    std::cout << "Не все равны? " << (notAllEqual ? "да" : "нет") << "\n";

    std::cout << "a > 1000 && печать: " << ((a > 1000) && (std::cout << "[&& вызов]\n", true)) << "\n";
    std::cout << "a > -1000 && печать: " << ((a > -1000) && (std::cout << "[&& вызов]\n", true)) << "\n";
    std::cout << "a > -1000 || печать: " << ((a > -1000) || (std::cout << "[|| вызов]\n", true)) << "\n";
    std::cout << "a > 1000 || печать: " << ((a > 1000) || (std::cout << "[|| вызов]\n", true)) << "\n";

    // ---------- Ч2. if/else и switch ----------
    std::cout << "\n=== CH2. Условные операторы ===\n";
    int grade;
    std::cout << "Введите оценку (1..5): ";
    if (!(std::cin >> grade)) { std::cerr << "Ошибка ввода\n"; return 1; }

    std::cout << "if/else: ";
    if (grade == 5) std::cout << "отлично\n";
    else if (grade == 4) std::cout << "хорошо\n";
    else if (grade == 3) std::cout << "удовлетворительно\n";
    else if (grade == 2) std::cout << "неудовлетворительно\n";
    else if (grade == 1) std::cout << "очень плохо\n";
    else std::cout << "некорректная оценка\n";

    std::cout << "switch: ";
    switch (grade)
    {
        case 5: std::cout << "отлично\n"; break;
        case 4: std::cout << "хорошо\n"; break;
        case 3: std::cout << "удовлетворительно\n"; break;
        case 2: std::cout << "неудовлетворительно\n"; break;
        case 1: std::cout << "очень плохо\n"; break;
        default: std::cout << "некорректная оценка\n"; break;
    }

    // ---------- Ч3. Первые N простых чисел ----------
    std::cout << "\n=== CH3. Первые N простых чисел ===\n";
    int N;
    std::cout << "Введите N: ";
    if (!(std::cin >> N) || N <= 0) { std::cerr << "Ошибка ввода\n"; return 1; }

    std::cout << "for:   ";
    int found = 0;
    for (int number = 2; found < N; ++number)
    {
        bool prime = true;
        for (int d = 2; d * d <= number; ++d)
        {
            if (number % d == 0) { prime = false; break; }
        }
        if (prime) { std::cout << number << ' '; ++found; }
    }
    std::cout << "\n";

    std::cout << "while: ";
    found = 0;
    int number = 2;
    while (found < N)
    {
        bool prime = true;
        for (int d = 2; d * d <= number; ++d)
        {
            if (number % d == 0) { prime = false; break; }
        }
        if (prime) { std::cout << number << ' '; ++found; }
        ++number;
    }
    std::cout << "\n";

    // ---------- Ч4. Массив: элементы больше среднего ----------
    std::cout << "\n=== CH4. Массив: элементы больше среднего ===\n";
    int arr[10];

    std::cout << "Введите 10 целых чисел: ";
    for (int i = 0; i < 10; ++i)
    {
        if (!(std::cin >> arr[i])) { std::cerr << "Ошибка ввода\n"; return 1; }
    }

    double sum = 0;
    for (int i = 0; i < 10; ++i) sum = sum + arr[i];
    double average = sum / 10;

    int greaterThanAvg = 0;
    for (int i = 0; i < 10; ++i)
        if (arr[i] > average) ++greaterThanAvg;

    std::cout << "Массив: ";
    for (int i = 0; i < 10; ++i) std::cout << arr[i] << ' ';
    std::cout << "\nСреднее: " << average << "\n";
    std::cout << "Больше среднего: " << greaterThanAvg << "\n";

    // ---------- Ч6. Сортировка обменом (пузырьковая) ----------
    std::cout << "\n=== CH6. Сортировка обменом ===\n";
    int copy[10];
    for (int i = 0; i < 10; ++i) copy[i] = arr[i];

    std::cout << "До: ";
    for (int i = 0; i < 10; ++i) std::cout << copy[i] << ' ';
    std::cout << "\n";

    int swapCount = 0;
    for (int i = 0; i < 10 - 1; ++i)
        for (int j = 0; j < 10 - 1 - i; ++j)
            if (copy[j] > copy[j + 1])
            {
                int tmp = copy[j];
                copy[j] = copy[j + 1];
                copy[j + 1] = tmp;
                ++swapCount;
            }

    std::cout << "После: ";
    for (int i = 0; i < 10; ++i) std::cout << copy[i] << ' ';
    std::cout << "\nОбменов: " << swapCount << "\n";

    // ---------- Ч5. Совершенное число ----------
    std::cout << "\n=== CH5. Совершенное число ===\n";
    int M;
    std::cout << "Введите N: ";
    if (!(std::cin >> M)) { std::cerr << "Ошибка ввода\n"; return 1; }

    if (M <= 1) { std::cout << M << " — не совершенное\n"; return 0; }

    long long divisorSum = 1;
    for (int d = 2; d * d <= M; ++d)
    {
        if (M % d == 0)
        {
            divisorSum += d;
            int paired = M / d;
            if (paired != d) divisorSum += paired;
        }
    }

    std::cout << "Сумма делителей: " << divisorSum << "\n";
    std::cout << (divisorSum == M ? "совершенное" : "не совершенное") << "\n";

    return 0;
}