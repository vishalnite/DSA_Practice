// Progrm to show basic bitwise operations like (&, |, ~, ^, <<, >>)
#include<iostream>
using namespace std;

int main() {

    cout << "Bitwise AND(&): 5 & 2 = " << (5 & 2) << endl; // 0

    cout << "Bitwise OR(|): 5 | 2 = " << (5 | 2) << endl; // 7

    cout << "Bitwise NOT(~): ~5 = " << (~5) << endl; // -6

    cout << "Bitwise XOR(^): 5 ^ 3 = " << (5 ^ 3) << endl; // 6

    cout << "Left Shift(<<): 5 << 1 = " << (5 << 1) << endl; // 10

    cout << "Right Shift(>>): 5 >> 1 = " << (5 >> 1) << endl; // 2

}