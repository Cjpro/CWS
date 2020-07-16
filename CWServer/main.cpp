//
// @Author cory
// @Email cjcory@qq.com
//

#include <string>
#include <getopt.h>
#include "EventLoop.h"
#include "Server.h"
#include "Log/Logging.h"

int main(int argc, char *argv[])
{
    int threadNum = 4;
    int port = 80;
    std::string logPath = "./CWS.log";

    //解析args
    const char* str = "n:l:p"; //huh,nlp!
    int opt;

    while((opt = getopt(argc,argv,str)) != -1)
    {
        switch (opt) {
            case 'n': {
                threadNum = atoi(optarg);
                break;
            }
            case 'l': {
                logPath = optarg;
                if(logPath.size() < 2 || optarg[0] != '/')
                {
                    printf("LogPath should begin with \"/\"\n");
                    abort();
                }
                break;
            }
            case 'p' : {
                port = atoi(optarg);
                break;
            }
            default:
                break;
        }
    }

    Logger::setLogFileName(logPath);

#ifdef _PTHREADS
    LOG << "_PTHREADS is not defined";
#endif
    Eventloop mainLoop;
    Server myHTTPServer(&mainLoop,threadNum,port);
    myHTTPServer.start();
    mainLoop.loop();
    return 0;
}