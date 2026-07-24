#include <iostream>
#include <string>
using namespace std;

bool isGoalScored(string field[7]) {
    int ballRow = -1, ballCol = -1;
    int crossbarRow = -1;
    int leftPost = -1, rightPost = -1;
    for (int i = 0; i < 7; i++) {
        for (int j = 0; j < field[i].length(); j++) {
            if (field[i][j] == '0') {
                ballRow = i;
                ballCol = j;
            }
            if (field[i][j] == '#') {
                if (leftPost == -1 || j < leftPost) {
                    leftPost = j;
                }
                if (rightPost == -1 || j > rightPost) {
                    rightPost = j;
                }
            }
        }
    }
    for (int i = 0; i < 7; i++) {
        bool hasMultipleHash = false;
        int hashCount = 0;
        for (int j = 0; j < field[i].length(); j++) {
            if (field[i][j] == '#') {
                hashCount++;
            }
        }
        if (hashCount > 2) {
            crossbarRow = i;
            break;
        }
    }
    if (ballRow < crossbarRow && ballCol > leftPost && ballCol < rightPost) {
        return true;
    }
    return false;
}

int main() {
    string field[7];
    cout << "Enter the football field (7 rows, 16 columns each):" << endl;
    cin.ignore();
    for (int i = 0; i < 7; i++) {
        getline(cin, field[i]);
    }
    if (isGoalScored(field)) {
        cout << "Goal scored: true" << endl;
    } else {
        cout << "Goal scored: false" << endl;
    }
    return 0;
}                                                                                                   