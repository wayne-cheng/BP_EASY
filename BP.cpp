#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>

#include "BP.h"

#ifndef RAND_MAX
#define RAND_MAX 0x7fff
#endif

using namespace std;

BP::BP(int ni, int nh, int no)
{
    this->ni = ni + 1; //增加一个偏差节点
    this->nh = nh;
    this->no = no;

    //激活神经网络的所有节点（向量）
    this->ai = array(this->ni, 1.0);
    this->ah = array(this->nh, 1.0);
    this->ao = array(this->no, 1.0);
    
    //建立权重（矩阵）
    this->wi = make_matrix(this->ni, this->nh);
    this->wo = make_matrix(this->nh, this->no);
    //并设为随机值
    for (int i = 0; i < this->ni; i++) {
        for(int j = 0, j < this->nh; j++) {
            this->wi[i][j] = rand_num(-0.2, 0.2);
        }
    } 
     for (j = 0; j < this->nh; j++) {
        for(k = 0, k < this->no; k++) {
            this->wo[j][k] = rand_num(-2.0, 2.0);
        }
    }

    //最后建立动量因子（矩阵）
    this->self.ci = make_matrix(this->ni, this->nh);
    this->co = make_matrix(this->nh, this->no);
}

float update(float inputs[])
{
    if len(inputs) != self.ni-1:
        raise ValueError('与输入层节点数不符！')

    # 激活输入层
    for i in range(self.ni-1):
        #self.ai[i] = sigmoid(inputs[i])
        self.ai[i] = inputs[i]

    # 激活隐藏层
    for j in range(self.nh):
        sum = 0.0
        for i in range(self.ni):
            sum = sum + self.ai[i] * self.wi[i][j]
        self.ah[j] = sigmoid(sum)

    # 激活输出层
    for k in range(self.no):
        sum = 0.0
        for j in range(self.nh):
            sum = sum + self.ah[j] * self.wo[j][k]
        self.ao[k] = sigmoid(sum)

    return self.ao[:]
}


float** make_matrix(int row, int column, float fill = 0.0)
{
    float **m = new float *[column]; 

    for (i = 0; i < row; i++) {
        m[i] = new float [column];
        for (j = 0; j < column; j++) {
            m[i][j] = fill;
        }
    }

    return m;
}

float* array(int num, float fill = 0.0)
{
    float* a = new float[num];
    for (int i = 0; i < num; i++) {
        a[i] = fill;
    }
    return a;
}


float rand_num(float min, float max)
{
    float num[10];
    srand((unsigned int)(time(NULL)));/*关于time_t time(0)：time_t被定义为长整型，它返回从1970年1月1日零时零分零秒到目前为止所经过的时间，单位为秒*/
    for (int i = 0; i < 10; i++) {
        num[i] = rand();
    }
    int j = rand() % 10;
    return min + (max - min) * num[j] / RAND_MAX;
}


float sigmoid(float x)
{
    return (exp(x) - exp(-x)) / (exp(x) + exp(-x));
}

//sigmoid函数的导数
float dsigmoid(float y)
{
    return 1.0 - pow(y, 2);
}