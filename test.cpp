#include <iostream>

#include "BP.h"

using namespace std;

extern void demo();

int main()
{
    demo();

    return 0;
}

void demo()
{
    int ni = 2;
    int nh = 2;
    int no = 1;
    // 创建一个神经网络：输入层有两个节点、隐藏层有两个节点、输出层有一个节点
    Bp mybp = Bp(ni, nh, no);

    //一个演示：教神经网络学习逻辑异或（XOR）------------可以换成你自己的数据试试
    int data_num = 4;
        
    float** inputs = make_matrix(data_num, nh);
    float** targets = make_matrix(data_num, no);

    float eg_inputs[data_num][ni] = {  
                                    {0,0}, 
                                    {0,1},
                                    {1,0},
                                    {1,1}};
    float eg_targets[data_num][no] = {
                                    {0},
                                    {1},
                                    {1},
                                    {0}};

    for (int i = 0; i < data_num; i++) {
        inputs[i] = (float *)&eg_inputs[i];
        targets[i] = (float *)&eg_targets[i];
    }

    // 用一些模式训练它
    mybp.train(inputs, targets, data_num);
    // 测试训练的成果（不要吃惊哦）
    for (int i = 0; i < data_num; i++)
    {
        mybp.test_result(inputs[data_num]);
    }
    // 看看训练好的权重（当然可以考虑把训练好的权重持久化）
    //n.weights()
}
   