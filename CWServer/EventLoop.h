//
// @Author cory
// @Email cjcory@qq.com
//
#pragma once
#include <iostream>
#include <functional>
#include <memory>
#include <vector>
#include "Channel.h"
#include "Epoll.h"
#include "Util.h"
#include "Log/CurrentThread.h"
#include "Log/Logging.h"
#include "Log/Thread.h"

class EventLoop{
public:
    typedef std::function<void()> Functor;
    EventLoop();
    ~EventLoop();
    void loop();
    void quit();
    void runInLoop(Functor&& cb);
    void queueInLoop(Functor&& cb);
    bool isInLoopThread() const { return threadId_ == CurrentThread::tid();}
    void assertInLoopThread() { assert(isInLoopThread()); }
    void shutdown(shared_ptr<Channel> channel) { shutDownWR(channel->getFd()); }
    void removeFromPoller(shared_ptr<Channel> channel){
        poller_->epoll_del(channer);
    }
    void updatePoller(share_ptr<Channel> channel,int timeout = 0){
        poller_->epoll_mod(channel, timeout);
    }
    void addToPoller(shared_ptr<Channel> channel, int timeout = 0) {
        poller_->epoll_add(channel, timeout);
    }

private:
    bool looping_;
    shared_ptr<Epoll> poller_;
    int wakeupFd_;
    bool quit_;
    bool eventHandling_;
    mutable MutexLock mutex_;
    std::vector<Functor> pendingFunctors_;
    bool callingPendingFunctors_;
    const pid_t threadId_;
    shared_ptr<Channel> pwakeupChannel_;

    void wakeup();
    void handleRead();
    void doPendingFunctors();
    void handleConn();
};