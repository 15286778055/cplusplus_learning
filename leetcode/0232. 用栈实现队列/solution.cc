/**
 * @file solution.cc
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-04-06
 * 
 * @copyright Copyright (c) 2022
 * 
 * 特征：注意 stack 这个容器适配器的操作就行，容器的很多操作，这个适配器都没有
 * 
 */

#include <iostream>
#include <stack>

using namespace std;

class MyQueue {
public:
    MyQueue() {
    
    }
    
    void push(int x) {
        stack1.push(x);
    }
    
    int pop() {
        stack1tostack2();
        int o = stack2.top();
        stack2.pop();
        return o;
    }
    
    int peek() {
        stack1tostack2();
        return stack2.top();
    }

    void stack1tostack2() {
        if (stack2.empty()) {
            while(!stack1.empty()) {
                stack2.push(stack1.top());
                stack1.pop();
            }
        }
    }
    
    bool empty() {
        return stack1.empty() && stack2.empty();
    }

private:
    stack<int> stack1;
    stack<int> stack2;
};

/**
 * Your MyQueue object will be instantiated and called as such:
 * MyQueue* obj = new MyQueue();
 * obj->push(x);
 * int param_2 = obj->pop();
 * int param_3 = obj->peek();
 * bool param_4 = obj->empty();
 */