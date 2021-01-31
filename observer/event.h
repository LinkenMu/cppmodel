#include <iostream>
#include <string>
#include <functional>
#include <map>
using namespace std;

class NonCopyable
{
protected:
  NonCopyable() = default;
  ~NonCopyable() = default;
  NonCopyable(const NonCopyable&) = delete; // 禁用复制构造

  // 禁用赋值构造
  NonCopyable& operator = (const NonCopyable&) = delete;
};


template<typename Func>
class Events : NonCopyable
{
public:
   Events(){};

    ~Events(){}
   // 注册观察者，支持右值引用

   int Connect(Func&& f)
   {
       printf("right value \n");
      return Assgin(f);
   }
  // 注册观察者


   int Connect(const Func& f)
   {
       printf("left value\n");
      return Assgin(f);
   }
  // 移除观察者


   void Disconnect(int key)
   {
      m_connections.erase(key);
   }
   // 通知所有的观察者

   template<typename... Args>
   void Notify(Args&&... args)
   {
      for (auto& it: m_connections)
      {
         it.second(std::forward<Args>(args)...);
      }
   }
private:
   // 保存观察者并分配观察者的编号
    template<typename F>
   int Assgin(F&& f)
   {
      int k=m_observerId++;
      m_connections.emplace(k, std::forward<F>(f));
      return k;
   }
   int m_observerId=0;                          // 观察者对应的编号

   std::map<int, Func> m_connections;             // 观察者列表


};
