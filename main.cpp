#include <iostream>
#include <random>
#include <vector>
#include <ctime>
using namespace std;

int initialState;
vector<vector<float>> transitionMatrix(0);
vector<vector<vector<float>>> newMatrix;
vector<float> randProb(0);
vector<int> counter(0);
vector<vector<vector<float>>> probabilityMatrix;
int hours;
int msize;


void initialize(int msize)
{
    for (unsigned short i = 0; i < msize; i++)
    {
        for (unsigned short j = 0; j < msize; j++)
        {
            transitionMatrix.assign(msize, vector<float>(msize, 0));
            int a, b, c, d, count = 1;
            a = i + 1;
            b = i - 1;
            c = j + 1;
            d = j - 1;
            if (a <= msize - 1)
            {
                transitionMatrix[a][j] = 1;
                count++;
            }
            if (b >= 0)
            {
                transitionMatrix[b][j] = 1;
                count++;
            }
            if (c <= msize - 1)
            {
                transitionMatrix[i][c] = 1;
                count++;
            }
            if (d >= 0)
            {
                transitionMatrix[i][d] = 1;
                count++;
            }
            double res = 1.0 / count;
            transitionMatrix[i][j] = res;
            if (a <= msize - 1)
            {
                transitionMatrix[a][j] = res;
            }
            if (b >= 0)
            {
                transitionMatrix[b][j] = res;
            }
            if (c <= msize - 1)
            {
                transitionMatrix[i][c] = res;
            }
            if (d >= 0)
            {
                transitionMatrix[i][d] = res;
            }
            newMatrix.push_back(transitionMatrix);
        }
    }
}
vector<int> pos(int num)
{
    int i = 0, j = 0;
    while (num - 1 > 0)
    {
        j++;
        if (j % msize == 0)
        {
            i++;
            j = 0;
        }
        num--;
    }
    vector<int> pos;
    pos.push_back(i);
    pos.push_back(j);
    return pos;
}

int irandomized(int current)
{
    int i;
    do
    {
        srand(time(0));
        i = rand() % msize;
    } while (transitionMatrix[i][current] == 0);
    return i;
}

int jrandomized(int current)
{
    int j;
    do
    {
        srand(time(0));
        j = rand() % msize;
    } while (transitionMatrix[current][j] == 0);
    return j;
}

void randomizer(int& currenti, int& currentj)
{
    srand(time(0));
    int x = rand() % 3;
    if (x == 0)
    {
        currenti = irandomized(currenti);
    }
    else if (x == 1)
    {
        currentj = jrandomized(currentj);
    }
    cout << "i: " << currenti << " j: " << currentj << endl;
}

int convert(int i, int j)
{
    return i * msize + j + 1;
}

void randomwalk(int& currenti, int& currentj)
{
    int num = -1;
    for (int i = 0; i < hours; i++)
    {
        int num = convert(currenti, currentj);
        cout << "from state " << num << " to state ";
        randomizer(currenti, currentj);
        num = convert(currenti, currentj);
        cout << num << endl;
        counter[num]++;
    }
}

void fProb()
{
    for (int i = 0; i < (msize * msize); i++)
    {
        randProb[i] = counter[i] / hours;
        cout << randProb[i] << endl;
    }
}

void display()
{
    for (int i = 0; i < msize; i++)
    {
        for (int j = 0; j < msize; j++)
        {
            cout << transitionMatrix[i][j] << " ";
        }
        cout << endl;
    }
}

void rprob() {
    for (int i = 0; i < msize; i++) {
        for (int j = 0; j < msize; j++) {
            probabilityMatrix[i][j][0] = transitionMatrix[i][j];
        }
    }
    if (hours > 1) {
        for (int h = 1; h < hours; h++) {
            for (int i = 0; i < msize; i++) {
                for (int j = 0; j < msize; j++) {
                    probabilityMatrix[i][j][h] = 0;
                    for (int k = 0; k < 9; k++) {
                        probabilityMatrix[i][j][h] += probabilityMatrix[i][k][h - 1] * transitionMatrix[k][j];
                    }
                }
            }
        }
    }
}

int main()
{
    cout << "Enter the size of the matrix: ";
    cin >> msize;
    cout << "Enter the initial state: ";
    cin >> initialState;
   cout << "Enter the number of hours: ";
    cin >> hours;
    initialize(msize);
   // display();
    for (unsigned short k = 0; k < newMatrix.size(); k++) {
        cout << k << ")\n";
        for (int i = 0; i < msize; i++)
        {
            for (int j = 0; j < msize; j++)
            {
                cout << newMatrix[k][i][j] << " ";
            }
            cout << endl;
        }
    }
    int currenti = pos(initialState)[0];
    int currentj = pos(initialState)[1];
    randomwalk(currenti, currentj);
  /*
    fProb();
    rprob();*/
    return 0;
}