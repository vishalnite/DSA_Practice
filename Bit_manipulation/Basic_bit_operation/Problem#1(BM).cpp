/* Given an array with every element appearing twice except two elements which appear only once.
   We need to find those two numbers
   
   Brute force - We can run two loops to find the numbers which appears only once. T.C. - O(N^2)  S.C. - O(1)
   Better solution - We can use a map to store  the frequency of each element. T.C. - O(NlogN)  S.C. - O(N)
   Optimal solution - Use Bit manipulation
                      First, find the XOR of all elements. Twice appearing elements will be cancelled and we get XOR of those two elements only
                      Then find the position of the bit at which the two numbers differ i.e, find the lowest set bit of the result.
                      Run a loop 
                        Split the array into numbers which has that bit set and those which has that bit unset
                        Find the XOR of the splitted array and thus we get our desired result.
*/

#include <iostream>
using namespace std;

int main() {

    int arr[] = {7, 8, 1, 4, 5, 10, 1, 4, 7, 10, 5, 8, 6, 9}; // Output - 6, 9
    int x = 0;

    for(auto i : arr) {
        x ^= i;
    }
    
    int pos = (x & (-x)) - 1;

    int num1 = 0, num2 = 0;

    for(auto i : arr) {
        if(i & (1 << pos))
            num1 ^= i;
        else
            num2 ^= i;
    }

    cout << "The required numbers are: " << num1 << ", " << num2 << endl;

    return 0;

}