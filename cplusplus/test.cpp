#include <iostream>

#include "Bp.h"

#define ITERATIONS 100000
#define DATA_NUM 4

using namespace std;

extern void demo();

int main()
{
    demo();

    return 0;
}

void demo()
{
    int nh = 3;

    // 创建一个神经网络：输入层有两个节点、隐藏层有nh个节点、输出层有一个节点
    Bp mybp = Bp(2, nh, 1);
    int i, j;

    //数据样本：逻辑异或（XOR），可改成其它逻辑
    double inputs[DATA_NUM][2] =  { {0, 0}, 
                                    {0, 1},
                                    {1, 0},
                                    {1, 1} };
    double targets[DATA_NUM][1] = { {1},
                                    {0},
                                    {0},
                                    {1} };

    //进行训练
    for (i = 0; i < ITERATIONS; i++) {
        mybp.error_total = 0.0;
        for (j = 0; j < DATA_NUM; j++)
            mybp.train(inputs[j], targets[j]);
        if (i % 1000 == 0)
            cout << "error_total=" << mybp.error_total << endl;
    }

    // 测试训练的成果
    // mybp.print_weights();// 看看训练好的权重（当然可以考虑把训练好的权重持久化）
    for (i = 0; i < 4; i++)
    {
        mybp.test_result(inputs[i]);
    }
}
