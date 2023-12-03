#include <string>
#include <iostream>
#include <fstream>
using namespace std;
class Third {
    public:
    string str;
    int width;
    int numberOfRows;
    Third(string s, int w, int num) {
        str = s;
        width = w;
        numberOfRows = num;
    }

    char getCharAt(int x, int y) {
        if(x < 0 || x >= width || y < 0 || y >= numberOfRows) {
            return '.';
        }
        return str[y * width + x];
    }

    int sumUp() {
        bool isPartNumber = false;
        int total = 0;
        string currentNumberString = "";
        int currentNumber;
        for(int y = 0; y < numberOfRows; y++) {
            for(int x = 0; x < width; x++) {
                char currentChar = getCharAt(x, y);
                if(isdigit(currentChar)) {
                    currentNumberString += currentChar;
                    if(!isPartNumber) {
                        isPartNumber = checkIfPartNumber(x, y);
                    }
                } else {
                    if(isPartNumber) {
                        currentNumber = stoi(currentNumberString);
                        total += currentNumber;
                    } 
                    isPartNumber = false;
                    currentNumberString = "";
                    currentNumber = 0;
                }
            }
        }
        return total;
    }

    int gearUp() {
        bool isGear = false;
        int total = 0;
        for(int y = 0; y < numberOfRows; y++) {
            for(int x = 0; x < width; x++) {
                char currentChar = getCharAt(x, y);
                if(currentChar == '*') {
                    isGear = checkIfGear(x, y);
                }
                if(isGear) {
                    total += multiplyGearNumbers(x, y);
                    isGear = false;
                }
            }
        }
        return total;
    }

    int multiplyGearNumbers(int x, int y) {
        int total = 1;
        for(int i = y-1; i <= y+1; i++) {
            for(int j = x-1; j <= x+1; j++) {
                char current = getCharAt(j, i);
                char next = getCharAt(j+1, i);
                char nextnext = getCharAt(j+2, i);
                cout << current << endl;
                if(isdigit(current)) {
                    total *= getNumber(j, i);
                    if(isdigit(next)) {
                        j++;
                        if(isdigit(nextnext)) {
                            j++;
                        }
                    }
                }
            }
        }
        return total;
    }

    int getNumber(int x, int y) {
        int firstX = x;
        int lastX = x;
        string numberString = "";
        while(isdigit(getCharAt(firstX-1, y))) {
            firstX -= 1;
        }

        while(isdigit(getCharAt(lastX+1, y))) {
            lastX += 1;
        }
        for(int i = firstX; i <= lastX; i++) {
            char current = getCharAt(i, y);
            numberString += current;
        } 
        return stoi(numberString);
    }

    bool checkIfPartNumber(int x, int y) {
        bool isPartNumber = false;
        for(int i = y-1; i <= y+1; i++) {
            for(int j = x-1; j <= x+1; j++) {
                if(!(i == y && j == x)) {
                    char current = getCharAt(j, i);
                    if(current != '.' && !isdigit(current)) {
                        isPartNumber = true;
                        break;
                    } 
                }
            }
        }
        return isPartNumber;
    }

    bool checkIfGear(int x, int y) {
        bool isGear = false;
        bool containsNumber = false;
        string surrounding = "";
        for(int i = y-1; i <= y+1; i++) {
            for(int j = x-1; j <= x+1; j++) {
                char current = getCharAt(j,i);
                surrounding += getCharAt(j, i);
                containsNumber = isdigit(current);
            }
        }
        return checkFor2Numbers(surrounding);;
    }

    bool checkFor2Numbers(string s) {
        int numberCount = 0;
        for(int i = 0; i < 3; i++) {
            for(int j = 0; j < 3; j++) {
                char current = s[i * 3 + j];
                
                char next = '.';
                char nextnext = '.';
                if(j+1 < 3) {
                    next = s[i*3 + (j+1)];
                }
                if(j+2 < 3) {
                    nextnext = s[i*3 + (j+2)];
                }
                if(isdigit(current)) {
                    s[i * 3 + j] = '.';
                    numberCount += 1;
                    if(isdigit(next)) {
                        s[i*3 + (j+1)] = '.';
                        if(isdigit(nextnext)) {
                            s[i*3 + (j+2)] = '.';
                        }
                    }
                }
            }
        }
        return numberCount > 1;
    }
};

int main() {
    int width;

    ifstream file("input");
    string str;
    string wholeString = "";
    int rows = 0;
    while(std::getline(file, str)) {
        width = str.length();
        rows++;
        wholeString += str;
    }
    Third third = Third(wholeString, width, rows);
    int result = third.sumUp();
    int secondResult = third.gearUp();
    cout << result << endl;
    cout << secondResult << endl;
}