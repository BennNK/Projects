#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <string>
#include <map>
#include <queue>
#include <unordered_set>
typedef long long ll;
using namespace std;




int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    int n_case=1;
    //5 6 5 2 7 6 11 7 0
    for (; n_case >0; n_case++)
    {

        //for (int i = 0; i < 50000; i++) cout << 1 << ' ';
        //cout << 0;

        ll income = 0;
        unordered_set <int> bet;
        int c = 0;
        
        while (1)
        {
            int n;
            if (cin >> n) c++;

            if (n == 0) break;
            if (n == 11) {
                income++; continue;
            }
            if (n == 2 || n == 3 || n == 12) {
                income--; continue;
            }
            if (n == 7)
            {
                income++;
                if (!bet.empty())
                {
                    income -= bet.size();
                    bet.clear();
                }
                continue;
            }
            if (bet.count(n))
            {
                income++;

            }
            else bet.insert(n);


        }
        if (c == 0) break;
        if (income == 0) cout << "Sequence " << n_case << ": Break even." << endl;
        if (income > 0) cout << "Sequence " << n_case << ": Win of $"<<income<<"." << endl;
        if (income < 0) cout << "Sequence " << n_case << ": Loss of $" << income << "." << endl;
        cin.clear();
        fflush(stdin);
    }
    
    
    return 0;
}