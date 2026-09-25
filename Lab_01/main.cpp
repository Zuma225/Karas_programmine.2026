#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <climits>
#include <iomanip>
#include <locale>

#ifdef _WIN32
    #include <windows.h>
#endif

using namespace std;

// ============================================================
//  Настройка кодировки консоли
// ============================================================
static void setupConsole() {
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
#endif
    // Локаль для std::cout (может не сработать на Windows — не критично)
    try {
        locale::global(locale(""));
        cout.imbue(locale(""));
    } catch (...) {
        // игнорируем, если локаль недоступна
    }
}

// ============================================================
//  Числа прописью
// ============================================================

static string digitToWord(short d, bool female = false) {
    static const char* male[]     = {"ноль","один","два","три","четыре",
                                     "пять","шесть","семь","восемь","девять"};
    static const char* femaleArr[]= {"ноль","одна","две","три","четыре",
                                     "пять","шесть","семь","восемь","девять"};
    return female ? femaleArr[d] : male[d];
}

static string teenToWord(short n) { // 10..19
    static const char* words[] = {
        "десять","одиннадцать","двенадцать","тринадцать","четырнадцать",
        "пятнадцать","шестнадцать","семнадцать","восемнадцать","девятнадцать"};
    return words[n - 10];
}

static string tensToWord(short n) { // 20,30,...,90
    static const char* words[] = {"","","двадцать","тридцать","сорок",
        "пятьдесят","шестьдесят","семьдесят","восемьдесят","девяносто"};
    return words[n / 10];
}

static string hundredsToWord(short n) { // 100..900
    static const char* words[] = {"","сто","двести","триста","четыреста",
        "пятьсот","шестьсот","семьсот","восемьсот","девятьсот"};
    return words[n / 100];
}

// Триада 0..999 -> слова
static string triadToWords(int n, bool female) {
    string result;
    short h = static_cast<short>(n / 100);
    short t = static_cast<short>((n / 10) % 10);
    short u = static_cast<short>(n % 10);

    if (h) result += string(hundredsToWord(h)) + " ";

    if (t == 1) {
        result += string(teenToWord(static_cast<short>(n % 100))) + " ";
    } else {
        if (t) result += string(tensToWord(static_cast<short>(t * 10))) + " ";
        if (u) result += digitToWord(u, female) + " ";
    }
    return result;
}

// Склонение: 1 рубль / 2 рубля / 5 рублей
static string pluralForm(long long n, const string& one,
                         const string& few, const string& many) {
    long long m100 = n % 100;
    long long m10  = n % 10;
    if (m100 >= 11 && m100 <= 14) return many;
    if (m10 == 1)                  return one;
    if (m10 >= 2 && m10 <= 4)      return few;
    return many;
}

// Основная функция: копейки -> прописью
static string moneyToWords(long long kopeks) {
    if (kopeks == 0) return "ноль рублей 00 копеек";

    bool negative = kopeks < 0;
    if (negative) kopeks = -kopeks;

    long long rub = kopeks / 100;
    short     kop = static_cast<short>(kopeks % 100);

    string result;
    if (negative) result += "минус ";

    if (rub == 0) {
        result += "ноль рублей ";
    } else {
        // Имена триад в четырёх формах
        static const char* t0[4] = {"", "тысяча", "миллион", "миллиард"};   // 1
        static const char* t2[4] = {"", "тысячи", "миллиона", "миллиарда"}; // 2-4
        static const char* t5[4] = {"", "тысяч", "миллионов", "миллиардов"};// 5-20
        static const bool  female[4] = {false, true, false, false};

        vector<int> triads;
        long long tmp = rub;
        while (tmp > 0) { triads.push_back(static_cast<int>(tmp % 1000)); tmp /= 1000; }

        for (int i = static_cast<int>(triads.size()) - 1; i >= 0; --i) {
            if (triads[i] == 0) continue;
            result += triadToWords(triads[i], female[i]);

            if (i > 0) {
                int t = triads[i];
                int m100 = t % 100, m10 = t % 10;
                const char* form;
                if (m100 >= 11 && m100 <= 14)      form = t5[i];
                else if (m10 == 1)                 form = t0[i];
                else if (m10 >= 2 && m10 <= 4)     form = t2[i];
                else                               form = t5[i];
                result += string(form) + " ";
            }
        }
        result += pluralForm(rub, "рубль", "рубля", "рублей");
    }

    // Копейки
    result += " " + to_string(kop) + " ";
    result += pluralForm(kop, "копейка", "копейки", "копеек");
    return result;
}

// ============================================================
//  Демонстрация проблемы float
// ============================================================

static void demonstrateFloatProblem() {
    cout << "\n=== Почему float/double плохо для денег ===\n";

    float       f  = 0.1f + 0.2f;
    double      d  = 0.1  + 0.2;
    long double ld = 0.1L + 0.2L;

    cout << setprecision(20);
    cout << "float:       0.1 + 0.2 = " << f  << "\n";
    cout << "double:      0.1 + 0.2 = " << d  << "\n";
    cout << "long double: 0.1 + 0.2 = " << ld << "\n";

    float money = 1234.56f;
    cout << "\nfloat money = 1234.56f -> " << money << "\n";
    cout << "(реально хранится ~1234.5599365234...)\n";

    float sum = 0.0f;
    for (int i = 0; i < 100000; ++i) sum += 0.01f;
    cout << "\n100000 * 0.01f = " << sum << " (ожидалось 1000)\n";

    cout << "\nВывод: для денег используем целое (long long) в копейках!\n";
}

// ============================================================
//  Округление до копеек
// ============================================================

static long long roundToKopeks(long double amount) {
    // llroundl округляет по правилам математики (0.5 — вверх по модулю)
    return static_cast<long long>(llroundl(amount * 100.0L));
}

// ============================================================
//  main
// ============================================================

int main() {
    setupConsole();

    demonstrateFloatProblem();

    long double amount;
    cout << "\nВведите сумму в рублях (например, 1234.567): ";
    if (!(cin >> amount)) {
        cerr << "Ошибка: введено не число.\n";
        return 1;
    }

    long long kopeks = roundToKopeks(amount);

    cout << "\n--- Результат ---\n";
    cout << "Введено:             " << static_cast<double>(amount) << "\n";
    cout << "Округлено до копеек: "
         << (kopeks / 100) << "."
         << setfill('0') << setw(2) << (kopeks % 100)
         << setfill(' ') << " руб\n";
    cout << "Прописью: " << moneyToWords(kopeks) << "\n";

    // Работа с типами (для отчёта)
    short     kopShort = static_cast<short>(kopeks % 100);
    int       rubInt   = static_cast<int>(kopeks / 100);
    long long total    = kopeks;

    cout << "\n--- Типы ---\n";
    cout << "short     kopShort = " << kopShort << " (size " << sizeof(short)     << ")\n";
    cout << "int       rubInt   = " << rubInt   << " (size " << sizeof(int)       << ")\n";
    cout << "long long total    = " << total    << " (size " << sizeof(long long) << ")\n";
    cout << "float = "        << sizeof(float)
         << ", double = "      << sizeof(double)
         << ", long double = " << sizeof(long double) << "\n";

    return 0;
}