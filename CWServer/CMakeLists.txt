set(SRCS
        Channel.cpp
        Epoll.cpp
        EventLoop.cpp
        EventLoopThread.cpp
        EventLoopThreadPool.cpp
        HttpData.cpp
        Main.cpp
        Server.cpp
        ThreadPool.cpp
        Timer.cpp
        Util.cpp
        Server.cpp)
include_directories(${PROJECT_SOURCE_DIR}/Log)


add_executable(WebServer ${SRCS})
target_link_libraries(WebServer libserver_base)


add_subdirectory(Log)
