#include<iostream>
#include<vector>
using namespace std;



class Solution {
public:
	vector<int> twoSum(vector<int>& nums, int target)
	{
		vector<int> buf;
		for (int i = 0; i < nums.size() - 1; i++)
		{
			for (int j = i + 1; j < nums.size(); j++)
			{
				if (nums[i] + nums[j] == target)
				{
					buf.push_back(i);
					buf.push_back(j);
					break;
				}
			}
		}
		return buf;
	}
};



int main()
{
	vector<int> nums = { 2, 7, 11, 15 };
	int target = 9;

	vector<int> r = Solution().twoSum(nums, target);
	for (int i = 0; i < r.size(); i++)
		cout << r[i] << " ";
	cout << endl;
}
