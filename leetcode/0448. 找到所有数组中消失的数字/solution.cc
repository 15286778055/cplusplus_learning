/**
 * @file solution.cc
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-04-06
 * 
 * @copyright Copyright (c) 2022
 * 
 * 数据结构：vector
 * 时间复杂度：O(2*N)
 * 空间复杂度：O(0)
 * 特征：
 * 注意：vector最重要的是：
 * 1）避免暴力解
 * 2）迭代的推导(举一般的例子)
 * 3）终止条件，容器为空的情况
 */

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