#ifndef TESTRESULT_H
#define TESTRESULT_H

#include <QObject>

using namespace std;

class TestResult
{
public:
    TestResult(double _RMSE, vector<vector<double>> _output_values, vector<double> _errorVec);
    vector<vector<double>> getOutputValues() {return output_values;}
    vector<double> getRMSEVec(){return errorVec;}
    double getRMSE(){return RMSE;}
private:
    vector<vector<double>> output_values;
    vector<double> errorVec;
    double RMSE;
};

#endif // TESTRESULT_H
