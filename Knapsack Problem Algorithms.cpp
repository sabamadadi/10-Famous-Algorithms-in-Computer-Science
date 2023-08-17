#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Item {
    int value;
    int weight;
};

bool compareItems(const Item& item1, const Item& item2) {
    double ratio1 = static_cast<double>(item1.value) / item1.weight;
    double ratio2 = static_cast<double>(item2.value) / item2.weight;
    return ratio1 > ratio2;
}

int knapsackGreedy(int W, const vector<Item>& items) {
    sort(items.begin(), items.end(), compareItems);

    int totalValue = 0;
    int totalWeight = 0;

    for (const auto& item : items) {
        if (totalWeight + item.weight <= W) {
            totalValue += item.value;
            totalWeight += item.weight;
        } else {
            int remainingWeight = W - totalWeight;
            totalValue += static_cast<double>(remainingWeight) / item.weight * item.value;
            break;
        }
    }

    return totalValue;
}

int main() {
    int W = 50;
    vector<Item> items = {
        {60, 10},
        {100, 20},
        {120, 30}
    };

    int max_value = knapsackGreedy(W, items);

    cout << "Maximum value that can be obtained: " << max_value << endl;

    return 0;
}
