// Лабораторная работа № 3. Условия и циклы.
// Вариант 8.
// Ч3: первые N простых чисел.
// Ч4: количество элементов массива, больших среднего арифметического.
// Ч5: проверка, является ли число N совершенным.

#include <iostream>
#include <cmath>
#include <windows.h>

// ============================================================
// Вспомогательные функции
// ============================================================

// Функция с побочным эффектом — печатает сообщение при вызове.
// Нужна для демонстрации short-circuit evaluation в части Ч1.
bool sideEffect(const char* name)
{
    std::cout << "  [вызвана функция " << name << "]\n";
    return true;
}

// Проверка числа на простоту: перебор делителей до sqrt(n).
bool isPrime(int n)
{
    if (n < 2) return false;
    if (n == 2) return true;
    if (n % 2 == 0) return false;
    // Идём только по нечётным делителям до sqrt(n).
    for (int d = 3; d * d <= n; d += 2)
    {
        if (n % d == 0) return false;
    }
    return true;
}

// ============================================================
// Ч1. Логика и short-circuit
// ============================================================
void part1Logic()
{
    std::cout << "\n===== Ч1. Логика и short-circuit =====\n";

    int a, b, c;
    std::cout << "Введите три целых числа (a b c): ";
    std::cin >> a >> b >> c;

    // Логические операторы на сравнениях.
    bool allPositive  = (a > 0) && (b > 0) && (c > 0);
    bool anyNegative  = (a < 0) || (b < 0) || (c < 0);
    bool notAllEqual  = !(a == b && b == c);

    std::cout << "Все числа положительные?         " << (allPositive ? "да" : "нет") << "\n";
    std::cout << "Есть хотя бы одно отрицательное? " << (anyNegative ? "да" : "нет") << "\n";
    std::cout << "Не все числа равны между собой?  " << (notAllEqual ? "да" : "нет") << "\n";

    // Демонстрация short-circuit evaluation.
    std::cout << "\n--- Демонстрация short-circuit ---\n";

    // Случай 1: левый операнд && ложный -> правый НЕ вызовется.
    std::cout << "Случай a > 1000 && sideEffect(\"правая часть &&\"):\n";
    bool r1 = (a > 1000) && sideEffect("правая часть &&");
    std::cout << "  результат: " << (r1 ? "true" : "false") << "\n";

    // Случай 2: левый операнд && истинный -> правый вызовется.
    std::cout << "Случай a > -1000 && sideEffect(\"правая часть &&\"):\n";
    bool r2 = (a > -1000) && sideEffect("правая часть &&");
    std::cout << "  результат: " << (r2 ? "true" : "false") << "\n";

    // Случай 3: левый операнд || истинный -> правый НЕ вызовется.
    std::cout << "Случай a > -1000 || sideEffect(\"правая часть ||\"):\n";
    bool r3 = (a > -1000) || sideEffect("правая часть ||");
    std::cout << "  результат: " << (r3 ? "true" : "false") << "\n";

    // Случай 4: левый операнд || ложный -> правый вызовется.
    std::cout << "Случай a > 1000 || sideEffect(\"правая часть ||\"):\n";
    bool r4 = (a > 1000) || sideEffect("правая часть ||");
    std::cout << "  результат: " << (r4 ? "true" : "false") << "\n";
}

// ============================================================
// Ч2. Условные операторы: if/else и switch
// ============================================================
void part2Conditions()
{
    std::cout << "\n===== Ч2. Условные операторы =====\n";

    int grade;
    std::cout << "Введите школьную оценку (1..5): ";
    std::cin >> grade;

    // --- Вариант 1: цепочка if/else ---
    std::cout << "Через if/else: ";
    if (grade == 5)
        std::cout << "отлично\n";
    else if (grade == 4)
        std::cout << "хорошо\n";
    else if (grade == 3)
        std::cout << "удовлетворительно\n";
    else if (grade == 2)
        std::cout << "неудовлетворительно\n";
    else if (grade == 1)
        std::cout << "очень плохо\n";
    else
        std::cout << "некорректная оценка\n";

    // --- Вариант 2: switch ---
    // Читаемость: switch чуть компактнее для дискретных значений,
    // но требует break в каждом case, иначе «проваливание».
    std::cout << "Через switch: ";
    switch (grade)
    {
        case 5: std::cout << "отлично\n";               break;
        case 4: std::cout << "хорошо\n";                break;
        case 3: std::cout << "удовлетворительно\n";     break;
        case 2: std::cout << "неудовлетворительно\n";   break;
        case 1: std::cout << "очень плохо\n";           break;
        default: std::cout << "некорректная оценка\n";  break;
    }
    // Комментарий: для диапазонов («оценка >= 4») if/else удобнее,
    // а для фиксированного набора значений switch читается нагляднее.
}

// ============================================================
// Ч3. Циклы: первые N простых чисел (for и while)
// ============================================================
void part3Loops()
{
    std::cout << "\n===== Ч3. Первые N простых чисел =====\n";

    int N;
    std::cout << "Введите N (сколько простых чисел вывести): ";
    std::cin >> N;

    if (N <= 0)
    {
        std::cout << "N должно быть положительным.\n";
        return;
    }

    // --- Способ 1: for ---
    std::cout << "Через for:   ";
    {
        int found = 0;
        for (int number = 2; found < N; ++number)
        {
            if (isPrime(number))
            {
                std::cout << number << " ";
                ++found;
            }
        }
        std::cout << "\n";
    }

    // --- Способ 2: while ---
    std::cout << "Через while: ";
    {
        int found = 0;
        int number = 2;
        while (found < N)
        {
            if (isPrime(number))
            {
                std::cout << number << " ";
                ++found;
            }
            ++number;
        }
        std::cout << "\n";
    }
}

// ============================================================
// Ч4. Массив: количество элементов больше среднего
// ============================================================
void part4Array()
{
    std::cout << "\n===== Ч4. Массив: элементы больше среднего =====\n";

    const int SIZE = 10;
    int arr[SIZE];

    // Заполняем массив вводом с клавиатуры.
    std::cout << "Введите " << SIZE << " целых чисел:\n";
    for (int i = 0; i < SIZE; ++i)
    {
        std::cout << "  элемент[" << i << "] = ";
        std::cin >> arr[i];
    }

    // Считаем сумму и среднее.
    double sum = 0.0;
    for (int i = 0; i < SIZE; ++i)
    {
        sum += arr[i];
    }
    double average = sum / SIZE;

    // Считаем, сколько элементов строго больше среднего.
    int greaterThanAvg = 0;
    for (int i = 0; i < SIZE; ++i)
    {
        if (arr[i] > average)
            ++greaterThanAvg;
    }

    std::cout << "Массив: ";
    for (int i = 0; i < SIZE; ++i)
        std::cout << arr[i] << " ";
    std::cout << "\n";
    std::cout << "Среднее арифметическое: " << average << "\n";
    std::cout << "Элементов больше среднего: " << greaterThanAvg << "\n";

    // --- Ч6. Сортировка обменом (пузырьковая) ---
    std::cout << "\n===== Ч6. Сортировка обменом =====\n";

    int copy[SIZE];
    for (int i = 0; i < SIZE; ++i)
        copy[i] = arr[i];

    std::cout << "До сортировки:  ";
    for (int i = 0; i < SIZE; ++i)
        std::cout << copy[i] << " ";
    std::cout << "\n";

    int swapCount = 0;
    for (int i = 0; i < SIZE - 1; ++i)
    {
        for (int j = 0; j < SIZE - 1 - i; ++j)
        {
            if (copy[j] > copy[j + 1])
            {
                int tmp = copy[j];
                copy[j] = copy[j + 1];
                copy[j + 1] = tmp;
                ++swapCount; // счётчик строго в месте обмена
            }
        }
    }

    std::cout << "После сортировки: ";
    for (int i = 0; i < SIZE; ++i)
        std::cout << copy[i] << " ";
    std::cout << "\n";
    std::cout << "Количество обменов: " << swapCount << "\n";
}

// ============================================================
// Ч5. Совершенное число
// ============================================================
void part5Perfect()
{
    std::cout << "\n===== Ч5. Проверка на совершенное число =====\n";

    int N;
    std::cout << "Введите натуральное число N: ";
    std::cin >> N;

    if (N <= 1)
    {
        std::cout << "Число " << N << " не является совершенным.\n";
        return;
    }

    // Сумма собственных делителей (без самого числа).
    long long divisorSum = 1; // 1 — всегда собственный делитель для N > 1
    for (int d = 2; d * d <= N; ++d)
    {
        if (N % d == 0)
        {
            divisorSum += d;
            int paired = N / d;
            if (paired != d)
                divisorSum += paired;
        }
    }

    std::cout << "Сумма собственных делителей числа " << N
              << " равна " << divisorSum << "\n";

    if (divisorSum == N)
        std::cout << "Число " << N << " — совершенное.\n";
    else
        std::cout << "Число " << N << " — не совершенное.\n";
}

// ============================================================
// Точка входа
// ============================================================
int main()
{
    SetConsoleOutputCP(65001); // переключаем вывод консоли в UTF-8

    std::cout << "Лабораторная работа №3. Вариант 8.\n";

    part1Logic();
    part2Conditions();
    part3Loops();
    part4Array();
    part5Perfect();

    std::cout << "\nГотово.\n";
    return 0;
}