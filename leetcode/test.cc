#include "0739. 每日温度/solution.cc"
#include <iostream>

int main() {

    vector<int> test = {73,74,75,71,69,72,76,73};
    auto out = Solution().dailyTemperatures(test);
    cout << "[" << out[0];
    for (auto first = out.cbegin()+1; out.cend() > first; ++first) cout << "," << *first;
    cout << "]" << endl;
    



    return 0;
}