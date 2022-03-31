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