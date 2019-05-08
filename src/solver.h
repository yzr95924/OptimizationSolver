#ifndef SIME_OP_SOLVER_H_
#define SIME_OP_SOLVER_H_
#include <vector>
#include <map>
#include <string>
#include <iostream>
#include <algorithm>
#include <stdio.h>
#include <math.h>
#include <cmath>


#define DEBUG 1

using namespace std;

class OpSolver {
    public:
        OpSolver(int m, vector<pair<string, int> > inputDistribution);
        ~OpSolver();
        void GetOptimal();
        void PrintResult();
        bool CheckConstrain(int startIndex);
        bool Compare(pair<string, int> a, pair<string, int> b);
        
    private:
        int m_;
        int n_;
        int sum_;
        int currentIndex_;
        int remainSum_;
        double storageBlow_;
        double maxEntropy_;
        double 

        vector<pair<string, int> > inputFeqDistr_;  
        //std::vector<pair<string, float> > outputFeqDistr_;
        vector<float> outputFeqDistr_;      
};

#endif