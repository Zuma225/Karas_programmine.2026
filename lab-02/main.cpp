// ЛР №2. Вариант 13: int32_t / uint32_t, период маятника.
// Весь код — в одном main().

#include <bitset>
#include <cmath>
#include <cstdint>
#include <iostream>
#include <limits>

#ifdef _WIN32
#define NOMINMAX
#include <windows.h>
#endif

int main() {
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
#endif

    const double PI = std::acos(-1.0);
    const double GRAVITY = 9.8;

    // ---- Ч1. Арифметика ----
    std::cout << "=== Ч1. Арифметические операторы ===\n";
    int a = 0, b = 0;
    std::cout << "Введите a и b: ";
    std::cin >> a >> b;

    std::cout << "a + b = " << (a + b) << '\n';
    std::cout << "a - b = " << (a - b) << '\n';
    std::cout << "a * b = " << (a * b) << '\n';

    if (b == 0) {
        std::cerr << "Ошибка: b == 0\n";
        return 1;
    }
    std::cout << "a / b = " << (a / b) << '\n';
    std::cout << "a % b = " << (a % b) << '\n';
    std::cout << "a / b (double) = " << (static_cast<double>(a) / b) << '\n';

    int c = a;
    c += b;
    std::cout << "c = a; c += b; c = " << c << '\n';

    // ---- Ч2. Переполнение ----
    std::cout << "\n=== Ч2. Переполнение int32_t / uint32_t ===\n";
    int32_t sa = 0, sb = 0;
    std::cout << "Два int32_t с суммой вне диапазона: ";
    std::cin >> sa >> sb;

    int64_t sum64 = static_cast<int64_t>(sa) + sb;
    std::cout << "int32_t: " << sa << " + " << sb << " = " << sum64
              << " (в int64_t)\n";
    std::cout << "  Диапазон: [" << std::numeric_limits<int32_t>::min()
              << "; " << std::numeric_limits<int32_t>::max() << "]\n";
    if (sum64 > std::numeric_limits<int32_t>::max() ||
        sum64 < std::numeric_limits<int32_t>::min()) {
        std::cout << "  Не влезает в int32_t — было бы UB\n";
    }

    uint32_t ua = 0, ub = 0;
    std::cout << "Два uint32_t с суммой вне диапазона: ";
    std::cin >> ua >> ub;

    std::cout << "uint32_t: " << ua << " + " << ub << " = " << (ua + ub)
              << " (по модулю 2^32)\n";
    std::cout << "  Диапазон: [0; " << std::numeric_limits<uint32_t>::max()
              << "]\n";

    // ---- Ч3. Биты и bitset ----
    std::cout << "\n=== Ч3. Битовые операции ===\n";
    uint32_t n = 0;
    int k = 0;
    std::cout << "Введите n (uint32_t) и k (0..31): ";
    std::cin >> n >> k;

    if (k < 0 || k > 31) {
        std::cerr << "Ошибка: k вне [0; 31]\n";
        return 1;
    }
    uint32_t mask = static_cast<uint32_t>(k);

    std::cout << "n       = " << std::bitset<32>(n) << '\n';
    std::cout << "n & k   = " << (n & mask) << "  "
              << std::bitset<32>(n & mask) << '\n';
    std::cout << "n | k   = " << (n | mask) << "  "
              << std::bitset<32>(n | mask) << '\n';
    std::cout << "n ^ k   = " << (n ^ mask) << "  "
              << std::bitset<32>(n ^ mask) << '\n';
    std::cout << "~n      = " << (~n) << "  "
              << std::bitset<32>(~n) << '\n';
    std::cout << "n << k  = " << (n << k) << "  "
              << std::bitset<32>(n << k) << '\n';
    std::cout << "n >> k  = " << (n >> k) << "  "
              << std::bitset<32>(n >> k) << '\n';

    std::cout << "Бит " << k << " = " << ((n >> k) & 1u) << '\n';
    bool pow2 = (n != 0) && ((n & (n - 1)) == 0);
    std::cout << "Степень двойки: " << (pow2 ? "да" : "нет") << '\n';

    // ---- Ч4. Преобразование типов ----
    std::cout << "\n=== Ч4. Преобразование типов ===\n";
    int a2 = 0, b2 = 0;
    std::cout << "Введите a и b: ";
    std::cin >> a2 >> b2;

    if (b2 == 0) {
        std::cerr << "Ошибка: b == 0\n";
        return 1;
    }
    std::cout << "a / b           = " << (a2 / b2) << '\n';
    std::cout << "(double)a / b   = " << (static_cast<double>(a2) / b2) << '\n';
    std::cout << "static_cast / b = " << (static_cast<double>(a2) / b2) << '\n';
    std::cout << "static_cast<int>(3.99) = " << static_cast<int>(3.99) << '\n';
    std::cout << "bool -> int: true = " << static_cast<int>(true)
              << ", false = " << static_cast<int>(false) << '\n';

    // ---- Ч5. Маятник ----
    std::cout << "\n=== Ч5. Период маятника ===\n";
    double length = 0.0;
    std::cout << "Введите L (м, > 0): ";
    std::cin >> length;

    if (length <= 0.0) {
        std::cerr << "Ошибка: L <= 0\n";
        return 1;
    }
    double period = 2.0 * PI * std::sqrt(length / GRAVITY);
    std::cout << "T = " << period << " с\n";
    std::cout << "pi = " << PI << '\n';

    return 0;
}