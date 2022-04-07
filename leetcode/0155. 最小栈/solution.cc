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
 * 时间复杂度：
 * 空间复杂度：
 * 特征：空间换时间，用最小栈保存当前最小值队列
 * 注意：
 * 
 */

#include <stack>
#include <iterator>
using namespace std;
class MinStack {
public:
    MinStack() {
    
    }
    
    void push(int val) {
        mystack.push(val);
        if (minstack.empty() || val <= minstack.top()) minstack.push(val);
    }
    
    void pop() {
        int num = mystack.top();
        mystack.pop();
        if (!minstack.empty() && num == minstack.top()) {
            minstack.pop();
        }
    }
    
    int top() {
        return mystack.top();
    }
    
    int getMin() {
        return minstack.top();
    }

private:
    stack<int> mystack;
    stack<int> minstack;
};

/**
 * Your MinStack object will be instantiated and called as such:
 * MinStack* obj = new MinStack();
 * obj->push(val);
 * obj->pop();
 * int param_3 = obj->top();
 * int param_4 = obj->getMin();
 */