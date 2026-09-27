// ============================================================
//  Лабораторная работа №1, вариант 17
//  Набор типов: short, int, long long, float, double, long double
//  Прикладная задача: перевод денежной суммы прописью
//                     в "рубли и копейки" с округлением до копеек
//  Дополнительно: демонстрация того, почему деньги нельзя
//                 хранить во float
// ============================================================

#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <limits>
#include <climits>
#include <cmath>
#include <cstdint>
#include <locale>

#ifdef _WIN32
    #include <windows.h>
#endif

// ------------------------------------------------------------
//  Настройка консоли (UTF-8), актуально для Windows
// ------------------------------------------------------------
static void setup_console() {
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
#endif
    try {
        std::locale::global(std::locale(""));
    } catch (...) {
        // локаль может быть недоступна — это не критично
    }
}

// ============================================================
//  Ч1. Карта типов
// ============================================================

// Печать строки-разделителя таблицы
static void print_separator() {
    std::cout << std::string(78, '-') << '\n';
}

// Печать информации о целочисленном типе (шаблон)
template <typename T>
static void print_integer_type(const char* name) {
    std::cout << std::left  << std::setw(14) << name
              << std::right << std::setw(6)  << sizeof(T) << " B"
              << std::setw(7) << (sizeof(T) * CHAR_BIT) << " bit"
              << "   min = " << std::setw(22) << +std::numeric_limits<T>::min()
              << "   max = " << std::setw(22) << +std::numeric_limits<T>::max()
              << '\n';
}

// Печать информации о вещественном типе (шаблон)
template <typename T>
static void print_real_type(const char* name) {
    std::cout << std::left  << std::setw(14) << name
              << std::right << std::setw(6)  << sizeof(T) << " B"
              << std::setw(7) << (sizeof(T) * CHAR_BIT) << " bit"
              << "   min    = " << std::setw(24) << std::numeric_limits<T>::min()
              << '\n';
    std::cout << std::string(14, ' ') << std::setw(6) << ""
              << std::setw(7) << ""
              << "   lowest = " << std::setw(24) << std::numeric_limits<T>::lowest()
              << '\n';
    std::cout << std::string(14, ' ') << std::setw(6) << ""
              << std::setw(7) << ""
              << "   max    = " << std::setw(24) << std::numeric_limits<T>::max()
              << '\n';
    std::cout << std::string(14, ' ') << std::setw(6) << ""
              << std::setw(7) << ""
              << "   eps    = " << std::setw(24) << std::numeric_limits<T>::epsilon()
              << "   digits10 = " << std::numeric_limits<T>::digits10
              << '\n';
}

static void part_1_type_map() {
    std::cout << "\n=== Part 1. Type map ===\n";
    std::cout << std::setprecision(10);

    print_separator();
    std::cout << "Integer types:\n";
    print_separator();
    print_integer_type<short>     ("short");
    print_integer_type<int>       ("int");
    print_integer_type<long long> ("long long");

    print_separator();
    std::cout << "Floating-point types:\n";
    print_separator();
    print_real_type<float>       ("float");
    print_real_type<double>      ("double");
    print_real_type<long double> ("long double");
    print_separator();
}

// ============================================================
//  Ч2. Литералы и суффиксы
// ============================================================

static void part_2_literals() {
    std::cout << "\n=== Part 2. Literals and suffixes ===\n";

    // unsigned int (суффикс u) — только неотрицательные значения
    const unsigned int kUnsignedValue = 42u;
    // long long (суффикс LL) — расширенный диапазон
    const long long kLongLongValue = 9'000'000'000LL;
    // float (суффикс f) — иначе литерал был бы double
    const float kFloatValue = 3.14f;
    // шестнадцатеричный литерал
    const int kHexValue = 0xFF;
    // двоичный литерал (C++14)
    const int kBinValue = 0b1010;
    // разделитель разрядов (C++14)
    const int kGroupedValue = 1'000'000;

    std::cout << std::setprecision(10);
    std::cout << "42u            = " << kUnsignedValue
              << "   sizeof = " << sizeof(kUnsignedValue) << '\n';
    std::cout << "9000000000LL   = " << kLongLongValue
              << "   sizeof = " << sizeof(kLongLongValue) << '\n';
    std::cout << "3.14f          = " << kFloatValue
              << "   sizeof = " << sizeof(kFloatValue) << '\n';
    std::cout << "0xFF           = " << kHexValue
              << "   sizeof = " << sizeof(kHexValue) << '\n';
    std::cout << "0b1010         = " << kBinValue
              << "   sizeof = " << sizeof(kBinValue) << '\n';
    std::cout << "1'000'000      = " << kGroupedValue
              << "   sizeof = " << sizeof(kGroupedValue) << '\n';
}

// ============================================================
//  Ч3. Переполнение знаковых и беззнаковых типов
// ============================================================

static void part_3_overflow() {
    std::cout << "\n=== Part 3. Overflow experiment ===\n";

    // Беззнаковый случай: модульная арифметика, поведение определено стандартом
    const unsigned int kMaxUnsigned = std::numeric_limits<unsigned int>::max();
    const unsigned int kUnsignedOverflow = kMaxUnsigned + 1u;
    std::cout << "unsigned int max     = " << kMaxUnsigned << '\n';
    std::cout << "unsigned int max + 1 = " << kUnsignedOverflow
              << "   (wraps to 0, defined behaviour)\n";

    // Знаковый случай: переполнение signed — UB.
    // Чтобы не поймать настоящий UB (компилятор вправе что угодно),
    // демонстрируем поведение через volatile и предупреждаем об этом.
    // Значение получаем так, чтобы компилятор не "свернул" его в константу.
    volatile int signed_max = std::numeric_limits<int>::max();
    int signed_overflow = signed_max + 1;   // UB! только для демонстрации
    std::cout << "int max              = " << std::numeric_limits<int>::max() << '\n';
    std::cout << "int max + 1          = " << signed_overflow
              << "   (undefined behaviour on real signed overflow)\n";

    // Безопасная "эмуляция" того же результата через беззнаковую арифметику
    const unsigned int kEmulatedSignedOverflow =
        static_cast<unsigned int>(std::numeric_limits<int>::max()) + 1u;
    std::cout << "int max + 1 (emulated, well-defined) = "
              << static_cast<int>(kEmulatedSignedOverflow) << '\n';
}

// ============================================================
//  Ч4. Эксперимент с точностью float/double
// ============================================================

static void part_4_precision() {
    std::cout << "\n=== Part 4. Precision experiment ===\n";
    std::cout << std::setprecision(20);

    const float  kF  = 0.1f + 0.2f;
    const double kD  = 0.1  + 0.2;
    const long double kLD = 0.1L + 0.2L;

    std::cout << "0.1f + 0.2f = " << kF  << "   (expected 0.3)\n";
    std::cout << "0.1  + 0.2  = " << kD  << "   (expected 0.3)\n";
    std::cout << "0.1L + 0.2L = " << kLD << "   (expected 0.3)\n";

    // Потеря точности при хранении денежной суммы во float
    const float kFloatMoney = 1234.56f;
    std::cout << "\nfloat money = 1234.56f -> " << kFloatMoney << '\n';

    // Накопление ошибки: 100000 раз прибавляем 0.01f
    float sum = 0.0f;
    for (int i = 0; i < 100000; ++i) {
        sum += 0.01f;
    }
    std::cout << "100000 * 0.01f = " << sum << "   (expected 1000)\n";

    // А теперь то же самое, но в копейках (long long) — точно
    long long kopeks = 0;
    for (int i = 0; i < 100000; ++i) {
        kopeks += 1;
    }
    std::cout << "100000 * 1 kopeck = " << kopeks
              << " kop. = " << (kopeks / 100) << " rub  (exact)\n";
}

// ============================================================
//  Ч5. Прикладная задача: сумма прописью + округление до копеек
// ============================================================

// --- 5.1. Словари для чисел прописью (английский) ---

static std::string digit_to_word(int d, bool female) {
    // В английском male/female формы совпадают, но параметр оставлен
    // для единообразия с русской версией и на случай расширения.
    static const char* words[] = {
        "zero","one","two","three","four",
        "five","six","seven","eight","nine"
    };
    (void)female;
    return words[d];
}

static std::string teen_to_word(int n) { // 10..19
    static const char* words[] = {
        "ten","eleven","twelve","thirteen","fourteen",
        "fifteen","sixteen","seventeen","eighteen","nineteen"
    };
    return words[n - 10];
}

static std::string tens_to_word(int n) { // 20,30,...,90
    static const char* words[] = {
        "","","twenty","thirty","forty",
        "fifty","sixty","seventy","eighty","ninety"
    };
    return words[n / 10];
}

static std::string hundreds_to_word(int n) { // n = 0..999, берётся n / 100
    static const char* words[] = {
        "","one hundred","two hundred","three hundred","four hundred",
        "five hundred","six hundred","seven hundred","eight hundred","nine hundred"
    };
    return words[n / 100];
}

// --- 5.2. Триада 0..999 -> слова ---

static std::string triad_to_words(int n, bool female) {
    std::string result;

    const int h = n / 100;
    const int t = (n / 10) % 10;
    const int u = n % 10;

    if (h) result += hundreds_to_word(n) + " ";

    if (t == 1) {
        result += teen_to_word(n % 100) + " ";
    } else {
        if (t) result += tens_to_word(t * 10) + " ";
        if (u) result += digit_to_word(u, female) + " ";
    }
    return result;
}

// --- 5.3. Склонение: 1 ruble / 2 rubles / 5 rubles ---

static std::string plural_form(long long n,
                               const std::string& one,
                               const std::string& few,
                               const std::string& many) {
    const long long m100 = n % 100;
    const long long m10  = n % 10;

    if (m100 >= 11 && m100 <= 14) return many;
    if (m10 == 1)                 return one;
    if (m10 >= 2 && m10 <= 4)     return few;
    return many;
}

// --- 5.4. Основная функция: копейки -> "X rubles Y kopecks" ---

static std::string money_to_words(long long kopeks) {
    if (kopeks == 0) return "zero rubles 00 kopecks";

    bool negative = kopeks < 0;
    if (negative) kopeks = -kopeks;

    const long long rub = kopeks / 100;
    const int       kop = static_cast<int>(kopeks % 100);

    std::string result;
    if (negative) result += "minus ";

    if (rub == 0) {
        result += "zero rubles ";
    } else {
        // Имена триад: 1 / 2-4 / 5-20; только "thousand" имеет женский род
        static const char* t_one [4] = {"", "thousand", "million",  "billion" };
        static const char* t_few [4] = {"", "thousands","millions", "billions"};
        static const char* t_many[4] = {"", "thousands","millions", "billions"};

        std::vector<int> triads;
        long long tmp = rub;
        while (tmp > 0) {
            triads.push_back(static_cast<int>(tmp % 1000));
            tmp /= 1000;
        }

        for (int i = static_cast<int>(triads.size()) - 1; i >= 0; --i) {
            if (triads[i] == 0) continue;

            // Только разряд тысяч имеет женский род (i == 1)
            const bool is_female = (i == 1);
            result += triad_to_words(triads[i], is_female);

            if (i > 0) {
                const int t    = triads[i];
                const int m100 = t % 100;
                const int m10  = t % 10;

                const char* form;
                if (m100 >= 11 && m100 <= 14)  form = t_many[i];
                else if (m10 == 1)             form = t_one [i];
                else if (m10 >= 2 && m10 <= 4) form = t_few [i];
                else                           form = t_many[i];

                result += std::string(form) + " ";
            }
        }
        result += plural_form(rub, "ruble", "rubles", "rubles");
    }

    // Копейки
    result += " " + std::to_string(kop) + " ";
    result += plural_form(kop, "kopeck", "kopecks", "kopecks");
    return result;
}

// --- 5.5. Округление вещественной суммы до копеек ---
// Используем long double + llroundl, чтобы не накапливать ошибку double.
static long long round_to_kopeks(long double amount) {
    return static_cast<long long>(std::llroundl(amount * 100.0L));
}

static int part_5_money() {
    std::cout << "\n=== Part 5. Money to words ===\n";

    std::cout << "Enter the amount in rubles (e.g., 1234.567): ";

    // Читаем как long double: точнее, чем double, и его можно
    // аккуратно округлить до копеек через llroundl.
    long double amount = 0.0L;
    if (!(std::cin >> amount)) {
        std::cerr << "Error: a non-numeric value was entered.\n";
        return 1;
    }

    // Ограничение: отрицательную сумму для задачи "деньги" считаем
    // недопустимой (по аналогии с отрицательным радиусом в примере).
    if (amount < 0.0L) {
        std::cerr << "Error: the amount must be non-negative.\n";
        return 1;
    }

    // Переводим в копейки как целое — это правильное хранение денег.
    const long long kopeks = round_to_kopeks(amount);

    const long long rub = kopeks / 100;
    const int       kop = static_cast<int>(kopeks % 100);

    std::cout << "\n--- Result ---\n";
    std::cout << "Introduced:                     "
              << static_cast<double>(amount) << '\n';
    std::cout << "Rounded to the nearest kopeck:  "
              << rub << '.'
              << std::setfill('0') << std::setw(2) << kop
              << std::setfill(' ') << " rub\n";
    std::cout << "In words: "
              << money_to_words(kopeks) << '\n';

    // Демонстрация: то же число во float теряет точность
    const float as_float = static_cast<float>(amount);
    std::cout << "\nFor comparison, stored as float: "
              << std::setprecision(20) << as_float << '\n';

    std::cout << std::setprecision(10);
    return 0;
}

// ============================================================
//  main
// ============================================================

int main() {
    setup_console();

    part_1_type_map();
    part_2_literals();
    part_3_overflow();
    part_4_precision();

    const int rc = part_5_money();
    if (rc != 0) return rc;

    std::cout << "\nAll parts completed successfully.\n";
    return 0;
}