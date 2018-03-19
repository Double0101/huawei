#ifndef LINEARRGRESSION_H
#define LINEARRGRESSION_H

#include "utils.h"
#include <vector>
#include "matrix.h"

class LinearRegression {
        public:
                LinearRegression(int dims, int num_iter, double alpha);

                int predict(std::vector<int> &x);

                void fit(std::vector< std::vector<int> > &X, std::vector<int> &Y);

                void dispParas();

        public:
                int dimensions;
                int num_iter;
                std::vector<double> theta;
                double intercept;
                double alpha;
                Matrix coef;
                std::vector<double> J_hist;

};

#endif
