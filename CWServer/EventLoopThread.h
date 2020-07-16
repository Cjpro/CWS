//
// @Author cory
// @Email cjcory@qq.com
//

#pragma once
#include "EventLoop.h"
#include "Log/Condition.h"
#include "Log/MutexLock.h"
#include "Log/Thread.h"
#include "Log/noncopyable.h"


class EventLoopThread : noncopyable {
 public:
  EventLoopThread();
  ~EventLoopThread();
  EventLoop* startLoop();

 private:
  void threadFunc();
  EventLoop* loop_;
  bool exiting_;
  Thread thread_;
  MutexLock mutex_;
  Condition cond_;
};
