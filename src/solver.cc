#include "solver.h"

double Log2(double number) {
    return log(number) / log(2);
}

OpSolver::OpSolver(int m, vector<pair<string, int> > inputDistribution) {
    m_ = m;
    n_ = inputDistribution.size();
    storageBlow_ = m_ / n_;
    inputFeqDistr_ = inputDistribution;
    maxEntropy_ = 0;
    int i;
    for (auto iter = inputDistribution.begin(); iter != inputDistribution.end(); iter++) {
        sum_ += iter->second;
    }
    /**Initialization */
    float average = (float)sum_ / m_;
    if (sum_ % m_ != 0) {
        printf("the output maybe float\n");
       
    }
    printf("the initialized average: %lf\n", average);

    for (int i = 0; i < m; i++) {
        outputFeqDistr_.push_back(average);
    }
    remainSum_ = sum_;
    double freq = 1 / sum_;
    for (i = 0; i < sum_; i++) {
        maxEntropy_ -= freq * Log2(freq);
    }
    printf("The maximum workload of this workload: %f\n", maxEntropy_);
}

void OpSolver::PrintResult() {
    printf("Total Plaintext Logical Chunk Amount: %d\n", sum_);
    float csum = 0;
    for (auto iter = outputFeqDistr_.begin(); iter != outputFeqDistr_.end(); iter++) {
        csum += *iter;
        printf("%lf, ", *iter);
    }
    printf("\n");
    printf("Total Ciphertext Logical Chunk Amount: %lf\n", csum);
    double originlRatio = static_cast<double> (sum_ - n_) / sum_;
    double cipherRatio = static_cast<double> (sum_ - m_) / sum_;
    printf("Original Storage Saving Rate: %f\n", originlRatio);
    printf("Cipher Storage Saving Rate: %f\n", cipherRatio);
    printf("Storage Saving Loss Rate: %f\n", (originlRatio - cipherRatio) / cipherRatio);
    double 

}

void OpSolver::GetOptimal() {
    /**sort the inputFeqDistr_ */
    sort(inputFeqDistr_.begin(), inputFeqDistr_.end(), [=](pair<string, int> a, pair<string, int> b)
    { return a.second < b.second;});

    if (DEBUG) {
        for (auto iter = inputFeqDistr_.begin(); iter != inputFeqDistr_.end(); iter++) {
            printf("%s, %d\n", iter->first.c_str(), iter->second);
        }
    }
    int finishItem = 0;
    float newAverage = 0;
    int startIndex = 0;
    while (1) {
        if (CheckConstrain(startIndex)) {
            break;
        } else {
            outputFeqDistr_[currentIndex_] = inputFeqDistr_[currentIndex_].second;
            finishItem ++;
            remainSum_ -= outputFeqDistr_[currentIndex_];
            newAverage = (float)remainSum_ / (float)(m_ - finishItem);
            for (int i = currentIndex_+1; i < m_; i++) {
                outputFeqDistr_[i] = newAverage;
            }
            startIndex = currentIndex_ + 1;
        }
        //printf("Iteration: %d, remainSum_: %d, newAverage_: %lf\n", finishItem, remainSum_, newAverage);
        //PrintResult();
    }
}

bool OpSolver::CheckConstrain(int startIndex) {
    int flag = 1;
    int counter = startIndex;
    while (counter < n_) {
        if (inputFeqDistr_[counter].second < outputFeqDistr_[counter]){
            flag = 0;
            /**store the current counter*/
            currentIndex_ = counter;
            break;    
        }
        counter++;
    }

    if (flag) {
        return true;
    } else {
        return false;
    }
}



