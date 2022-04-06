/**
 * @file solution.cc
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-04-06
 * 
 * @copyright Copyright (c) 2022
 * 
 * 数据结构：栈
 * 时间复杂度：O(N)，多次提前return，避免O(N)
 * 空间复杂度：最理想O(1)，不理想O(N-1)，但实际上，stack是有deque实现的，空间开销应该是比这个要大。
 * 特征：左右对称
 * 注意：提前结束的特殊条件
 * 
 */

#include <string>
#include <stack>

using namespace std;

class Solution {
public:
    bool isValid(string s) {
        stack<char> checkstack;
        char t = ' ';
        for (const char& c : s) {
            if ('(' == c || '[' == c || '{' == c) checkstack.push(c);
            else {
                if (checkstack.empty()) return false;
                else {
                    t = checkstack.top();
                    if (('[' == t && ']' == c) || ('{' == t && '}' == c) || ('(' == t && ')' == c)) checkstack.pop();
                    else return false;
                }
            }  
        }
        return checkstack.empty();
    }
};