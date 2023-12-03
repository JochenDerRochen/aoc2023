#include <string>
#include <iostream>
#include <fstream>
#include <regex>


class First {
public:
    int getFirstNumber(std::string &s, int length) {
        for(int i = 0; i < length; i++) {
            if(isdigit(s[i])) {
                int number = s[i] - '0';
                return number;
            }
        }
        return 1;
    }

    int getSecondNumber(std::string &s, int length) {
        for(int i = length; i >= 0; i--) {
            if(isdigit(s[i])) {
                int number = s[i] - '0';
                return number;
            }
        }
        return 0;
    }

    void replaceTextWithNumber(std::string &s) {
        s = std::regex_replace(s, std::regex("zero"), "0");
        s = std::regex_replace(s, std::regex("one"), "1");
        s = std::regex_replace(s, std::regex("two"), "2");
        s = std::regex_replace(s, std::regex("three"), "3");
        s = std::regex_replace(s, std::regex("four"), "4");
        s = std::regex_replace(s, std::regex("five"), "5");
        s = std::regex_replace(s, std::regex("six"), "6");
        s = std::regex_replace(s, std::regex("seven"), "7");
        s = std::regex_replace(s, std::regex("eight"), "8");
        s = std::regex_replace(s, std::regex("nine"), "9");
        s = std::regex_replace(s, std::regex("7ine"), "79");
        s = std::regex_replace(s, std::regex("seve9"), "79");
        s = std::regex_replace(s, std::regex("8wo"), "82");
        s = std::regex_replace(s, std::regex("eigh2"), "82");
        s = std::regex_replace(s, std::regex("0ne"), "01");
        s = std::regex_replace(s, std::regex("zer1"), "01");
        s = std::regex_replace(s, std::regex("2ne"), "21");
        s = std::regex_replace(s, std::regex("tw1"), "21");
        s = std::regex_replace(s, std::regex("5ight"), "58");
        s = std::regex_replace(s, std::regex("fiv8"), "58");
        s = std::regex_replace(s, std::regex("nin8"), "98");
        s = std::regex_replace(s, std::regex("9ight"), "98");
        s = std::regex_replace(s, std::regex("thre8"), "38");
        s = std::regex_replace(s, std::regex("3ight"), "38");
        s = std::regex_replace(s, std::regex("on8"), "18");
        s = std::regex_replace(s, std::regex("1ight"), "18");
    }
};

int main() {
    First first = First();
    std::ifstream file("input");
    std::string str;
    int result = 0;
    while(std::getline(file, str)) {
        first.replaceTextWithNumber(str);
        std::cout << str << std::endl;
        int length = str.length();
        int firstNumber = first.getFirstNumber(str, length);
        int secondNumber = first.getSecondNumber(str, length);
        int wholeNumber = firstNumber * 10 + secondNumber;
        result += wholeNumber;
    }
    std::cout << result << std::endl;
}