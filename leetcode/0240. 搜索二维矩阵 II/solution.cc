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
 * 时间复杂度：O(N+M)
 * 空间复杂度：O(4)
 * 特征： 规律性太强了
 * 注意： ！！！一定要注意临界条件(对角)
 * 
 */

#include <vector>

using namespace std;

class Solution {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        int i = 0, j = 0, m = matrix.size()-1, n = matrix[0].size()-1;
        if (m <= -1 || n <= -1) return false;
        while (i <= m && j <= n) {
            if (matrix[i][j] == target || matrix[m][n] == target || matrix[i][n] == target || matrix[m][j] == target) return true;
            if (matrix[i][j] > target || matrix[m][n] < target) return false;

            if (target < matrix[i][n] && target <  matrix[m][j]) {
                --n;
                --m;
            } else if (target < matrix[i][n] && target >  matrix[m][j]) {
                --n;
                ++j;
            } else if (target > matrix[i][n] && target <  matrix[m][j]) {
                ++i;
                --m;
            } else if (target > matrix[i][n] && target >  matrix[m][j]) {
                ++i;
                ++j;
            }
        }
        return false;
    }
};