struct SimpleSVM {
    vector<float> weights;
    float bias;
    float C = 1.0f;
    void train(vector<vector<float>>& X, vector<int>& y, int epochs=1000) 
    {
        int n = X.size();
        int dim = X[0].size();
        weights.resize(dim, 0);
        bias = 0;
        for (int epoch = 0; epoch < epochs; ++epoch) 
        {
            for (int i = 0; i < n; ++i) 
            {
                float pred = bias;
                for (int j = 0; j < dim; ++j) pred += weights[j] * X[i][j];
                if (y[i] * pred < 1) //更新
                { 
                    for (int j = 0; j < dim; ++j) weights[j] += C * y[i] * X[i][j];
                    bias += C * y[i];  // 更新偏置
                }
            }
        }
    }
    int predict(vector<float>& x) 
    {
        float score = bias;
        for (int i = 0; i < x.size(); ++i) score += weights[i] * x[i];
        return score > 0 ? 1 : -1;
    }
};
int main() 
{
    SimpleSVM svm;
    vector<vector<float>> X = {{1,2}, {3,4}, {5,6}};//这是一个输入样例
    vector<int> y = {1, -1, 1};
    svm.train(X, y);//训练魔性
    vector<float> test = {2, 3};
    int pred = svm.predict(test);//预测
}