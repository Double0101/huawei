#include "utils.h"
#include <iostream>
#include <vector>
#include "LinearRegression.h"
#include "TrainingData.h"
#include "common.h"

using namespace std;

//void dot(vector<double> &x, vector<double> &y, vector<double> &z);
void showVec(vector<int> &x)
{
        for (int i = 0; i < int(x.size()); i++) {
                cout<<x[i]<< " ";
        }  cout<<endl;
}

void showMat(vector< vector<int> > &matrix)
{
        for (int i = 0; i < int(matrix.size()); i++) {
                showVec(matrix[i]);
        }
}

double dot(vector<double> &x, vector<int> &y)
{
        if (x.size() != y.size()) {
                cout<< "vector dims not match"<<endl;
        }

        double s = 0.;
        for (int i = 0; i < int(x.size()); i++) {
                s += x[i] * y[i];
        }
        return s;
}

void train(const char* train_file_path, double alpha, int dimensions, \
                int num_iter, int duration, vector<int> &flavors, \
                vector<int> &results)
{
        TrainingData data(train_file_path, dimensions);
        //cout<<"cols: "<<data.cols<<endl;
        vector< vector< vector<int> > > Xs;
        vector< vector<int> > Ys;
        //cout<<"Preparing Data:"<<endl;
        for (int i = 0; i < int(flavors.size()); i++) {
                int flavor = flavors[i];
                vector< vector<int> > X;
                vector<int> Y;
                data.getXY(flavor, X, Y);
                //cout<<"X.size(): "<<X.size()<<endl;
                //cout<<"Y.size(): "<<Y.size()<<endl;
                Xs.push_back(X);
                Ys.push_back(Y);
        }
        //cout<<"flavors: "<<flavors.size()<<endl;

        //cout<<"Start Training:"<<endl;
        for (int i = 0; i < int(flavors.size());i ++) {
                int flavor = flavors[i];
                //cout<<"For flavor "<<flavor<<endl;
                LinearRegression lr(dimensions, num_iter, alpha);
                //cout<<"Xs[i].size(): "<<Xs[i].size()<<endl;
                //cout<<"Ys[i].size(): "<<Ys[i].size()<<endl;
                lr.fit(Xs[i], Ys[i]);  // train

                //lr.dispParas();

                data.prediction(flavor, duration, lr);  // predict
                //cout<<endl<<endl;
        }

        for (int i = 0; i < int(flavors.size()); i++) {  // get the result
                int flavor = flavors[i];
                results.push_back( data.calculateSum(flavor, data.cols, data.cols + duration - 1) );

        }
}


string allot(int CPU,int MEM,vector<int> flist,vector<int> numlist,int dim){

        //for (int i = 0; i < (int)numlist.size(); i++) {
        //        cout<<numlist[i]<<" ";
        //}  cout<<endl;
        int fcpu[15] = {1,1,1,2,2,2,4,4,4 ,8,8 ,8 ,16,16,16};
        int fmem[15] = {1,2,4,2,4,8,4,8,16,8,16,32,16,32,64};
        machineGroup machines = machineGroup();
        int numindex = -1;
        for(auto index : flist){
                numindex+=1;
                for(int number =0;number <numlist[numindex];number++){
                        int machineIndex = -1;
                        for(int i=0 ;i < int(machines.machinelist.size());i++){
                                if(machines.machinelist[i].cpu > fcpu[index] and machines.machinelist[i].mem>fmem[index]) {
                                        machineIndex = i;
                                        break;
                                }
                        }
                        if(machineIndex!=-1){
                                machines.change_machine(machineIndex,index);
                        }else {
                                machine new_machine = machine(CPU,MEM);
                                machines.add_machine(new_machine);
                                machines.change_machine(machines.machinelist.size()-1,index);
                        }
                }
        }
        string output_result = "";
        int sum = 0;
        for (int i = 0; i < (int)numlist.size(); i++) {
                sum += numlist[i];
        }
        output_result += to_string(sum) + "\n";
        for (int i = 0; i < (int)flist.size(); i++) {
                output_result += string("flavor") + to_string(flist[i] + 1) + " " + to_string(numlist[i]) + "\n";
        }
        output_result += "\n";

        output_result += to_string(machines.machinelist.size());
        //output_result += "\n";
        for(int i = 0;i < int(machines.machinelist.size());i++){
                output_result+="\n";
                output_result+= to_string(i+1);
                for(auto j=machines.machinelist[0].fdict.begin();j!=machines.machinelist[0].fdict.end();j++){
                        output_result+=" flavor";
                        output_result+=to_string(j->first+1);
                        output_result+=" ";
                        output_result+=to_string(j->second);
                }
        }
        //cout <<output_result;
        return output_result;
}
