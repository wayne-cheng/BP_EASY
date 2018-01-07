#ifndef BP
#define BP

class BP()
{
    public:
        BP();
        BP(int ni, int nh, int no);
       
        void sigmoid(x);
        void train(self, patterns, iterations=1000, N=0.5, M=0.1);
        void weights(self);

    private:
        int ni;
        int nh;
        int no;
        double input;
        double w;
        double output;
        float wi = makeMatrix(this->ni, this->nh)
        float wo = makeMatrix(this->nh, this->no)

        int update(self, inputs);
        int backPropagate(self, targets, N, M):;
};

extern void make_matrix();
extern void rand();

#endif
