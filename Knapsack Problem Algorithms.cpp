#include <iostream>
#include <vector>

using namespace std;

int knapsackDynamic(int W, const vector<int>& weights, const vector<int>& values, int n) {
    vector<vector<int>> dp(n + 1, vector<int>(W + 1, 0));

    for (int i = 1; i <= n; i++) {
        for (int w = 1; w <= W; w++) {
            if (weights[i - 1] <= w) {
                dp[i][w] = max(values[i - 1] + dp[i - 1][w - weights[i - 1]], dp[i - 1][w]);
            } else {
                dp[i][w] = dp[i - 1][w];
            }
        }
    }

    return dp[n][W];
}

int main() {
    int W = 50;
    vector<int> weights = {10, 20, 30};
    vector<int> values = {60, 100, 120};
    int n = weights.size();

    int max_value = knapsackDynamic(W, weights, values, n);

    cout << "Maximum value that can be obtained: " << max_value << endl;

    return 0;
}
