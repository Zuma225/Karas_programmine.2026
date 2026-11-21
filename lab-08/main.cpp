#include <iostream>
#include <vector>
#include <stdexcept>

#ifdef _WIN32
#define NOMINMAX
#include <windows.h>
#endif

using Numbers = std::vector<double>;   // Ч4: псевдоним типа

// ---------- Ч1: чтение в массив фиксированной длины ----------
// (обычный массив, псевдоним тут не нужен — это и есть суть Ч1)
int readFixedArray(double arr[], int arrSize, double stopValue) {
    int count = 0;
    double x;
    while (std::cin >> x && x != stopValue) {
        if (count < arrSize) {
            arr[count] = x;
            count = count + 1;
        } else {
            std::cout << "Массив заполнен, значение " << x << " потеряно\n";
        }
    }
    return count;
}

// ---------- Ч2: чтение без ограничения (Numbers в сигнатуре) ----------
Numbers readNumbers(double stopValue) {
    Numbers v;
    double x;
    while (std::cin >> x && x != stopValue) {
        v.push_back(x);
    }
    return v;
}

// ---------- Ч4: печать (Numbers в сигнатуре) ----------
void printNumbers(const Numbers& v) {
    for (std::size_t i = 0; i < v.size(); i++) {
        std::cout << v[i] << " ";
    }
    std::cout << "\n";
}

// ---------- Ч5 (вариант 4): фильтрация (Numbers в сигнатуре) ----------
Numbers filterMultiplesOfThree(const Numbers& src) {
    Numbers result;
    for (std::size_t i = 0; i < src.size(); i++) {
        int value = static_cast<int>(src[i]);
        if (src[i] == value && value % 3 == 0) {
            result.push_back(src[i]);
        }
    }
    return result;
}

int main() {
#ifdef _WIN32
    SetConsoleOutputCP(65001);   // UTF-8, чтобы не было кракозябр
#endif

    // ================= Ч1 =================
    std::cout << "\n=== Ч1. Массив фиксированной длины ===\n";
    const int arrSize = 5;
    double arr[arrSize];

    std::cout << "Введите числа (0 — конец): ";
    int count = readFixedArray(arr, arrSize, 0);

    std::cout << "Прочитано: " << count << " -> ";
    for (int i = 0; i < count; i++) {
        std::cout << arr[i] << " ";
    }
    std::cout << "\n";

    // ================= Ч2 =================
    std::cout << "\n=== Ч2. Чтение через std::vector ===\n";
    std::cout << "Введите числа (0 — конец): ";

    Numbers nums = readNumbers(0);   // исходная последовательность

    std::cout << "Вектор (size=" << nums.size()
              << ", capacity=" << nums.capacity() << "): ";
    printNumbers(nums);

    // ================= Ч3 =================
    // ВАЖНО: операции Ч3 выполняем на КОПИИ, чтобы nums остался исходным для Ч5
    std::cout << "\n=== Ч3. Операции vector (на копии, nums не трогаем) ===\n";
    Numbers demo = nums;

    std::cout << "size() = " << demo.size() << "\n";

    // at() с выходом за границу
    try {
        double bad = demo.at(demo.size());
        std::cout << "at = " << bad << "\n";
    } catch (const std::out_of_range& e) {
        std::cout << "Поймано std::out_of_range: " << e.what() << "\n";
    }
    std::cout << "operator[] с индексом >= size() границы не проверяет (UB)\n";

    // pop_back()
    if (demo.empty() == false) {
        std::cout << "pop_back(): удаляем " << demo.back() << "\n";
        demo.pop_back();
        std::cout << "После pop_back: ";
        printNumbers(demo);
    }

    // erase()
    if (demo.size() > 1) {
        std::cout << "erase(begin()+1): удаляем " << demo[1] << "\n";
        demo.erase(demo.begin() + 1);
        std::cout << "После erase: ";
        printNumbers(demo);
    }

    // ================= Ч4 =================
    std::cout << "\n=== Ч4. Псевдоним Numbers = std::vector<double> ===\n";
    std::cout << "Псевдоним Numbers использован в сигнатурах функций:\n";
    std::cout << "  - Numbers readNumbers(double)\n";
    std::cout << "  - void printNumbers(const Numbers&)\n";
    std::cout << "  - Numbers filterMultiplesOfThree(const Numbers&)\n";

    // ================= Ч5 (вариант 4) =================
    // Фильтруем ИСХОДНЫЙ nums (не demo), т.к. demo испорчен в Ч3
    std::cout << "\n=== Ч5. Вариант 4: числа, кратные 3 ===\n";

    Numbers filtered = filterMultiplesOfThree(nums);

    std::cout << "Исходный вектор: ";
    printNumbers(nums);

    std::cout << "Кратные 3: ";
    printNumbers(filtered);

    std::cout << "\n=== Все части выполнены ===\n";
    return 0;
}