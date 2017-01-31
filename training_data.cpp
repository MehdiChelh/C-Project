#include "training_data.h"


Training_Data::Training_Data(vector<unsigned> topology): QObject(),
  Net(Neural_Net(topology))
{
}

void Training_Data::Train(unsigned int nb_iteration_base, double val_alpha,
                          double val_eta, vector<vector<double>> input_values,
                          vector<vector<double>> target_values)
{
    m_val_eta= val_eta;
    m_val_alpha = val_alpha;
    m_mean_error.push_back(double());
    double sum = 0.0;
    vector<double> result_value;
    vector<vector<double>> result_values;
    vector<double> input;
    vector<double> target;
    for (unsigned nb_iteration = 0; nb_iteration < nb_iteration_base;++nb_iteration) {
        sum = 0.0;
        for (unsigned s = 0; s < input_values.size(); ++s) {
            for (unsigned nb_input = 0; nb_input < input_values[0].size(); ++nb_input)
            {
                input.push_back(input_values[s][nb_input]);
                target.push_back(target_values[s][nb_input]);

            };
            Net.Feed_Forward(input);
            Net.Get_Results(result_value);
            m_result_value.push_back(result_value);
            Net.Generalized_Delta_Rule(target,val_alpha,val_eta);
            target.clear();
            input.clear();
            sum += Net.Get_Error();
            this->progressValueChanged(nb_iteration*input_values.size() + s+1);
        };
//        m_mean_error.push_back((sum)/input_values[0].size());
        newMSE(QStringLiteral("%1_%2").arg(nb_iteration + 1).arg((sum)/input_values[0].size()));
    };
}

TestResult Training_Data::Test(vector<vector<double>> input_values, vector<vector<double>> target_values)
{
    vector<double> input;
    vector<double> target;
    vector<vector<double>> result_values;
    vector<double> result_value;
    vector<double> error;
    double sum = 0;
    for (unsigned s = 0; s < input_values.size(); ++s) {
        for (unsigned nb_input = 0; nb_input < input_values[0].size(); ++nb_input)
        {
            input.push_back(input_values[s][nb_input]);
            target.push_back(target_values[s][nb_input]);

        };
        Net.Feed_Forward(input);
        Net.Get_Results(result_value);
        result_values.push_back(result_value);
        Net.CalculateRMSE(target);
        target.clear();
        input.clear();
        sum += Net.Get_Error();
        error.push_back(Net.Get_Error());
    };
    TestResult result(sum/input_values[0].size(), result_values, error);
    return result;
}
