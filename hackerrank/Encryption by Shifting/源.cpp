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



int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */

    iostream::sync_with_stdio(false);
    std::cin.tie(0);

    int n,q;
    cin >> n;
    cin >> q;
    vector<int> data;
    data.resize(n);
    for (int i = 0; i < n; i++)
    {
        cin >> data[i];
    }

    for (int i = 0; i < q; i++)
    {
        int l, r, c;
        cin >> l;
        cin >> r;
        cin >> c;
        int cnt = 0;
        for (int j = l - 1; j < r; j++)
        {
            if (data[j] == c) cnt++;
        }
        cout << cnt <<'\n';

    }
    /*vector<vector<int>> qry;
    for (int i = 0; i < q; i++)
    {
        vector <int> one_qry(3);
        cin >> one_qry[0];
        cin >> one_qry[1];
        cin >> one_qry[2];
        qry.push_back(one_qry);
    }

    for (int i = 0; i < q; i++)
    {
        int cnt = count(data.begin() + qry[i][0] - 1, data.begin() + qry[i][1], qry[i][2]);
        cout << cnt <<'\n';
    }*/
    
    
    return 0;
}