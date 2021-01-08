#include<iostream>
#include<vector>
#include  <tgmath.h>
#include <string>
using namespace std;


 struct ListNode {
     int val;
      ListNode *next;
      ListNode() : val(0), next(nullptr) {}
      ListNode(int x) : val(x), next(nullptr) {}
      ListNode(int x, ListNode *next) : val(x), next(next) {}
  };
 



class Solution {
public:
	ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {

		ListNode* r = new  ListNode();
		ListNode* ite = r;
		

		while (l1 != nullptr || l2 != nullptr)
		{
			if (l1 == nullptr)
			{
				
				ite->val = l2->val;
				if (l2->next != nullptr)
				{
					auto r_next = new ListNode();
					ite->next = r_next;
					ite = ite->next;
					
				}
				l2 = l2->next;

			}
			else if(l2 == nullptr)
			
			{

				ite->val = l1->val;
				if (l1->next != nullptr)
				{
					auto r_next = new ListNode();
					ite->next = r_next;
					ite = ite->next;
					
				}
				l1 = l1->next;

			}

			else if (l1 != nullptr && l2 != nullptr)
			{
				ite->val = l1->val + l2->val;
				
				if (l1->next != nullptr || l2->next != nullptr)
				{
					auto r_next = new ListNode();
					ite->next = r_next;
					ite = ite->next;
				}
				l1 = l1->next;
				l2 = l2->next;
			}


		}

		int carry = 0;
		ite = r;
		while (ite != nullptr)
		{
			if (ite->val >= 10)
			{
				ite->val = ite->val - 10;
				if (ite->next == nullptr)
				{
					auto r_next = new ListNode(1);
					ite->next = r_next;
				}
				else
				{
					(ite->next)->val = (ite->next)->val + 1;
				}

			}

			ite = ite->next;

		}


		
		return r;

	}
};



int main()
{
	vector<int> nums1 = {2,4,9 };
	vector<int> nums2 = {5,6,4,9 };

	

	ListNode l1 = ListNode();

	ListNode* it = &l1;

	for (int i = 0; i < nums1.size(); i++)
	{
		it->val = nums1[i];
		if (i == nums1.size()-1) { break; }
		auto next_node = new ListNode (23);

		it->next = next_node;
		it = it->next;
		
	}

	it = &l1;

	while (it->next != nullptr) { cout << it->val; it = it->next;}
	cout << endl;


	ListNode l2 = ListNode();

	it = &l2;

	for (int i = 0; i < nums2.size(); i++)
	{
		it->val = nums2[i];
		if (i == nums2.size()-1) { break; }
		auto next_node = new ListNode(23);

		it->next = next_node;
		it = it->next;

	}

	it = &l2;

	while (it->next != nullptr) { cout << it->val; it = it->next; }
	cout << endl;





	ListNode* r = Solution().addTwoNumbers(&l1, &l2);
	
	
}
