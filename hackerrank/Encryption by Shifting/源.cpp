#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <string>
#include <map>
#include <queue>
#include <unordered_set>
#include <stdio.h>
typedef long long ll;
using namespace std;


//You are given an array of N numbers, each a number between 1 and 10.
//
//You need to answer Q queries, each specified by a, b, c, and asking how many times the number c appears between position aand position b, inclusive.
//
//Since the largest test case is very large, you will need to use efficient inputand output mechanism in your chosen language.
//
//Input Format
//
//The first line of input contains Nand Q.
//
//Each of lines 2 to N + 1 contains an integer x that is between 1 and 10, where line i gives the(i - 1) - th number.
//
//Each of the next Q lines contains three numbers a, b, c.
//
//Constraints
//
//1 ¡Ü N ¡Ü 500, 000
//
//1 ¡Ü Q ¡Ü 500, 000
//
//1 ¡Ü a ¡Ü b ¡Ü N
//
//1 ¡Ü c ¡Ü 10
//
//Output Format
//
//Output Q lines, each containing the answer to the Q - th query.
//
//Sample Input 0
//
//8 4
//1
//2
//3
//2
//1
//4
//2
//4
//1 8 5
//2 4 2
//3 8 1
//6 6 4
//Sample Output 0
//
//0
//2
//1
//1
//Sample Input 1
//
//20 10
//4
//4
//3
//10
//1
//9
//3
//7
//7
//10
//2
//2
//4
//6
//9
//4
//1
//7
//10
//3
//8 18 3
//1 9 4
//10 13 5
//10 12 8
//5 11 6
//1 5 1
//3 5 4
//2 11 7
//12 17 10
//16 18 2
//Sample Output 1
//
//0
//2
//0
//0
//0
//1
//0
//2
//0
//0
//Sample Input 2
//
//20 11
//2
//5
//2
//6
//3
//4
//4
//4
//4
//7
//8
//9
//9
//9
//6
//1
//7
//5
//2
//10
//11 13 8
//5 12 8
//14 19 4
//13 19 7
//1 4 10
//6 18 6
//18 20 7
//8 11 6
//7 20 9
//3 17 5
//1 20 10
//Sample Output 2
//
//1
//1
//0
//1
//0
//1
//0
//0
//3
//0
//1
//
//











int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */

    iostream::sync_with_stdio(false);
    std::cin.tie(0);

    int n, q;
    cin >> n;
    cin >> q;

    //use 10 vectors to record the element count of each digit upto a certain index, i.e. for a vector (i.e. named vector_1) that works for digit 1, the i th element of vector_1 should be 
    //the number of occurance of digit 1 between index 0 and i (inclusive interval)in the data vector. Then the number of occurance between [n,i] (inclusive interval) in data is simply vector_1[i]-vector[n-1]
    vector<vector <int>> digit_occurance;
    for (int i = 0; i < 10; i++)
    {
        vector<int>occ;
        occ.resize(n);
        digit_occurance.push_back(occ);
    }
    int num;
    cin >> num;
    digit_occurance[num-1][0] = 1;//num is 1 to 10

    for (int i = 1; i < n; i++)
    {
        cin >> num;
        num -= 1;
        for (int j = 0; j < 10; j++) {
            digit_occurance[j][i] = digit_occurance[j][i - 1];
        }
        digit_occurance[num][i] = digit_occurance[num][i - 1] + 1;

    }



    for (int i = 0; i < q; i++)
    {
        int l, r, c;
        cin >> l;
        cin >> r;
        cin >> c;
        c -= 1;
        

        if (l == 1) cout << digit_occurance[c][r - 1] << '\n';
        else cout << digit_occurance[c][r - 1] - digit_occurance[c][l - 2] << '\n';
        
    }
   
    
    return 0;
}