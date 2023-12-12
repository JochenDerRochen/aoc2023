#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

class Player {
    public:
    vector<int> hand;
    int bid;
    int handType;
    Player(vector<int> h, int b, int t) {
        hand = h;
        bid = b;
        handType = t;
    }
};

class Seventh {
    vector<Player> players;
    public:

    int createPlayers(vector<string> pStr) {
        for(int i = 0; i < pStr.size(); i++) {
            string currP = pStr[i];
            vector<int> currHand;
            int handEnd = currP.find_first_of(' ');
            int bid = 1;
            for(int j = 0; j < handEnd; j++) {
                if(isdigit(currP[j])) {
                    int a = currP[j] - '0';
                    currHand.push_back(a);
                } else {
                    switch(currP[j]) {
                        case 'T':
                            currHand.push_back(10);
                            break;
                        case 'J':
                            currHand.push_back(0);
                            break;
                        case 'Q':
                            currHand.push_back(12);
                            break;
                        case 'K':
                            currHand.push_back(13);
                            break;
                        case 'A':
                            currHand.push_back(14);
                            break;
                    }
                }
            }
            string currentNumberS = "";
            for(int x = handEnd+1; x < currP.length(); x++) {
                currentNumberS += currP[x];
            }
            bid = stoi(currentNumberS);
            int type = getHandType(currHand);
            Player p = Player(currHand, bid, type);
            players.push_back(p);
        }
        return calculateResult();
    }

    static bool compareByLength( Player &a, Player &b)
    {
        if(a.handType != b.handType) {  
             return a.handType < b.handType;
        } else {
            for(int i = 0; i < a.hand.size(); i++) {
                if(a.hand[i] != b.hand[i]) {
                    return a.hand[i] < b.hand[i];
                }
            }
        }
        return 0;
    }

    int calculateResult() {
        sort(players.begin(), players.end(), compareByLength);
        int sum = 0;
        for(int i = 0; i < players.size(); i++) {

            sum += (players[i].bid * (i+1));
        }
        return sum;
    }

    int getHandType(vector<int> hand) {
        vector<int> alreadyUsed;
        vector<int> counters;
        map<int, int> numbersCount;
        int highestFreq = 0; 
        int mostFrequent;
        for(int j = 0; j < hand.size(); j++) {
            int freq = 0;
            if(hand[j] != 1) {
                for(int x = 0; x < hand.size(); x++) {
                    if(hand[x] == hand[j]) {
                        freq++;
                    }
                }
                if(freq > highestFreq) {
                    highestFreq = freq;
                    mostFrequent = hand[j];
                }
            }
        }
        for(int i = 0; i < hand.size(); i++) {
            int curr = hand[i];
            if(curr == mostFrequent) {
                curr = 0;
                mostFrequent = 1000;
            }
            int count = 1;
            if(std::find(alreadyUsed.begin(), alreadyUsed.end(), curr) != alreadyUsed.end()) {

            } else {
                alreadyUsed.push_back(curr);
                for(int j = i+1; j< hand.size(); j++) {
                    if(hand[j] == curr) {
                        count++;
                    }
                }
            }
            if(count > 1) {
                counters.push_back(count);
            }
        }
        if(counters.size() == 1) {
            if(counters[0] == 2) {
                return 1;
            }  else if(counters[0] == 3) {
                return 3;
            }
            else if(counters[0] == 4) {
                return 5;
            } else if(counters[0] == 5) {
                return 6;
            }
        } else if(counters.size() == 0) {
            return 0;
        }
        int sum = 0;
        for(int i = 0; i < counters.size(); i++) {
            sum += counters[i];
        }
        if(sum == 4) {
            return 2;
        } else {
            return 4;
        }
    }
    
};

int main() {
    ifstream file("input");
    string str;
    vector<string> players;
    while(std::getline(file, str)) {
        players.push_back(str);
    }
    Seventh* f = new Seventh();
    int result = f->createPlayers(players);
    cout << result << endl;
    return 1;
}