/**
 * @file solution.cc
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-04-06
 * 
 * @copyright Copyright (c) 2022
 * 
 * 数据结构：
 * 时间复杂度：
 * 空间复杂度：
 * 特征： 能 分割 的条件和 前序累加 的条件 ，这个很巧妙
 * 注意：
 * 
 */

#include <vector>

using namespace std;

class Solution {
public:
    int maxChunksToSorted(vector<int>& arr) {
        int count1 = 0, count2 = 0, block = 1;
        for (int i = 0; i < arr.size()-1; ++i) {
            if (count1 + arr[i] == count2 + i) {
                ++block;
            }
            count1 += arr[i];
            count2 += i;
        }
        return block;
    }
};