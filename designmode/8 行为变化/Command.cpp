/**
 * @file Command.cpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-04-22
 * 
 * @copyright Copyright (c) 2022
 * 
 * 命令模式：实现方式和 组合模式很像
 * 比起组合模式，Command中添加了一个 receiver
 * 
 */
   
#include <functional>
#include <iostream>
#include <list>
#include <memory>
#include <utility>

class Receiver {
 public:
  void Print() { std::cout << 1; }
};

class Command {
 public:
  virtual void Execute() = 0;
  virtual ~Command() = default;
};

template <typename T>
class CommandA : public Command {
 public:
  using Action = std::function<void(T&)>;       /* std::function 函数包装器，使用和函数指针类似 */

  CommandA(const std::shared_ptr<T>& p, Action a)
      : receiver_(p), action_(std::move(a)) {}

  void Execute() override {
    std::cout << "A";
    if (const auto p = receiver_.lock()) {
      action_(*p);      
    }
  }

 private:
  std::weak_ptr<T> receiver_;
  Action action_;
};

template <typename T>
class CommandB : public Command {
 public:
 // 这里有T&,是因为绑定的是 Receiver::Print，这个函数的缺省参数就是 Receiver* 类型，所以 这里需要是void(T&) 或者void(T*)，两者皆可，编译器有转换
  using Action = std::function<void(T&)>;       /* std::function 函数包装器，使用和函数指针类似 */

  CommandB(const std::shared_ptr<T>& p, Action a)
      : receiver_(p), action_(std::move(a)) {}

  void Execute() override {
    std::cout << "B";
    if (const auto p = receiver_.lock()) {
      action_(*p);
    }
  }

 private:
  std::weak_ptr<T> receiver_;
  Action action_;
};

class Invoker : public Command {
 public:
  void Append(const std::shared_ptr<Command>& c) { commands_.emplace_back(c); }

  void Remove(const std::shared_ptr<Command>& c) {
    commands_.remove_if(
        [&](std::weak_ptr<Command>& x) { return x.lock() == c; });
  }

  void Execute() override {
    for (auto&& x : commands_) {
      if (const auto p = x.lock()) {
        p->Execute();
      }
    }
  }

 private:
  std::list<std::weak_ptr<Command>> commands_;
};

int main() {
  auto receiver = std::make_shared<Receiver>();
  const std::shared_ptr<Command> commandA = std::make_shared<CommandA<Receiver>>(receiver, &Receiver::Print);
  const std::shared_ptr<Command> commandB = std::make_shared<CommandB<Receiver>>(receiver, &Receiver::Print);

  Invoker invoker;
  invoker.Append(commandA);
  invoker.Append(commandB);
  invoker.Execute();  // A1B1
}