#include <iostream>
#include <vector>

using namespace std;

int binarySearch(const vector<int>& arr, int target) {
    int left = 0;
    int right = arr.size() - 1;

    while (left <= right) {
        int mid = left + (right - left) / 2;

        if (arr[mid] == target) {
            return mid; // Found the target element at index mid
        } else if (arr[mid] < target) {
            left = mid + 1; // Continue searching in the right half
        } else {
            right = mid - 1; // Continue searching in the left half
        }
    }

    return -1; // Target element not found
}

int main() {
    vector<int> arr = {2, 5, 8, 12, 16, 23, 38, 56, 72, 91};
    int target = 23;

    int index = binarySearch(arr, target);

    if (index != -1) {
        cout << "Element " << target << " found at index " << index << endl;
    } else {
        cout << "Element " << target << " not found in the array" << endl;
    }

    return 0;
}
