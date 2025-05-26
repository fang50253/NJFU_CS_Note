class SVMMetrics 
{
private:
    vector<double> y_true;
    vector<double> y_pred;
    vector<double> sv_coefs;
public:
    // 构造函数
    SVMMetrics(const vector<double>& true_vals, 
               const vector<double>& pred_vals,
               const vector<double>& support_vector_coefs)
        : y_true(true_vals), y_pred(pred_vals), sv_coefs(support_vector_coefs) {}
    double calculate_R2() 
    {
        double sse = 0.0;
        double sst = 0.0;
        double y_mean = accumulate(y_true.begin(), y_true.end(), 0.0) / y_true.size();
        for(size_t i = 0; i < y_true.size(); ++i) 
        {
            sse += pow(y_true[i] - y_pred[i], 2);
            sst += pow(y_true[i] - y_mean, 2);
        }
        return 1.0 - (sse / sst);
    }
    double accuracy() 
    {
        int correct = 0;
        for(size_t i = 0; i < y_true.size(); ++i) 
        {
            if((y_pred[i] >= 0.5 && y_true[i] == 1) || (y_pred[i] < 0.5 && y_true[i] == 0)) correct++;
        }
        return 1.0*static_cast<double>(correct) / y_true.size();
    }
    double support_vector_ratio(int total_samples) 
    {
        return static_cast<double>(sv_coefs.size()) / total_samples;
    }
};