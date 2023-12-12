#include <string>
#include <fstream>
#include <vector>
#include <iostream>
#include <algorithm> 

using namespace std;

struct Point{
    int x;
    int y;
};

class Eleven {
    vector<string> map;
    vector<Point> galaxies;
    vector<int> yCoords;
    vector<int> xCoords;
    int width;
    int height;
    public:

    void setKnownParams(vector<string> m, vector<int> y) {
        map = m;
        yCoords = y;
        height = map.size();
        width = map[0].length();
        getXCoords();
        getGalaxies();
    }

    bool checkIfExpandsX(int x) {
        for(int y = 0; y < height; y++) {
            if(map[y][x] != '.'){
                return false;
            }
        }
        return true;
    }

    void getXCoords() {
        for(int x = 0; x < width; x++) {
            if(checkIfExpandsX(x)) {    
                xCoords.push_back(x);
            }
        }
    }

    void getGalaxies() {
        for(int y = 0; y < height; y++) {
            for(int x = 0; x < width; x++) {
                char c = map[y][x];
                if(c == '#') {
                    Point p = Point();
                    p.x = x;
                    p.y = y;
                    galaxies.push_back(p);
                }
            }
        }
    }

    long calculateDistance(Point p, Point o) {
        int xDist = abs(p.x - o.x);
        int yDist = abs(p.y - o.y);
        int minX = min(p.x, o.x);
        int maxX = max(p.x, o.x);
        int minY = min(p.y, o.y);
        int maxY = max(p.y, o.y);
        int xCount = 0;
        int yCount = 0;
        for(int x = minX ; x < maxX; x++) {
            if(std::find(xCoords.begin(), xCoords.end(), x) != xCoords.end()) {
                xCount += 999999;
            }
        }
        for(int y = minY ; y < maxY; y++) {
            if(std::find(yCoords.begin(), yCoords.end(), y) != yCoords.end()) {
                yCount += 999999;
            }
        }
        int baseDistance = xDist + yDist;
        int extra = xCount + yCount;
        long distance = baseDistance + extra;
        return distance;
    }

    long calculate() {
        long result = 0;
        for(int i = 0; i < galaxies.size(); i++) {
            Point p = galaxies[i];
            for(int j = i+1; j < galaxies.size(); j++) {
                Point o = galaxies[j];
                if(!(p.x == o.x && p.y == o.y)) {
                    long distance = calculateDistance(p, o);
                    //cout << distance << ": " << i << " " << j << endl;
                    result += distance;
                }
            }
        }
        return result;
    }

    bool checkIfExpands(string s) {
        for(char c: s) {
            if(c != '.')
            return false;
        }
        return true;
    }
};

int main() {
    ifstream file("input");
    string str;
    vector<int> yCoordinates;
    vector<string> galaxyMap;
    int counter = 0;
    int width = 0;
    Eleven* e = new Eleven();
    while (std::getline(file, str)) {
        if(e->checkIfExpands(str)) {
            yCoordinates.push_back(counter);
        }
        galaxyMap.push_back(str);
        counter++;
    }
    e->setKnownParams(galaxyMap, yCoordinates);
    long result = e->calculate();
    cout << result << endl;
    return 1;

}