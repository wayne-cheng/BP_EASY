#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>

#include "Bp.h"

//范围X~Y的随机浮点数
#define RAND_DOUBLE(X, Y) ((Y - X) * rand() / RAND_MAX + X)

using namespace std;

Bp::Bp(int ni, int nh, int no)
{
    //各层节点数
    this->ni = ni;
    this->nh = nh;
    this->no = no;

    srand((unsigned int)(time(0)));

    //激活神经网络的所有节点（向量）
    this->ai = new double[this->ni];
    this->ah = new double[this->nh];
    this->ao = new double[this->no];
    
    //建立权重（矩阵），并设为随机值 
    this->wi = make_matrix(this->ni, this->nh, -0.2, 0.2);
    this->wo = make_matrix(this->nh, this->no, -2.0, 2.0);
 
    //最后建立动量因子（矩阵）
    //this->ci = make_matrix(this->ni, this->nh);
    //this->co = make_matrix(this->nh, this->no);
    

    this->error_total = 0.0;//记录一组样本训练的总误差
}

//前向输出
void Bp::update(double inputs[])
{
    double sum;
    int i, j, k;

    //激活输入层
    for (i = 0; i < this->ni; i++) 
        this->ai[i] = inputs[i];
    //激活隐藏层
    for (j = 0; j < this->nh; j++) {
        sum = 0.0;
        for (i = 0; i < this->ni; i++)
            sum += this->ai[i] * this->wi[i][j];
        this->ah[j] = sigmoid(sum);
    }
    //激活输出层
    for (k = 0; k < this->no; k++) {
        sum = 0.0;
        for (j = 0; j < this->nh; j++)
            sum += this->ah[j] * this->wo[j][k];
        this->ao[k] = sigmoid(sum);
    }
}

//反向传播 N: 学习速率(learning rate) M: 动量因子(momentum factor)
void Bp::back_propagate(double* targets, double N)//, double M)
{
    int i, j, k;
    double error;
    double change;
    double output_deltas[this->no];
    double hidden_deltas[this->nh];

    // 计算输出层的误差
    for (k = 0; k < this->no; k++) {
        error = targets[k] - this->ao[k];
        output_deltas[k] = dsigmoid(this->ao[k]) * error;
    }
    // 计算隐藏层的误差
    for (j = 0; j < this->nh; j++) {
        error = 0.0;
        for (k = 0; k < this->no; k++)
            error += output_deltas[k] * this->wo[j][k];
        hidden_deltas[j] = dsigmoid(this->ah[j]) * error;
    }
    // 更新输出层权重
    for (j = 0; j < this->nh; j++) {
        for (k = 0; k < this->no; k++) {
            change = output_deltas[k] * this->ah[j];
            this->wo[j][k] +=  N * change; //+ M * this->co[j][k];
            //this->co[j][k] = change;
            //print(N * change, M * this->co[j][k])
        }
    }
    // 更新输入层权重
    for (i = 0; i < this->ni; i++) {
        for (j = 0; j < this->nh; j++) {
            change = hidden_deltas[j] * this->ai[i];
            this->wi[i][j] += N * change;// + M * this->ci[i][j];
            //this->ci[i][j] = change;
        }
    }
    // 计算误差
    error = 0.0;
    for (k = 0; k < this->no; k++)
        error += 0.5 * pow((targets[k] - this->ao[k]), 2);
    this->error_total += error;
}

void Bp::train(double inputs[], double targets[])
{
    this->update(inputs);
    this->back_propagate(targets);
}

void Bp::test_result(double inputs[])
{
    int i;
    this->update(inputs);
    for (i = 0; i < this->ni; i++)
        cout << this->ai[i] << ",";
    cout << " -> ";
    for (i = 0; i < this->no; i++)
        cout << this->ao[i] << ",";
    cout << endl;
}

void Bp::print_weights(void)
{
    int i, j , k;
    cout << "wi[][] is " << endl;
    for (i = 0; i < this->ni; i++) {
        for (j = 0; j < this->nh; j++)
            cout << this->wi[i][j] << " ";
        cout << endl;
    }
    cout << "wo[][] is " << endl;
    for (j = 0; j < this->nh; j++) {
        for (k = 0; k < this->no; k++)
            cout << this->wo[j][k] << " ";
        cout << endl; 
    }
}

double** make_matrix(int row, int column, double min, double max)
{
    int i, j;
    double **m = new double* [row];//列数不能为1，暂定为10. 不能定为变量，原因需排查

    for (i = 0; i < row; i++) {
        m[i] = new double [column];
        for (j = 0; j < column; j++) {
            m[i][j] = RAND_DOUBLE(min, max);
        }
    }

    return m;
}

//激活函数sigmoid
double sigmoid(double x)
{
    //return (exp(x) - exp(-x)) / (exp(x) + exp(-x));
    return 1.0 / (1.0 + exp(-x));
}

//sigmoid函数的导数
double dsigmoid(double y)
{
    //return 1.0 - pow(y, 2);
    return y * (1 - y);
}
