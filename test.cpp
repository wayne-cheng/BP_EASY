// #include "BP.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

float** make_matrix(int row, int column, float fill = 0.0)
{
    float **m = new float *[column]; 

    for (int i = 0; i < row; i++) {
        m[i] = new float [column];
        for (int j = 0; j < column; j++) {
            m[i][j] = fill;
        }
    }

    return m;
}

// float rand_num(float min, float max)
// {
//     int rand1, rand2;
//     float rand_rate;
//     srand((unsigned int)(time(NULL)));
//     rand();
//     rand();
//     rand2 = rand();
//     cout << "rand1 " << rand1 <<endl;
//     cout << "rand2 " << rand2 <<endl;
//     rand_rate = (rand2 / (float)32767);
//     cout << "rand_num_rate" << rand_rate <<endl;
//     return min + rand_rate * (max - min);
// }

float rand_num(float min, float max)
{
    float num[10];
    srand((unsigned int)(time(NULL)));
    for (int i = 0; i < 10; i++) {
        num[i] = rand();
    }
    int j = rand() % 10;
    return min + (max - min) * num[j] / RAND_MAX;
}

float* array(int num, float fill = 0.0)
{
    float* a = new float[num];
    for (int i = 0; i < num; i++) {
        a[i] = fill;
    }
    return a;
}


int main()
{
    // int row = 2;
    // int column = 2;
    // float fill = 3.2;
    // float **mym = make_matrix(row, column, fill);
    // for (int i = 0; i < row; i++) {
    //     for (int j = 0; j < column; j++) {
    //         cout << mym[i][j] << "\t";
    //     }
    //         cout << endl;
    // }


    // cout<< rand_num(0.2, 0.4) << endl;

    float* ai = array(5, 2.0);
    cout << ai[2] <<endl;


    return 0;
}
