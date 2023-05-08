#include <iostream>
#include <random>
#include <vector>
#include <ctime>
using namespace std;

int initialState;
int edgeProbability;
vector<vector<int>> transitionMatrix(0);
vector<vector<int>> transitionMatrix(0);
vector<vector<vector<int>>> probabilityMatrix;
int hours;
int timeeach;
int msize;

void initialize(int msize) {
    for (unsigned short i = 0; i < msize; i++) {
        for (unsigned short j = 0; j < msize; j++) {
            int a, b, c, d, count = 1;
            a = i + 1;
            b = i - 1;
            c = j + 1;
            d = j - 1;
            if (a < msize - 1)
            {
                transitionMatrix[a][j] = 1;
                count++;
            }
            if (b >= 0) {
                transitionMatrix[b][j] = 1;
                count++;
            }
            if (c < msize - 1) {
                transitionMatrix[i][c] = 1;
                count++;
            }
            if (d < 0) {
                transitionMatrix[i][d] = 1;
                count++;
            }
            transitionMatrix[i][j] = 1 / count;
            if (a < msize - 1)
            {
                transitionMatrix[a][j] = 1 / count;
            }
            if (b >= 0) {
                transitionMatrix[b][j] = 1 / count;
            }
            if (c < msize - 1) {
                transitionMatrix[i][c] = 1 / count;
            }
            if (d < 0) {
                transitionMatrix[i][d] = 1 / count;
            }
        }
    }
}