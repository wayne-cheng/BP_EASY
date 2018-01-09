#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>

#include "Bp.h"

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
    srand((unsigned int)(time(0)));
    cout << "wi is :"<< endl;
    for (int i = 0; i < this->ni; i++) {
        for(int j = 0; j < this->nh; j++) {
            this->wi[i][j] = rand_num(-0.2, 0.2);
            cout << this->wi[i][j] << " ";
        }
        cout << endl;
    } 

    cout << "wo is :"<< endl;
    for (int j = 0; j < this->nh; j++) {
        for(int k = 0; k < this->no; k++) {
            this->wo[j][k] = rand_num(-2.0, 2.0);
            cout << this->wi[j][k] << " ";
        }
        cout << endl;
    }

    //最后建立动量因子（矩阵）
    this->ci = make_matrix(this->ni, this->nh);
    this->co = make_matrix(this->nh, this->no);

    this->error = 0.0;
}

void Bp::update(double inputs[])
{
    double sum;
    //激活输入层
    for (int i = 0; i < this->ni - 1; i++) {
        //this->ai[i] = sigmoid(inputs[i])
        this->ai[i] = inputs[i];
    }
    //激活隐藏层
    for (int j = 0; j < this->nh - 1; j++) {
        sum = 0.0;
        for (int i = 0; i < this->ni; i++)
            sum = sum + this->ai[i] * this->wi[i][j];
        this->ah[j] = sigmoid(sum);
    }
    //激活输出层
    for (int k = 0; k < this->no; k++) {
        sum = 0.0;
        for (int j = 0; j < this->nh; j++)
            sum = sum + this->ah[j] * this->wo[j][k];
        this->ao[k] = sigmoid(sum);
    }
}

double Bp::back_propagate(double* targets, double N, double M)//''' 反向传播 '''
{
    double error;
    double change;

   // 计算输出层的误差
    double* output_deltas = array(this->no);
    for (int k = 0; k < this->no; k++) {
        error = targets[k] - this->ao[k];
        output_deltas[k] = dsigmoid(this->ao[k]) * error;
    }
    // 计算隐藏层的误差
    double* hidden_deltas = array(this->nh);
    for (int j = 0; j < this->nh; j++) {
        error = 0.0f;
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

void Bp::test_result(double inputs[])
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

void Bp::train(double* inputs, double* targets, double N, double M)
{
    // N: 学习速率(learning rate)
    // M: 动量因子(momentum factor)
    this->update(inputs);
    this->error = this->error + this->back_propagate(targets, N, M);
}


double* array(int num, double fill)
{
    double* a = new double[num];
    for (int i = 0; i < num; i++) {
        a[i] = fill;
    }
    return a;
}

double** make_matrix(int row, int column, double fill)
{
    double **m = new double *[column];

    for (int i = 0; i < row; i++) {
        m[i] = new double [column];
        for (int j = 0; j < column; j++) {
            m[i][j] = fill;
        }
    }

    return m;
}

double rand_num(double min, double max)
{
    return min + (max - min) * rand() / RAND_MAX;
    
}

//激活函数sigmoid
double sigmoid(double x)
{
    return (exp(x) - exp(-x)) / (exp(x) + exp(-x));
}

//sigmoid函数的导数
double dsigmoid(double y)
{
    return 1.0 - y * y;
}