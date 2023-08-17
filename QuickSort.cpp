#include <iostream>
#include <vector>

using namespace std;

int partition(vector<int>& arr, int low, int high) {
    int pivot = arr[high]; // Choose the last element as the pivot
    int i = low - 1; // Index of the smaller element

    for (int j = low; j < high; j++) {
        if (arr[j] < pivot) {
            i++;
            swap(arr[i], arr[j]); // Swap elements at indices i and j
        }
    }

    swap(arr[i + 1], arr[high]); // Swap the pivot element with the element at index i+1
    return i + 1; // Return the index of the pivot element
}

void quickSort(vector<int>& arr, int low, int high) {
    if (low < high) {
        int pivotIndex = partition(arr, low, high);

        quickSort(arr, low, pivotIndex - 1); // Sort the elements before the pivot
        quickSort(arr, pivotIndex + 1, high); // Sort the elements after the pivot
    }
}

int main() {
    vector<int> arr = {9, 2, 5, 1, 7, 6, 8, 3, 4};
    int n = arr.size();

    cout << "Original array: ";
    for (int num : arr) {
        cout << num << " ";
    }
    cout << endl;

    quickSort(arr, 0, n - 1);

    cout << "Sorted array: ";
    for (int num : arr) {
        cout << num << " ";
    }
    cout << endl;

    return 0;
}
