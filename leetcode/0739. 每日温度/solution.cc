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