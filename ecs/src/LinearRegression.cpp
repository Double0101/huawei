#include "LinearRegression.h"
#include <iostream>
#include <vector>
#include <cstdlib>
#include "matrix.h"
using namespace std;

LinearRegression::LinearRegression(int dims, int num_iter, double alpha): coef(dims + 1, 1)
{
        dimensions = dims;
        this->num_iter = num_iter;
        for (int i = 0; i < dimensions; i++) {  //consider the intercept item
                theta.push_back(0.0);  // initialize all to 0
        }
        this->intercept = 0.0;
        this->alpha = alpha;
}

double computeCost(Matrix &X, Matrix &Y, Matrix &coef_)
{
        double J = Matrix::dotProduct((X * coef_ - Y), (X * coef_ - Y)) / (2 * X.rows_);
        return J;
}

void LinearRegression::fit(vector< vector<int> > &X, vector<int> &Y)
{
        Matrix XX(X.size(), X[0].size() + 1);
        for (int i = 0; i < (int)X.size(); i++) {
                for (int j = 0; j < (int)X[i].size(); j++) {
                        XX(i, j) = X[i][j];
                }
                XX(i, X[0].size()) = 1;  // tail 1
        }

        Matrix YY(Y.size(), 1);
        for (int i = 0; i < (int)Y.size(); i++) {
                YY(i, 0) = Y[i];
        }
        //cout<<XX<<endl<<YY<<endl;

        // Now, I have XX and YY and coef
        //cout<<XX<<endl;
        //cout<<YY.transpose()<<endl;
        for (int i = 0; i < num_iter; i++) {  // update the coefficient
                Matrix tmp = XX;
                //cout<<alpha / X.size()<<endl;
                //cout<<coef<<endl;
                coef = coef - (alpha / X.size()) * XX.transpose() * (tmp * coef - YY);

                //cout<<coef<<endl;
                for (int j = 0; j < dimensions + 1; j++) {
                        if (coef(j, 0) > 30) //exit(-1);
                        for (int i = 0; i < dimensions; i++) {
                                theta[i] = coef(i, 0);
                        }
                        intercept = coef(dimensions, 0);
                        return ;
                }

                J_hist.push_back(computeCost(XX, YY, coef));
        }


        for (int i = 0; i < dimensions; i++) {
                theta[i] = coef(i, 0);
        }
        intercept = coef(dimensions, 0);
}

int LinearRegression::predict(vector<int> &x)
{
        double pred_y = dot(theta, x) + intercept ;
        if (pred_y > 0) {
                int tmp_y = (int)pred_y;
                if (pred_y - tmp_y >= 0.5)
                        pred_y = int(pred_y) + 1;
        }
        return pred_y > 0 ? int(pred_y) : 0;
}

void LinearRegression::dispParas()
{
        cout<<"Thetas: ";
        for (int i = 0; i < dimensions; i++) {
                cout << theta[i]<<" ";
        } cout<<endl;
        cout<<"Intercept: "<<intercept<<endl;
}
