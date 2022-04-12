/**
 * @file solution.cc
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-04-06
 * 
 * @copyright Copyright (c) 2022
 * 
 * 数据结构：优先队列
 * 时间复杂度：O(n*logn + n*m*logn)
 * 空间复杂度：O(N)
 * 特征：最值，利用指针，出栈之后，继续压栈
 * 注意：
 * 
 */


#include <vector>
#include <queue>

using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
 };
class Solution {
public:

    struct compare {
        bool operator() (ListNode* i, ListNode* j) {
            return i->val > j->val;

        }
    };


    ListNode* mergeKLists(vector<ListNode*>& lists) {

        if (lists.empty()) return nullptr;
        priority_queue<ListNode*, vector<ListNode*>, compare> q;
        for (auto it : lists) {
            if (it) {
                q.push(it);
            }
        }
            
        ListNode *out = new ListNode();
        ListNode *cur = out;
        while(!q.empty()) {
            cur->next = q.top();
            q.pop();
            cur = cur->next;
            if (cur->next) {
                q.push(cur->next);
            }
        }
        return out->next;
    }
};