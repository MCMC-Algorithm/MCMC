#include <iostream>
#include <random>
#include <vector>
#include <ctime>
#include <iomanip>
using namespace std;

int msize;
int initialState;
vector<vector<vector<float>>> transitionMatrix;
vector<float> randProb(0);
vector<int> counter;
int hours;


void initialize(int msize)
{
    vector<vector<float>> temp(0);

    for (unsigned short i = 0; i < msize; i++) 
    {
        for (unsigned short j = 0; j < msize; j++)
        {
            temp.assign(msize, vector<float>(msize, 0));
            int a, b, c, d, count = 1;
            a = i + 1;
            b = i - 1;
            c = j + 1;
            d = j - 1;
            if (a <= msize - 1)
            {
                temp[a][j] = 1;
                count++;
            }
            if (b >= 0)
            {
                temp[b][j] = 1;
                count++;
            }
            if (c <= msize - 1)
            {
                temp[i][c] = 1;
                count++;
            }
            if (d >= 0)
            {
                temp[i][d] = 1;
                count++;
            }
            double res = 1.0 / count;
            temp[i][j] = res;
            if (a <= msize - 1)
            {
                temp[a][j] = res;
            }
            if (b >= 0)
            {
                temp[b][j] = res;
            }
            if (c <= msize - 1)
            {
                temp[i][c] = res;
            }
            if (d >= 0)
            {
                temp[i][d] = res;
            }
            transitionMatrix.push_back(temp);
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

int convert(int i, int j)
{
    return i * msize + j;
}

void randomwalk()
{
    counter.assign(msize * msize, 0);
    int randomState = initialState;
    cout << "Start at " << randomState<<endl;
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> rowDist(0, msize - 1);
    uniform_int_distribution<> colDist(0, msize - 1);
    int randomi, randomj, temp;

    for (unsigned short i = 0; i < hours; i++) { //n
        cout << "\nHour [" << i + 1<<"]";
        do {
            temp = randomState;
            randomi = rowDist(gen);
            randomj = colDist(gen);
        } while (transitionMatrix[temp][randomi][randomj] == 0);
        randomState = convert(randomi, randomj);
        cout << "\nProbable intersection : " << randomState << " with indicies (" << randomi << ", " << randomj << ")" << endl;
        counter[randomState]++;
    }
    cout << endl << endl;

}


void display()
{
    for (unsigned short k = 0; k < transitionMatrix.size(); k++) {
        cout << k << ")\n";
        for (int i = 0; i < msize; i++)
        {
            for (int j = 0; j < msize; j++)
            {
                cout << transitionMatrix[k][i][j] << "    ";
            }
            cout << endl;
        }
    }
}


void fProb()
{
    randProb.assign((msize * msize), 0);
    for (int i = 0; i < (msize * msize); i++)
    {
        randProb[i] = (float)counter[i] / hours;
        cout << left << setw(20) << randProb[i] ;
        if ((i + 1) % msize == 0)
            cout << endl<<endl;
    }
}


int main()
{
    cout << "\n\t\t\t\t\t  ******************************" << "\n\t\t\t\t\t*                                *" << "\n\t\t\t\t\t*              MCMC              *" << "\n\t\t\t\t\t*                                *" << "\n\t\t\t\t\t  ******************************\n\n\n";   
    
    do{
    cout << "Please specify the number of roads in your neighberhood : "; 
    cin >> msize;
    if(msize < 2)             
    cerr << "\n\t\t*** INVALID :: LOGICAL ERROR :: MAP MUST AT LEAST INCLUDE TWO ROADS TO CONTAIN AN INTERSECTION ***\n" << endl; 
    } while(msize<2);

   do{
    cout << "\nPlease specify the intersection number for where the roadblock is currently located : ";
    cin >> initialState;
    if(initialState > (msize*msize)-1 || initialState < 0)
    cerr << "\n\t\t*** INVALID :: LOGICAL ERROR :: NUMBER OF INTERSECTIONS ENTERED DOES NOT MATCH WITH THE SPECIFIED ROADS ABOVE ***\n" << endl;
    } while(initialState > (msize * msize) - 1 || initialState < 0);
    
    do{
    cout << "\nPlease specify the number of hours you believe the roadblock will last for : ";
    cin >> hours;
    if(hours<1) 
    cerr << "\n\t\t*** INVALID :: LOGICAL ERROR :: HOURS CAN NOT BE LESS THAN ONE***\n" << endl;
    } while(hours < 1);
    
    initialize(msize);
    randomwalk();
    fProb();
    //display();

    return 0;
}