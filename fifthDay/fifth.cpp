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
    vector<vector<long>> seed2Soil;
    vector<vector<long>> soil2Fert;
    vector<vector<long>> fert2Water;
    vector<vector<long>> water2Light;
    vector<vector<long>> light2Temp;
    vector<vector<long>> temp2hum;
    vector<vector<long>> hum2Location;

    enum MapType{Seed2Soil = 1, Soil2Fert = 2, Fert2Water = 3, Water2Light = 4, Light2Temp = 5, Temp2Hum = 6, Hum2Location = 7};
    void findSeeds(string s) {
        seeds.clear();
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
            switch(mapType) {
                case Seed2Soil:
                    seed2Soil.push_back({startDestIndex, startSourceIndex, range});
                    break;
                case Soil2Fert:
                    soil2Fert.push_back({startDestIndex, startSourceIndex, range});
                    break;
                case Fert2Water:
                    fert2Water.push_back({startDestIndex, startSourceIndex, range});
                    break;
                case Water2Light:
                    water2Light.push_back({startDestIndex, startSourceIndex, range});
                    break;
                case Light2Temp:
                    light2Temp.push_back({startDestIndex, startSourceIndex, range});
                    break;
                case Temp2Hum:
                    temp2hum.push_back({startDestIndex, startSourceIndex, range});
                    break;
                case Hum2Location:
                    hum2Location.push_back({startDestIndex, startSourceIndex, range});
                    break;
                default:
                    break;
                }
        }
    }

    long getLowestLocation() {
        long lowestValue = -1;
        for(int i = 0; i < seeds.size(); i++) {
            long currentSeed = seeds[i];
            cout << currentSeed << endl;
            for(int i = 0; i < seed2Soil.size(); i++) {
                vector<long> map = seed2Soil[i];
                for(long j = map[1]; j < map[1] + map[2]; j++) {
                    if(j == currentSeed) {
                        long diff = map[1] - map[0];
                        currentSeed = j - (diff);
                        break;
                    }
                }
            }
            for(int i = 0; i < soil2Fert.size(); i++) {
                vector<long> map = soil2Fert[i];
                for(long j = map[1]; j < map[1] + map[2]; j++) {
                    if(j == currentSeed) {
                        long diff = map[1] - map[0];
                        currentSeed = j - (diff);
                        break;
                    }
                }
            }
            for(int i = 0; i < fert2Water.size(); i++) {
                vector<long> map = fert2Water[i];
                for(long j = map[1]; j < map[1] + map[2]; j++) {
                    if(j == currentSeed) {
                        long diff = map[1] - map[0];
                        currentSeed = j - (diff);
                        break;
                    }
                }
            }
  
            for(int i = 0; i < water2Light.size(); i++) {
                vector<long> map = water2Light[i];
                for(long j = map[1]; j < map[1] + map[2]; j++) {
                    if(j == currentSeed) {
                        long diff = map[1] - map[0];
                        currentSeed = j - (diff);
                        break;
                    }
                }
            }
            for(int i = 0; i < light2Temp.size(); i++) {
                vector<long> map = light2Temp[i];
                for(long j = map[1]; j < map[1] + map[2]; j++) {
                    if(j == currentSeed) {
                        long diff = map[1] - map[0];
                        currentSeed = j - (diff);
                        break;
                    }
                }
            }
            for(int i = 0; i < temp2hum.size(); i++) {
                vector<long> map = temp2hum[i];
                for(long j = map[1]; j < map[1] + map[2]; j++) {
                    if(j == currentSeed) {
                        long diff = map[1] - map[0];
                        currentSeed = j - (diff);
                        break;
                    }
                }
            }
            for(int i = 0; i < hum2Location.size(); i++) {
                vector<long> map = hum2Location[i];
                for(long j = map[0]; j < map[1] + map[2]; j++) {
                    if(j == currentSeed) {
                        long diff = map[1] - map[0];
                        currentSeed = j - (diff);
                        break;
                    }
                }
            }
            if(lowestValue == -1 || lowestValue > currentSeed) {
                lowestValue = currentSeed;
            }
        }
        return lowestValue;
    }
};

int main()
{
    Fifth *f = new Fifth();
    ifstream file("testCase");
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