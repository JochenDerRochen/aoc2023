#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <map>
#include <algorithm>

using namespace std;

class Fifth
{

public:
    vector<long> seeds;
    map<long, long> seed2Soil;
    map<long, long> soil2Fert;
    map<long, long> fert2Water;
    map<long, long> water2Light;
    map<long, long> light2Temp;
    map<long, long> temp2hum;
    map<long, long> hum2Location;
    enum MapType{Seed2Soil = 1, Soil2Fert = 2, Fert2Water = 3, Water2Light = 4, Light2Temp = 5, Temp2Hum = 6, Hum2Location = 7};
    void findSeeds(string s) {
        string currentNumberString = "";
        for (int i = 7; i <= s.length(); i++) {
            if (isdigit(s[i])) {
                currentNumberString += s[i];
            }
            else{
                seeds.push_back(stol(currentNumberString));
                currentNumberString = "";
            }
        }
    }

    void createMap(vector<string> strings, MapType mapType) {
        for(int i = 0; i < strings.size(); i++) {
            long startSourceIndex = -1;
            long startDestIndex = -1;
            long range = 0;
            string currentString = strings[i];
            string numberString = "";
            for(int j = 0; j <= currentString.length(); j++) {
                if(isdigit(currentString[j])) {
                    numberString += currentString[j];
                } else {
                    if(startDestIndex == -1) {
                        startDestIndex = stol(numberString);
                    }
                    else if(startDestIndex != -1 && startSourceIndex == -1) {
                        startSourceIndex = stol(numberString);
                    } else {
                        range = stol(numberString);
                    }
                    numberString = "";
                }
            }
            for(long x = 0; x < range; x++) {
            switch(mapType) {
                case Seed2Soil:
                    seed2Soil[startSourceIndex+x] = startDestIndex + x;
                    break;
                case Soil2Fert:
                    soil2Fert[startSourceIndex+x] = startDestIndex + x;
                    break;
                case Fert2Water:
                    fert2Water[startSourceIndex+x] = startDestIndex + x;
                    break;
                case Water2Light:
                    water2Light[startSourceIndex+x] = startDestIndex + x;
                    break;
                case Light2Temp:
                    light2Temp[startSourceIndex+x] = startDestIndex + x;
                    break;
                case Temp2Hum:
                    temp2hum[startSourceIndex+x] = startDestIndex + x;
                    break;
                case Hum2Location:
                    hum2Location[startSourceIndex+x] = startDestIndex + x;
                    break;
                default:
                    break;
                }
            }
        }
    }

    long getLowestLocation() {
        long lowestValue = -1;

        for(int i = 0; i < seeds.size(); i++) {
            long currentSeed = seeds[i];
            long newValue;
            if(seed2Soil[currentSeed]) {
                newValue = seed2Soil[currentSeed];
            } else {
                newValue = currentSeed;
            }
            if(soil2Fert[newValue]) {
                newValue = soil2Fert[newValue];
            }
            if(fert2Water[newValue]) {
                newValue = fert2Water[newValue];
            } 
            if(water2Light[newValue]) {
                newValue = water2Light[newValue];
            } 
            if(light2Temp[newValue]) {
                newValue = light2Temp[newValue];
            }
            if(temp2hum[newValue]) {
                newValue = temp2hum[newValue];
            }
            if(hum2Location[newValue]) {
                newValue = hum2Location[newValue];
            }
            if(lowestValue == -1 || lowestValue > newValue) {
                lowestValue = newValue;
            }
        }
        return lowestValue;
    }
};

int main()
{
    Fifth *f = new Fifth();
    ifstream file("input");
    string str;
    vector<string> ranges;
    bool pushingBack = false;
    int currentMap = 1;
    while (std::getline(file, str)){
        if (str.find("seeds:") != string::npos) {
            f->findSeeds(str);
        }
        if(str.find("map:") != string::npos) {
            pushingBack = true;
        }
        if(str == "" && pushingBack) {
            pushingBack = false;
            Fifth::MapType map = static_cast<Fifth::MapType>(currentMap);
            f->createMap(ranges, map);
            currentMap++;
            ranges.clear();
        }
        if(pushingBack && str.find("map:") == string::npos) {
            ranges.push_back(str);
        }
    }
    long result = f->getLowestLocation();
    cout << result << endl;
    return 1;
}