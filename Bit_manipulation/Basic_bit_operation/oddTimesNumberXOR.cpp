// Find the number which occurs odd number of times in an array
// Brute Force - Find the count of each number using either sorting or hashmap then, check whether the count is odd or even - O(nlogn)
// Efficient approach - Since XOR of a number with itself is zero. We calculate the XOR of all the numbers in the array and the number 
// which appears odd number of times remains.

#include<iostream>
using namespace std;

int main() {

    int arr[] = {1, 3, 4, 4, 3, 3, 1, 5, 5, 5, 5, 6, 7, 6 , 3, 7, 7};
    int ans = 0;

    for(auto i : arr) {
        ans ^= i;
    }

    cout << "Number which appears odd number of times is " << ans << "\n";

}