#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>

using namespace std;
class Sixth {
    string time;
    string record;
    vector<long> times;
    vector<long> records;
    public:
        Sixth(string t, string r) {
            time = t;
            record = r;
        }

    void createTimes() {
        string numberString = "";
        for(int i = 0; i <= time.length(); i++) {
            if(isdigit(time[i])) {
                numberString += time[i];
            } else if(numberString != ""){
                times.push_back(stol(numberString));
                numberString = "";
            }
        }
    }

    void createRecords() {
        string numberString = "";
        for(int i = 0; i <= record.length(); i++) {
            if(isdigit(record[i])) {
                numberString += record[i];
            } else if(numberString != "") {
                records.push_back(stol(numberString));
                numberString = "";
            }
        }
    }

    int calculate() {
        int result = 1;
        for(int i = 0; i < times.size(); i++) {
            int counter = 0;
            for(int j = 0; j < times[i]; j++) {
                long speed = j;
                long dist = speed * (times[i] - speed);
                if(dist > records[i]) {
                    counter++;
                }
            }
            result *= counter;
            cout << result << endl;
        }
    }
};


int main() {
    ifstream file("input");
    string str;
    string timeStr;
    string recordStr;
    while(std::getline(file, str)) {
        if(str.find("Time: ") != std::string::npos) {
            timeStr = str;
        }
        else {
            recordStr = str;
        }
    }
    Sixth* s = new Sixth(timeStr, recordStr);
    s->createRecords();
    s->createTimes();
    s->calculate();
    //-1x^2 + maxDur*x - record = 0
}