#include <string>
#include <iostream>
#include <fstream>

class Second {
    public:

    int getGameNumber(std::string &s, int length) {
        for(int i = 0; i < length; i++) {
            if(isspace(s[i])) {
                std::string numberString = "";
                for(int j = i+1; j < length; j++) {
                    if(isdigit(s[j])) {
                        numberString += s[j];
                    } else {
                        return std::stoi(numberString, nullptr);
                    }
                }
            }
        }
        return -1;
    }

    bool gamePossible(std::string &s, int length) {
        size_t index = s.find_first_of(':');
        for(int i = index; i < length; i++) {
            if(isdigit(s[i]) && isdigit(s[i+1])) {
                std::string numberString = "";
                char color = s[i+3];
                numberString += s[i];
                numberString += s[i+1];
                int number = std::stoi(numberString);
                if(number > 12 && color == 'r') {
                    return false;
                }
                if(number > 13 && color == 'g') {
                    return false;
                }
                if(number > 14 && color == 'b') {
                    return false;
                }
            }
        }
        return true;
    }

    int getMinimumOfColors(std::string &s, int length) {
        size_t index = s.find_first_of(':');
        int minRed = 0;
        int minBlue = 0;
        int minGreen = 0;
        for(int i = index; i < length; i++) {
            std::string numberString = "";
            if(isdigit(s[i])) {
                numberString += s[i];
                int currentNumber = 0;
                char color;
                if(isdigit(s[i+1])) {
                    numberString += s[i+1];
                    currentNumber = std::stoi(numberString);
                    color = s[i+3];
                } else {
                    currentNumber = std::stoi(numberString);
                    color = s[i+2];
                }
                if(color == 'r' && currentNumber > minRed) {
                    minRed = currentNumber;
                }
                if(color == 'g' && currentNumber > minGreen) {
                    minGreen = currentNumber;
                }
                if(color == 'b' && currentNumber > minBlue) {
                    minBlue = currentNumber;
                }
            }
        }
        return minRed * minBlue * minGreen;
    }
};

int main() {
    Second sec = Second();
    std::string string = "Game 3: 8 green, 6 blue, 20 red; 5 blue, 4 red, 13 green; 5 green, 1 red";
    int length = string.length();
    std::ifstream file("input");
    std::string str;
    int result = 0;
    int power = sec.getMinimumOfColors(string, length);
    std::cout << power << std::endl;
    int powerSum = 0;
    while(std::getline(file, str)) {
        int length = str.length();
        powerSum += sec.getMinimumOfColors(str, length);
        bool possible = sec.gamePossible(str, length);
        if(possible) {
            result += sec.getGameNumber(str, length);
        }
    }
    std::cout << result << std::endl;
    std::cout << powerSum << std::endl;
}