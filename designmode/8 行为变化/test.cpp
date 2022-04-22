#include <iostream>
#include <functional>

class Receiver {
 public:
  void Print() { std::cout << 1; }
};


int main(){
    Receiver a;
    std::function<void(Receiver&)> ft(&Receiver::Print);
    ft(a);

}