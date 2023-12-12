#include <cctype>
#include <string>
#include <fstream>
#include <vector>
#include <iostream>

using namespace std;

class Nine {
    vector<string> allSeq;
    public:
    int sum = 0;
    int sumFirst = 0;
    Nine(vector<string> s) {
        allSeq = s;
    }

    void generateSeq() {
        for(string seq: allSeq) {
            string numberS = "";
            vector<int> sequence;
            for(char c : seq) {
                if(isdigit(c) || c == '-') {
                    numberS += c;
                } else {
                    sequence.push_back(stoi(numberS));
                    numberS = "";
                }
            }
            solveSeq(sequence);
        }
    }

    bool allMembersAreZero(vector<int> seq) {
        for(int mem: seq) {
            if(mem != 0) {
                return false;
            }
        }
        return true;
    }

    void solveSeq(vector<int> s) {
        vector<int> currentSeq;
        currentSeq = s;
        vector<int> firstDiffs = {currentSeq[0]};
        vector<int> lastDiffs = {currentSeq[currentSeq.size()-1]};
        while(!allMembersAreZero(currentSeq)) {
            vector<int> diffs;
            int diff;
            for(int i = 0; i < currentSeq.size()-1; i++) {
                diff = currentSeq[i+1] - currentSeq[i];
                diffs.push_back(diff);
            }
            firstDiffs.push_back(diffs[0]);
            lastDiffs.push_back(diff);
            currentSeq = diffs;
        }
        int newValue = 0;
        int firstNewValue = 0;
        for(int d: lastDiffs) {
            newValue += d;
        }
        for(int i = firstDiffs.size()-1; i >= 0; i--) {
            int fd = firstDiffs[i];
            firstNewValue = fd - firstNewValue;
        }
        sumFirst += firstNewValue;
        sum += newValue;
    }


};

int main() {
    ifstream file("input");
    string str;
    vector<string> seq;
    while (std::getline(file, str)) {
        seq.push_back(str);
    }
    Nine* n = new Nine(seq);
    n->generateSeq();
    cout << n->sumFirst << endl;
    cout << n->sum << endl;
    return 1;
}
