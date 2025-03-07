#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <vector>

std::string generatePassword(int length, bool useUppercase, bool useLowercase, bool useDigits, bool useSpecialChars) {
    std::string uppercase = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    std::string lowercase = "abcdefghijklmnopqrstuvwxyz";
    std::string digits = "0123456789";
    std::string specialChars = "!@#$%^&*()-_=+[]{}|;:,.<>?";

    std::string characterPool;

    if (useUppercase) {
        characterPool += uppercase;
    }
    if (useLowercase) {
        characterPool += lowercase;
    }
    if (useDigits) {
        characterPool += digits;
    }
    if (useSpecialChars) {
        characterPool += specialChars;
    }

    if (characterPool.empty()) {
        throw std::invalid_argument("At least one character type must be selected.");
    }

    std::string password;
    srand(static_cast<unsigned int>(time(0)));

    for (int i = 0; i < length; ++i) {
        int index = rand() % characterPool.size();
        password += characterPool[index];
    }

    return password;
}

int main() {
    int length;
    char useUppercase, useLowercase, useDigits, useSpecialChars;

    std::cout << "Введите длину пароля: ";
    std::cin >> length;

    std::cout << "Использовать заглавные буквы? (y/n): ";
    std::cin >> useUppercase;

    std::cout << "Использовать строчные буквы? (y/n): ";
    std::cin >> useLowercase;

    std::cout << "Использовать цифры? (y/n): ";
    std::cin >> useDigits;

    std::cout << "Использовать специальные символы? (y/n): ";
    std::cin >> useSpecialChars;

    try {
        std::string password = generatePassword(length,
                                                useUppercase == 'y',
                                                useLowercase == 'y',
                                                useDigits == 'y',
                                                useSpecialChars == 'y');
        std::cout << "Сгенерированный пароль: " << password << std::endl;
    } catch (const std::invalid_argument& e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }

    return 0;
}