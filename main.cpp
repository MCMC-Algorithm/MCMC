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
vector<int> pos(int num) {
    int i = 0, j = 0;
    while (num - 1 > 0) {
        j++;
        if (j % msize == 0) {
            i++;
            j = 0;
        }
        num--;
    }
    vector<int> x; 
    x[0] = i; 
    x[1] = j;
    return x;
}

int irandomized(int current) {
    int i;
    do {
        srand(time(0));
        i = rand() % msize;
    } while (transitionMatrix[i][current] == 0);
    return i;
}

int jrandomized(int current) {
    int j;
    do {
        srand(time(0));
        j = rand() % msize;
    } while (transitionMatrix[current][j] == 0);
    return j;
}

void randomizer(int &currenti,int &currentj) {
    srand(time(0));
    int x = rand() % 3;
    if (x == 0) {
        currenti = irandomized(currenti);
    }
    else if (x == 1) {
        currentj = jrandomized(currentj);
    }
    cout << "i: " << currenti << " j: " << currentj << endl;
}


int main()
{

}