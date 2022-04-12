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
 * 时间复杂度：1) O(N*M)     2）O(M/2 + M*N/2)
 * 空间复杂度：1) O(1)     2) O(2)
 * 特征：
 * 注意：vector最重要的是：
 * 1）避免暴力解
 * 2）迭代的推导(举一般的例子)
 * 3）终止条件，容器为空的情况
 * 
 */


#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    // 常规方法：由外至内，依次旋转
    void rotate(vector<vector<int>>& matrix) {
        int temp = 0, n = matrix.size();
        for (int i = 0; i < n/2; ++i) {
            for (int j = i; j < n-i-1; ++j) {
                temp = matrix[i][j];
                matrix[i][j] = matrix[n-j-1][i];
                matrix[n-j-1][i] = matrix[n-i-1][n-j-1];
                matrix[n-i-1][n-j-1] = matrix[j][n-i-1];
                matrix[j][n-i-1] = temp;
            }
        }
    }

    // 法2: 上下翻转 + 对角翻转
    void rotate2(vector<vector<int>>& matrix) {
        reverse(matrix.begin(), matrix.end());
        int n = matrix.size();
        for (int i = 0; i < n-1; ++i) {
            for (int j = i+1; j < n; ++j) {
                swap(matrix[i][j], matrix[j][i]);
            }
        }
    }
};