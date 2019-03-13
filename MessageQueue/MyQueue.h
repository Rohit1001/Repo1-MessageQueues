#ifndef MYQUEUE_
#define MYQUEUE_

#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>

using namespace std;

template <typename T>
class MyQueue
{
 public:

  T pop() 
  {
    unique_lock<mutex> mlock(mtx);
    while (q.empty())
    {
      condvar.wait(mlock);
    }
    auto val = q.front();
    q.pop();
    return val;
  }

  void pop(T& item)
  {
    unique_lock<mutex> mlock(mtx);
    while (q.empty())
    {
      condvar.wait(mlock);
    }
    item = q.front();
    q.pop();
  }

  void push(const T& item)
  {
    unique_lock<mutex> mlock(mtx);
    q.push(item);
    mlock.unlock();
    condvar.notify_one();
  }
    
 private:
  queue<T> q;
  mutex mtx;
  condition_variable condvar;
};

#endif
