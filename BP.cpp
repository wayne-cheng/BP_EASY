#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>

#include "BP.h"

#ifndef RAND_MAX
#define RAND_MAX 0x7fff
#endif

using namespace std;

Bp::Bp(int ni, int nh, int no)
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
        for(int j = 0; j < this->nh; j++) {
            this->wi[i][j] = rand_num(-0.2, 0.2);
        }
    } 
     for (int j = 0; j < this->nh; j++) {
        for(int k = 0; k < this->no; k++) {
            this->wo[j][k] = rand_num(-2.0, 2.0);
        }
    }

    //最后建立动量因子（矩阵）
    this->ci = make_matrix(this->ni, this->nh);
    this->co = make_matrix(this->nh, this->no);
}

void Bp::update(float* inputs)
{
    //激活输入层
    for (int i = 0; i < this->ni - 1; i++) {
        //this->ai[i] = sigmoid(inputs[i])
        this->ai[i] = inputs[i];
    }
    //激活隐藏层
    for (int j = 0; j < this->nh - 1; j++) {
        float sum = 0.0;
        for (int i = 0; i < this->ni; i++) {
            sum = sum + this->ai[i] * this->wi[i][j];
        this->ah[j] = sigmoid(sum);
        }
    }
    //激活输出层
    for (int k = 0; k < this->no; k++) {
        float sum = 0.0;
        for (int j = 0; j < this->nh; j++) {
            sum = sum + this->ah[j] * this->wo[j][k];
        this->ao[k] = sigmoid(sum);
        }
    }

}

float Bp::back_propagate(float* targets, float N, float M)//''' 反向传播 '''
{
    float error = 0.0;
    float change = 0.0;

   // 计算输出层的误差
    float* output_deltas = array(this->no, 0.0);
    for (int k = 0; k < this->no; k++) {
        error = targets[k] - this->ao[k];
        output_deltas[k] = dsigmoid(this->ao[k]) * error;
    }
    // 计算隐藏层的误差
    float* hidden_deltas = array(this->nh, 0.0);
    for (int j = 0; j < this->nh; j++) {
        error = 0.0;
        for (int k = 0; k < this->no; k++)
            error = error + output_deltas[k] * this->wo[j][k];
        hidden_deltas[j] = dsigmoid(this->ah[j]) * error;
    }

    // 更新输出层权重
    for (int j = 0; j < this->nh; j++) {
        for (int k = 0; k < this->no; k++) {
            change = output_deltas[k] * this->ah[j];
            this->wo[j][k] = this->wo[j][k] + N * change + M * this->co[j][k];
            this->co[j][k] = change;
            //print(N * change, M * this->co[j][k])
        }
    }

    // 更新输入层权重
    for (int i = 0; i < this->ni; i++) {
        for (int j = 0; j < this->nh; j++) {
            change = hidden_deltas[j] * this->ai[i];
            this->wi[i][j] = this->wi[i][j] + N * change + M * this->ci[i][j];
            this->ci[i][j] = change;
        }
    }

    // 计算误差
    error = 0.0;
    for (int k = 0; k < this->no; k++)
        error = error + 0.5 * pow((targets[k] - this->ao[k]), 2);
    return error;
}

void Bp::test_result(float inputs[])
{
    this->update(inputs);
    for (int i = 0; i < this->ni - 1; i++)
        cout << this->ai[i] << ",";
    cout << " -> ";
    for (int i = 0; i < this->no; i++)
        cout << this->ao[i] << ",";
    cout << endl;
}

void Bp::print_weights(void)
{
    cout << "输入层权重:" << endl;
    for (int i = 0; i < this->ni; i++)
        cout << this->wi[i] << endl;
    cout << endl;
    cout << "输出层权重:" << endl;
    for (int j = 0; j < this->nh; j++)
        cout << this->wo[j] << endl;
}

void Bp::train(float** inputs, float** targets, int data_num, int iterations, float N, float M)
{
    // N: 学习速率(learning rate)
    // M: 动量因子(momentum factor)
    float error;
    for (int i = 0; i < iterations; i++) {
        error = 0.0;
        for (int j = 0; j < data_num; j++) {
            this->update(inputs[j]);
            error = error + this->back_propagate(targets[j], N, M);
        }
        if (i % 100 == 0)
            printf("误差 %.5f\n", error);
    }
}

float* array(int num, float fill)
{
    float* a = new float[num];
    for (int i = 0; i < num; i++) {
        a[i] = fill;
    }
    return a;
}

float** make_matrix(int row, int column, float fill)
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