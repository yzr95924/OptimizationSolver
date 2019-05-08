#include "solver.h"

int main(int argc, char* argv[]) {
    int n = 0;
    int totalChunk = 0;
    int m;
    vector<pair<string, int> > input;
    input.push_back(make_pair<string, int>("c1", 9));
    input.push_back(make_pair<string, int>("c2", 8));
    input.push_back(make_pair<string, int>("c3", 4));
    input.push_back(make_pair<string, int>("c4", 4));
    input.push_back(make_pair<string, int>("c5", 3));
    input.push_back(make_pair<string, int>("c6", 2));
    for (auto iter = input.begin(); iter != input.end(); iter++){
        n++;
        totalChunk += iter->second;
    }
    printf("n:%d, total logicl chunk:%d\n", n, totalChunk);
    scanf("%d", &m);
    printf("m: %d\n", m);
    OpSolver* solver = new OpSolver(m, input);
    printf("Check 1\n");
    solver->GetOptimal();
    solver->PrintResult();
    return 0;
}