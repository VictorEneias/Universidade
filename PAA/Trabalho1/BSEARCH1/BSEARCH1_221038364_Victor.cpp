#include <iostream>
#include <vector>

using namespace std;

int binarySearchFirst(const vector<int>& arr, int target)
{
    int left = 0;
    int right = arr.size() - 1;
    int answer = -1;

    while (left <= right)
    {
        int mid = left + (right - left) / 2;

        if (arr[mid] == target)
        {
            answer = mid;
            right = mid - 1;
        }
        else if (arr[mid] < target)
        {
            left = mid + 1;
        }
        else
        {
            right = mid - 1;
        }
    }

    return answer;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, Q;
    cin >> N >> Q;

    vector<int> arr(N);

    for (int i = 0; i < N; i++)
    {
        cin >> arr[i];
    }

    for (int i = 0; i < Q; i++)
    {
        int x;
        cin >> x;
        cout << binarySearchFirst(arr, x) << "\n";
    }

    return 0;
}