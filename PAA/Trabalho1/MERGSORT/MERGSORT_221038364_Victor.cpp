#include <iostream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

void merge(vector<int>& arr, int left, int mid, int right)
{
    int n1 = mid - left + 1;
    int n2 = right - mid;

    vector<int> Left(n1), Right(n2);

    for (int i = 0; i < n1; i++)
        Left[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        Right[j] = arr[mid + 1 + j];

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2)
    {
        if (Left[i] <= Right[j])
            arr[k++] = Left[i++];
        else
            arr[k++] = Right[j++];
    }

    while (i < n1) arr[k++] = Left[i++];
    while (j < n2) arr[k++] = Right[j++];
}

void sort(vector<int>& arr, int left, int right)
{
    if (left < right)
    {
        int mid = left + (right - left) / 2;
        sort(arr, left, mid);
        sort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

int main() 
{   
    string s;
    getline(cin, s);
    istringstream iss(s);
    vector<int> numbers;
    int n;

    while (iss >> n) {
        numbers.push_back(n);
    }

    int arr_size = numbers.size();

    sort(numbers, 0, arr_size - 1);

    for(int i = 0; i < arr_size; i++) {
        cout << numbers[i] << (i < arr_size - 1 ? " " : "");
    }

    return 0;
}