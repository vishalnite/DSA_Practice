#include<bits/stdc++.h>
using namespace std;

void sortArr(vector<int> &arr) {
    int n = arr.size();
    for(int i = 0; i < n; i++) {
        int mini = i;
        for(int j = i + 1; j < n; j++) {
            if(arr[j] < arr[i]) 
                mini = j;
        }
        int temp = arr[mini];
        arr[mini] = arr[i];
        arr[i] = temp; 
    }
}

int main() {
    vector<int> arr = {1, 2, 4, 6, 5, 3, 8, 9, 7, 0};
    int n = arr.size();
    vector<int> temp;

    for(int i = 0; i < n; i++) {
        if(arr[i] % 2 == 0)
            temp.push_back(arr[i]);
    }

    //sort
    sortArr(temp);

    int k = 0;
    for(int i = 0; i < n; i += 2) {
        if(arr[i] % 2 != 0) {
            arr[i + 1] = arr[i];   
        }
        arr[i] = temp[k++];
    }

    cout << "Array elements: " << endl;
    for(int i = 0; i < n; i++) 
        cout << arr[i] << " ";
    cout << endl;

    return 0;
}