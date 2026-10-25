#include <iostream>
#include <string>
#include <locale.h>

int main() {
    setlocale(LC_ALL, "Russian");

    std::cout << "Привет, как тебя зовут?";
    std::string name;
    std::getline(std::cin, name);

    std::cout << "А сколько тебе лет?";
    std::string age;
    std::cin >> age;

    std::cout << "Хорошо, а какой язык программирования ты любишь?";
    std::string language;
    std::getline(std::cin, language);

    return 0;
}