// Лабораторная работа № 2. Операторы, биты, преобразования типов.
// Вариант 13: тип int32_t/uint32_t (Ч2), период малых колебаний
// математического маятника T = 2*pi*sqrt(L/g) (Ч5).

#include <bitset>
#include <cmath>
#include <cstdint>
#include <iostream>
#include <limits>

namespace {

// Точное значение числа pi, переносимо между компиляторами.
const double PI = std::acos(-1.0);

// Ускорение свободного падения, м/с^2. Не меняется в ходе программы.
const double GRAVITY = 9.8;

// Проверка, является ли беззнаковое число степенью двойки.
bool IsPowerOfTwo(std::uint32_t value) {
    return value != 0 && (value & (value - 1)) == 0;
}

// Вывод разделителя для читаемости секций.
void PrintHeader(const char* title) {
    std::cout << "\n===== " << title << " =====\n";
}

}  // namespace

int main() {
    // ---------- Ч1. Арифметические операторы ----------
    PrintHeader("Ch1. Arithmetic operators");

    int a = 0;
    int b = 0;
    std::cout << "Enter two integers a and b: ";
    std::cin >> a >> b;

    if (b == 0) {
        std::cerr << "Error: b must not be zero for division and remainder.\n";
        return 1;
    }

    std::cout << "a + b = " << a + b << '\n';
    std::cout << "a - b = " << a - b << '\n';
    std::cout << "a * b = " << a * b << '\n';
    std::cout << "a / b (integer) = " << a / b << '\n';
    std::cout << "a % b = " << a % b << '\n';
    // Вещественное деление: одно из слагаемых явно приводим к double.
    std::cout << "a / b (double)  = "
              << static_cast<double>(a) / static_cast<double>(b) << '\n';

    // Демонстрация составного оператора.
    int compound = a;
    compound += b;
    std::cout << "a += b -> " << compound << '\n';

    // ---------- Ч2. Переполнение ----------
    PrintHeader("Ch2. Overflow (int32_t / uint32_t)");

    std::int32_t signed_value = 0;
    std::uint32_t unsigned_value = 0;
    std::cout << "Enter value for int32_t and uint32_t: ";
    std::cin >> signed_value >> unsigned_value;

    std::cout << "int32_t max = " << std::numeric_limits<std::int32_t>::max()
              << ", min = " << std::numeric_limits<std::int32_t>::min() << '\n';
    std::cout << "uint32_t max = " << std::numeric_limits<std::uint32_t>::max()
              << '\n';

    // Знаковое переполнение — UB; здесь демонстрируем через беззнаковый
    // эквивалент, чтобы поведение было предсказуемым и объяснимым.
    std::uint32_t wrapped = unsigned_value * 2u;
    std::cout << "unsigned * 2 (wraps modulo 2^32) = " << wrapped << '\n';

    // Явно показываем модульную арифметику: сумма с максимумом.
    std::uint32_t sum_wrap =
        unsigned_value + std::numeric_limits<std::uint32_t>::max();
    std::cout << "unsigned + UINT32_MAX (wraps) = " << sum_wrap << '\n';

    // Знаковое переполнение опасно тем, что это UB: результат не определён
    // стандартом. Продемонстрируем аккуратно через int64_t и приведение.
    std::int64_t big = static_cast<std::int64_t>(signed_value) * 2;
    std::cout << "int64 intermediate = " << big
              << " (compare with int32 range)\n";

    // ---------- Ч3. Битовые операции и bitset ----------
    PrintHeader("Ch3. Bitwise operators and std::bitset");

    std::uint32_t n = 0;
    unsigned k = 0;
    std::cout << "Enter non-negative n (uint32_t) and shift k (0..31): ";
    std::cin >> n >> k;

    if (k > 31) {
        std::cerr << "Error: k must be in range 0..31.\n";
        return 1;
    }

    std::bitset<32> bits_n(n);
    std::cout << "n as bitset: " << bits_n << '\n';

    std::cout << "n & k = " << (n & k) << " | bitset: "
              << std::bitset<32>(n & k) << '\n';
    std::cout << "n | k = " << (n | k) << " | bitset: "
              << std::bitset<32>(n | k) << '\n';
    std::cout << "n ^ k = " << (n ^ k) << " | bitset: "
              << std::bitset<32>(n ^ k) << '\n';
    std::cout << "~n    = " << (~n) << " | bitset: "
              << std::bitset<32>(~n) << '\n';
    std::cout << "n << k = " << (n << k) << " | bitset: "
              << std::bitset<32>(n << k) << '\n';
    std::cout << "n >> k = " << (n >> k) << " | bitset: "
              << std::bitset<32>(n >> k) << '\n';

    // Значение конкретного бита с индексом k через сдвиг и &.
    std::uint32_t bit_k = (n >> k) & 1u;
    std::cout << "bit #" << k << " of n = " << bit_k << '\n';

    // Проверка степени двойки.
    std::cout << "n is power of two: " << std::boolalpha
              << IsPowerOfTwo(n) << '\n';

    // ---------- Ч4. Преобразование типов ----------
    PrintHeader("Ch4. Type conversion");

    if (b == 0) {
        std::cerr << "Error: b must not be zero for division.\n";
        return 1;
    }

    // Целочисленное деление без приведения.
    std::cout << "a / b (no cast)            = " << a / b << '\n';
    // C-style приведение.
    std::cout << "a / b (C-style cast)       = "
              << (double)a / b << '\n';
    // static_cast — предпочтительный вариант.
    std::cout << "a / b (static_cast)        = "
              << static_cast<double>(a) / b << '\n';

    // ---------- Ч5. Прикладная задача ----------
    PrintHeader("Ch5. Period of a mathematical pendulum");

    double length = 0.0;
    std::cout << "Enter pendulum length L (m, > 0): ";
    std::cin >> length;

    if (length <= 0.0) {
        std::cerr << "Error: length must be positive.\n";
        return 1;
    }

    const double period = 2.0 * PI * std::sqrt(length / GRAVITY);
    std::cout << "T = " << period << " s\n";

    return 0;
}