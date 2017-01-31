#include "testresult.h"

TestResult::TestResult(double _RMSE, vector<vector<double>> _output_values, vector<double> _errorVec):
RMSE(_RMSE), output_values(_output_values), errorVec(_errorVec)
{
}
