#ifndef BP
#define BP

class Bp
{
    public:
        Bp();
        Bp(int ni, int nh, int no);

        void train(float** inputs, float** targets, int data_num, int iterations = 10000, float N = 0.5, float M = 0.1);
        void test_result(float* inputs);
        void print_weights();

    private:
        int ni;
        int nh;
        int no;

        float* ai;
        float* ah;
        float* ao;
        
        float** wi;
        float** wo;

        float** ci;
        float** co;

        float** inputs;
        float** targets;

        void update(float* inputs);
        float back_propagate(float* targets, float N, float M);
};

extern float** make_matrix(int row, int column, float fill = 0.0f);
extern float* array(int num, float fill = 0.0f);
extern float rand_num(float min, float max);
extern float sigmoid(float x);
extern float dsigmoid(float y);

#endif
