#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <map>


using namespace std;


class Eight {
    public:
    vector<char> decs;
    map<string, vector<string>> lu;
    void createDecisions(string str) {
        for(int i = 0; i < str.length(); i++) {
            decs.push_back(str[i]);
        }
    }

    void createLookups(vector<string> l) {
        for(int i = 0; i < l.size(); i++) {
            string s = l[i];
            string source = "";
            string leftD = "";
            string rightD = "";
            for(int j = 0; j < 3; j++) {
                source += s[j];
            }
            for(int j = 7; j < 10; j++) {
                leftD += s[j];
            }
            for(int j = 12; j < 15; j++) {
                rightD += s[j];
            }
            vector<string> lr;
            lr.push_back(leftD);
            lr.push_back(rightD);
            lu[source] = lr;
        }
    }

    int goThrough(string start) {
        string currentPos = start;
        int counter = 0;
        while(currentPos != "ZZZ") {
            char dec = decs[counter % decs.size()];
            vector<string> leftR = lu[currentPos];
            currentPos = dec == 'L' ? leftR[0] : leftR[1];
            counter++;
        }
        return counter;
    }

    bool checkIfAllAreEnd(vector<string> currents) {
        int count = 0;
        for(string curr: currents) {
            if(curr[2] != 'Z') {
                return false;
            } 
        }
        return true;
    }
    
    long gcd(int a, int b)
    {
        for (;;)
        {
            if (a == 0) return b;
            b %= a;
            if (b == 0) return a;
            a %= b;
        }
    }

    long lcm(int a, int b)
    {
        long temp = gcd(a, b);

        return temp ? (a / temp * b) : 0;
    }


    long goThroughList(vector<string> starts) {
        int counter = 0;
        vector<string> s = starts;
        vector<int> counts;
        for(string sa: starts) {
            while(sa[2] != 'Z' || counter == 0) {
                char dec = decs[counter % decs.size()];
                vector<string> leftR = lu[sa];
                sa = dec == 'L' ? leftR[0] : leftR[1];
                counter++;
            }
            counts.push_back(counter);
            cout << counter << endl;
            counter = 0;
        }
        /*for(int i = 0; i < s.size(); i++) {
                string currentPos = s[i];
                char dec = decs[counter % decs.size()];
                vector<string> leftR = lu[currentPos];
                currentPos = dec == 'L' ? leftR[0] : leftR[1];
                s[i] = currentPos;
            }
        counter += 1;*/

        return lcm(counts[0], lcm(counts[1], lcm(counts[2], lcm(counts[3], lcm(counts[4], counts[5])))));
    }
};

int main() {

    ifstream file("input");
    string str;
    string decs = "";
    vector<string> lookUps;
    while (std::getline(file, str)){
        if(decs == "") {
            decs = str;
        }
        else if(str != "") {
            lookUps.push_back(str);
        }
    }
    Eight* e = new Eight();
    e->createDecisions(decs);
    e->createLookups(lookUps);
    //int result = e->goThrough("11A");
    long result2 = e->goThroughList({"AAA", "LHA", "RHA", "CVA", "LDA", "VGA"});
    //cout << result << endl;
    //int result2 = e->goThroughList({"11A", "22A"});
    cout << result2 << endl;
    return 1;
}