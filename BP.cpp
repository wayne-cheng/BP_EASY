#include <iostream>
#include <cstdlib>
#include <ctime>

#include "BP.h"

#ifndef RAND_MAX
#define RAND_MAX 0x7fff
#endif

using namespace std;

BP::BP(int ni, int nh, int no)
{
    this->ni = ni + 1 //增加一个偏差节点
    this->nh = nh
    this->no = no

    //激活神经网络的所有节点（向量）
    this->ai = [1.0]*self.ni
    this->ah = [1.0]*self.nh
    this->ao = [1.0]*self.no
        
    //建立权重（矩阵）
    this->wi = makeMatrix(this->ni, this->nh)
    this->wo = makeMatrix(this->nh, this->no)    
    //设为随机值
    for (int i = 0; i < this->ni; i++) {
        for(int j = 0, j < this->nh; j++) {
            this->wi[i][j] = rand(-0.2, 0.2)
        }
    }
          
     for (j = 0; j < this->nh; j++) {
        for(k = 0, k < this->no; k++) {
            this->wo[j][k] = rand(-2.0, 2.0)
        }
    }

    //最后建立动量因子（矩阵）
    self.ci = makeMatrix(self.ni, self.nh)
    self.co = makeMatrix(self.nh, self.no)
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

float rand_num(float min, float max)
{
    srand((unsigned int)(time(NULL)));
    rand();
    return min + (max - min) * rand() / RAND_MAX;
}
/*关于time_t time(0)：  
* time_t被定义为长整型，它返回从1970年1月1日零时零分零秒到目前为止所经过的时间，单位为秒
*/

