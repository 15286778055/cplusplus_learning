#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    vector<int> findDisappearedNumbers(vector<int>& nums) {
        vector<int> output;
        
        for (const int &num : nums) {
            int pos = abs(num) - 1;
            if (0 < nums[pos]) nums[pos] = -nums[pos];
        }

        for (int i = 0; i < nums.size() ; ++i) {
            if (0 < nums[i]) output.push_back(i+1);
        }
        return output;
    }
};