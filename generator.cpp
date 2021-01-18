#include "generator.h"


std::string generator(int length, bool num, bool symbol, bool upper, bool lower, std::string begin) {
    std::string result;

    std::random_device rd;
    std::mt19937 mt(rd());

    // Random generator distribution for the different types of characters
    std::uniform_int_distribution<int> numDist(0, 9);
    std::uniform_int_distribution<int> alphaDist(0, 25);
    std::uniform_int_distribution<int> symbolDist(0, 13);

    // Place the users choice into a std::vector
    std::vector<int> choices = {};
    if (num) {
        choices.push_back(1);
    }
    if (symbol) {
        choices.push_back(2);
    }
    if (upper) {
        choices.push_back(3);
    }
    if (lower) {
        choices.push_back(4);
    }
    // Randomise which type of char we'll get
    std::uniform_int_distribution<int> typeDist(0, choices.size() - 1);

    char lowerCase[26] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z' };
    char upperCase[26] = { 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z' };
    char symbols[14] = { '!', '#', '@', '~', '$', '^', '.', ',', '-', '+', '%', '?', '*', '=' };

    for (int i = 0; i < length; i++) {
        switch(choices[typeDist(mt)]) {
            case 1:
                result += std::to_string(numDist(mt));
                break;
            case 2:
                result += symbols[symbolDist(mt)];
                break;
            case 3:
                result += upperCase[alphaDist(mt)];
                break;
            case 4:
                result += lowerCase[alphaDist(mt)];
                break;
        }
    }
    return (begin + result);
}
