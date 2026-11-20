#include <iostream>
#include <vector>
#include <stdexcept>

#ifdef _WIN32
#include <windows.h>
#endif

using Numbers = std::vector<double>;   // Ч4: псевдоним типа

int main() {
#ifdef _WIN32
    SetConsoleOutputCP(65001);   // UTF-8, чтобы не было кракозябр
#endif

    // ================= Ч1 =================
    std::cout << "\n=== Ч1. Массив фиксированной длины ===\n";
    const int size = 5;
    double arr[size];
    int count = 0;
    double x;

    std::cout << "Введите числа (0 — конец): ";
    while (std::cin >> x && x != 0) {
        if (count < size) {
            arr[count] = x;
            count = count + 1;
        } else {
            std::cout << "Массив заполнен, значение " << x << " потеряно\n";
        }
    }

    std::cout << "Прочитано: " << count << " -> ";
    for (int i = 0; i < count; i++) {
        std::cout << arr[i] << " ";
    }
    std::cout << "\n";

    std::cin.clear();

    // ================= Ч2 =================
    std::cout << "\n=== Ч2. Чтение через std::vector ===\n";
    Numbers nums;   // используем псевдоним

    std::cout << "Введите числа (0 — конец): ";
    while (std::cin >> x && x != 0) {
        nums.push_back(x);
    }

    std::cout << "Вектор (size=" << nums.size()
              << ", capacity=" << nums.capacity() << "): ";
    for (std::size_t i = 0; i < nums.size(); i++) {
        std::cout << nums[i] << " ";
    }
    std::cout << "\n";

    // ================= Ч3 =================
    std::cout << "\n=== Ч3. Операции vector ===\n";

    std::cout << "size() = " << nums.size() << "\n";

    // at() с выходом за границу
    try {
        double bad = nums.at(nums.size());
        std::cout << "at = " << bad << "\n";
    } catch (const std::out_of_range& e) {
        std::cout << "Поймано std::out_of_range: " << e.what() << "\n";
    }
    std::cout << "operator[] границы не проверяет (UB)\n";

    // pop_back()
    if (nums.empty() == false) {
        std::cout << "pop_back(): удаляем " << nums.back() << "\n";
        nums.pop_back();
        std::cout << "После pop_back: ";
        for (std::size_t i = 0; i < nums.size(); i++) {
            std::cout << nums[i] << " ";
        }
        std::cout << "\n";
    }

    // erase()
    if (nums.size() > 1) {
        std::cout << "erase(begin()+1): удаляем " << nums[1] << "\n";
        nums.erase(nums.begin() + 1);
        std::cout << "После erase: ";
        for (std::size_t i = 0; i < nums.size(); i++) {
            std::cout << nums[i] << " ";
        }
        std::cout << "\n";
    }

    // ================= Ч4 =================
    std::cout << "\n=== Ч4. Псевдоним Numbers = std::vector<double> ===\n";
    std::cout << "Псевдоним Numbers использован для вектора nums\n";

    // ================= Ч5 (вариант 4) =================
    std::cout << "\n=== Ч5. Вариант 4: числа, кратные 3 ===\n";
    Numbers filtered;   // снова псевдоним

    for (std::size_t i = 0; i < nums.size(); i++) {
        // проверяем, что число целое и делится на 3
        int value = static_cast<int>(nums[i]);
        if (nums[i] == value && value % 3 == 0) {
            filtered.push_back(nums[i]);
        }
    }

    std::cout << "Исходный вектор: ";
    for (std::size_t i = 0; i < nums.size(); i++) {
        std::cout << nums[i] << " ";
    }
    std::cout << "\n";

    std::cout << "Кратные 3: ";
    for (std::size_t i = 0; i < filtered.size(); i++) {
        std::cout << filtered[i] << " ";
    }
    std::cout << "\n";

    std::cout << "\n=== Все части выполнены ===\n";
    return 0;
}