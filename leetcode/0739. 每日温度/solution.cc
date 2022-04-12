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
 * 时间复杂度：O(M*N)
 * 空间复杂度：O(1)不包括返回值
 * 特征：正序需要全遍历，逆序避免最坏情况O(M*N)，时间开销和最小栈一个数量级
 * 注意：
 * 
 */

#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:

    // solution1 逆序
    vector<int> dailyTemperatures(vector<int>& temperatures) {
        int n = temperatures.size();
        vector<int> out(n, -1);
        out[n-1] = 0;
        for (int i = n-2; i >= 0; --i) {
            for (int j = 1; ; j += out[i+j]) {
                if (temperatures[i] < temperatures[i+j]) {
                    out[i] = j;
                    break;
                } else if (0 == out[i+j]) {
                    // 以后 == 写法，变量在右，避免写成 =
                    out[i] = 0;
                    break;
                }
                if (i + j >= n - 1) {
                    out[i] = 0;
                    break;
                }
            } 
        }
        return out;
    }


    // solution2 单调栈
    vector<int> solution2(vector<int>& temperatures) {

        return vector<int>();
    }
};