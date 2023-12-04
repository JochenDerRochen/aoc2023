#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>

using namespace std;
class Fourth {
    public:

    vector<int> getWinningNumbers(string str, int length) {
        size_t index = str.find_first_of(':');
        size_t endIndex = str.find_first_of('|');
        vector<int> winningNumbers;
        string numberString;
        for(int i = index+1; i < endIndex; i++) {
            if(isdigit(str[i])) {
                numberString += str[i];
            } else if(numberString != ""){
                winningNumbers.push_back(stoi(numberString));
                numberString = "";
            }
        }
        return winningNumbers;
    }

    vector<int> getMyNumbers(string str, int length) {
        size_t index = str.find_first_of('|');
        vector<int> myNumbers;
        string numberString;
        for(int i = index+1; i <= length; i++) {
            if(isdigit(str[i])) {
                numberString += str[i];
            } else if(numberString != ""){
                myNumbers.push_back(stoi(numberString));
                numberString = "";
            }
        }
        return myNumbers;
    }

    int countPoints(vector<int> winningNumbers, vector<int> myNumbers) {
        int count = 0;
        for(int i = 0; i < winningNumbers.size(); i++) {
            int currentWinNumber = winningNumbers[i];
            for(int j = 0; j < myNumbers.size(); j++) {
                int currentNumber = myNumbers[j];
                if(currentNumber == currentWinNumber) {
                    count += 1;
                }
            }
        }
        return pow(2, count-1);
    }

    int countCopies(vector<int> winningNumbers, vector<int> myNumbers) {
              int count = 0;
        for(int i = 0; i < winningNumbers.size(); i++) {
            int currentWinNumber = winningNumbers[i];
            for(int j = 0; j < myNumbers.size(); j++) {
                int currentNumber = myNumbers[j];
                if(currentNumber == currentWinNumber) {
                    count += 1;
                }
            }
        }
        return count;
    }

    int getGameNumber(string str) {
        int index = str.find_first_of('d');
        int endIndex = str.find_first_of(':');
        string numberString = "";
        for(int i = index+2; i < endIndex; i++) {
            numberString += str[i];
        }
        return stoi(numberString);
    }


};

int main() {
    string s = "Card 1: 41 48 83 86 17 | 83 86  6 31 17  9 48 53";
    Fourth* f = new Fourth();
    vector<int> winningNums = f->getWinningNumbers(s, s.length());
    vector<int> myNumbers = f->getMyNumbers(s, s.length());
    int points = f->countPoints(winningNums, myNumbers);

    ifstream file("input");
    string str;
    std::ofstream out;
    int overallPoints = 0;
    vector<string> scratchCards;
    vector<string> scratchCardsLookUp;
    while(std::getline(file, str)) {
        int length = str.length();
        vector<int> wNums = f->getWinningNumbers(str, length);
        vector<int> mNums = f->getMyNumbers(str, length);
        overallPoints += f->countPoints(wNums, mNums);
        scratchCards.push_back(str);
        scratchCardsLookUp.push_back(str);
    }
    int pointer = 0;
    while(pointer < scratchCards.size()) {
        string currentScratchCard = scratchCards[pointer];
        int length = currentScratchCard.length();
        int gameNumber = f->getGameNumber(currentScratchCard);
        vector<int> wNums = f->getWinningNumbers(currentScratchCard, length);
        vector<int> mNums = f->getMyNumbers(currentScratchCard, length);
        int copies = f->countCopies(wNums, mNums);
        for(int i = 0; i < copies; i++) {
            scratchCards.insert(scratchCards.begin() + pointer + (i+1), scratchCardsLookUp[gameNumber + i]);
        }
        pointer++;
    }
    cout << scratchCards.size() << endl;
    cout << overallPoints << endl;
    return 1;

}