#include <cmath>
#include <string>
#include <fstream>
#include <vector>
#include <iostream>

using namespace std;

struct PipePiece {
    int x;
    int y;
    int distToStart;
    char c;
};
class Ten { 
    string tilesMap;
    int len;
    int width;
    int height;
    int startX;
    int startY;
    int highestDist = 0;
    vector<PipePiece> pieces;
    public:
    Ten(string s, int h, int w) {
        tilesMap = s;
        len = tilesMap.length();
        height = h;
        width = w;
    }

    char getCharAt(int x, int y) {
        int index = y * width + x;
        if(tilesMap[index]) {
           return tilesMap[index];
        } else {
            return '.';
        }
    }

    int dist(int x, int y) {
        int xSquare = abs(startX - x);
        int ySquare = abs(startY - y);
        return xSquare + ySquare;
    } 

    int iterateThrough() {
        PipePiece start; 
        for(int y = 0; y < height; y++) {
            for(int x = 0; x < width; x++) {
                char c = getCharAt(x, y);
                if(c == 'S') {
                    start = PipePiece();
                    start.distToStart = 0;
                    start.x = x;
                    start.y = y;
                    start.c = 'S';
                    startX = x;
                    startY = y;
                }
            }
        }
        PipePiece current;
        current.x = start.x;
        current.distToStart = 0;
        current.y = start.y;
        current.c = 'S';
        pieces.push_back(start);
        char left;
        char right;
        char top;
        char bot;
        do {
            PipePiece next = PipePiece();
            int x = current.x;
            int y = current.y;
            int index = y * width + x;
            left = getCharAt(x-1, y);
            right = getCharAt(x+1, y);
            top = getCharAt(x, y-1);
            bot =  getCharAt(x, y+1);

            if(current.c == 'S') {
                if(top == '|' || top == 'F' || top == '7') {
                    y -= 1;   
                }  else if(bot == '|' || bot == 'J' || bot == 'L') {
                    y += 1;
                } else if(left == '-' || left == 'F' || left == 'L') {
                    x -= 1;
                } else if(right == '-' || right == '7' || right == 'J') {
                    x += 1;
                }
            } else if(current.c == '-') {
                if(left == 'L' || left == 'F' || left == '-') {
                    x -= 1;
                } else if(right == 'J' || right == '-' || right == '7') {
                    x += 1;
                }
            } else if(current.c == '|') {
                if(top == '7' || top == '|' || top == 'F') {
                    y -= 1;
                } else if(bot == '|' || bot == 'J' || bot == 'L') {
                    y += 1;
                }
            } else if(current.c == 'F') {
                if(right == '-' || right == '7' || right == 'J') {
                    x += 1;
                }else if(bot == '|' || bot == 'J' || bot == 'L') {
                    y += 1;
                }
            } else if(current.c == 'J') {
                if(left == '-' || left == 'L' || left == 'F') {
                    x -= 1;
                } else if(top == '|' || top == '7' || top == 'F') {
                    y -= 1; 
                }
            } else if(current.c == 'L') {
                if(right == '-' || right == 'J' || right == '7') {
                    x += 1;
                }else if(top == '7' || top == '|' || top == 'F') { 
                    y -= 1;
                } 
            } else if(current.c == '7') {
                if(bot == '|' || bot == 'J' || bot == 'L') {
                    y += 1;
                } else if(left == 'F' || left == 'L' || left == '-') {
                    x -= 1;
                }
            } else {
                current = pieces[pieces.size()-1];
                pieces.pop_back();
            }
            next.x = x;
            next.y = y;

            next.c = getCharAt(x, y);
            next.distToStart = pieces.size() + 1;

            tilesMap[index] = '.';
            
            pieces.push_back(next);
            current = next;
        } while(!(left == '.' && right == '.' && top == '.' && bot == '.'));
        int highestDist = 0;
        for (PipePiece p : pieces) {
            if(p.distToStart > highestDist) {
                highestDist = p.distToStart;
            }
        }
        return highestDist/2;
    }

    void drawOutline() {
        for(PipePiece pp: pieces) {
            int index = width * pp.y + pp.x;
            tilesMap[index] = '!';
        }
        cout << tilesMap << endl;
    }
    bool checkIfInside(int x, int y) {
        int intersections = 0;
        bool onLine = false;
        for(int i = x; i < width; i++) {
            char c = getCharAt(i, y);
            char top = getCharAt(x, y-1);
            char bot = getCharAt(x, y+1);
            char cNext = getCharAt(i+1, y);
            //were on a horizontal
            if(c == '!' && cNext == '!' && top != '!' && bot != '!') {
                onLine = true;
            } else if(c != '!' && top != '!' && bot != '!') {
                onLine = false;
                intersections++;
            }
        }
        return (intersections % 2 == 1 );
    }

    int checkInsides() {
        int counter = 0;
        for(int y = 0; y < height; y++) {
            for(int x = 0; x < width; x++) {
                cout << getCharAt(x, y) << endl;
                char c = getCharAt(x, y);
                if(c != '!') {
                    if(checkIfInside(x, y)) {
                    counter++;
                }
                }
            }
        }
        return counter;
    }

    int calculate() {
        return iterateThrough();
    }
};

int main() {
    ifstream file("test");
    string str;
    string mapString = "";
    int width = 0;
    int height = 0;
    while (std::getline(file, str)) {
        mapString += str;
        if(width == 0)  {
            width = str.length();
        }
        height++;
    }
    Ten* t = new Ten(mapString, height, width);
    int dist = t->calculate();
    t->drawOutline();
    int result = t->checkInsides();
    cout << dist << endl;
    cout << result << endl;
    return 1;
}