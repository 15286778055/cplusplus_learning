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