#include <iostream>
#include <vector>

using namespace std;

long long merge(vector<int>& arr, int left, int mid, int right)
{
    int n1 = mid - left + 1;
    int n2 = right - mid;

    vector<int> Left(n1), Right(n2);

    for (int i = 0; i < n1; i++)
        Left[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        Right[j] = arr[mid + 1 + j];

    int i = 0, j = 0, k = left;
    long long inversions = 0;

    while (i < n1 && j < n2)
    {
        if (Left[i] <= Right[j])
        {
            arr[k++] = Left[i++];
        }
        else
        {
            arr[k++] = Right[j++];
            inversions += (n1 - i);
        }
    }

    while (i < n1) arr[k++] = Left[i++];
    while (j < n2) arr[k++] = Right[j++];

    return inversions;
}

long long sort(vector<int>& arr, int left, int right)
{
    long long inversions = 0;

    if (left < right)
    {
        int mid = left + (right - left) / 2;

        inversions += sort(arr, left, mid);
        inversions += sort(arr, mid + 1, right);
        inversions += merge(arr, left, mid, right);
    }

    return inversions;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;

    while (T--)
    {
        int N;
        cin >> N;

        vector<int> arr(N);

        for (int i = 0; i < N; i++)
            cin >> arr[i];

        cout << sort(arr, 0, N - 1) << "\n";
    }

    return 0;
}