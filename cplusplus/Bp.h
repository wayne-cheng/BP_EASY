#ifndef BP
#define BP

class Bp
{
    public:
        int ni;
        int nh;
        int no;
        double error_total;
        
        Bp(int ni, int nh, int no);
        void train(double inputs[], double targets[]);
        void print_weights();
        void test_result(double inputs[]);

    private:
        double* ai;
        double* ah;
        double* ao;
        
        double** wi;
        double** wo;

        // double** ci;
        // double** co;

        double** inputs;
        double** targets;

        void update(double inputs[]);
        void back_propagate(double targets[], double N = 0.5);//, double M = 0.1);
};

extern double** make_matrix(int row, int column, double min = 0.0, double max = 0.0);

extern double sigmoid(double x);
extern double dsigmoid(double y);

#endif
