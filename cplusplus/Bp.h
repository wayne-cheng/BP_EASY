#ifndef BP
#define BP

class Bp
{
    public:
        int ni;
        int nh;
        int no;
        double error_total;
        
        Bp();
        Bp(int ni, int nh, int no);
        void train(double inputs[], double targets[]);
        void test_result(double inputs[]);
        void print_weights();

    private:
        double* ai;
        double* ah;
        double* ao;
        
        double** wi;
        double** wo;

        double** ci;
        double** co;

        double** inputs;
        double** targets;

        void update(double inputs[]);
        void back_propagate(double targets[], double N = 0.5, double M = 0.1);
};

extern double** make_matrix(int row, int column, double fill = 0.0);
extern double* array(int num, double fill = 0.0);
extern double rand_num(double min, double max);
extern double sigmoid(double x);
extern double dsigmoid(double y);

#endif
