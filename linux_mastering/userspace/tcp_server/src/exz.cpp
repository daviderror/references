#include <getopt.h>
#include <iostream>
#include <sstream>
#include <signal.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
//#define NOT_LOG
#include <sys/wait.h>

#include <list>

#include <map>


enum command
{
    RESET,
    OPU_ON,
    OPU_OFF,
    VIDEO_ON,
    VIDEO_OFF,
    ZOOM_IN,
    ZOOM_OUT,
    ZOOM_RESET,
    ZOOM,
    TERM_ON,
    TERM_OFF,
    TERM,
    OPU,
    WRIPER_ON,
    WRIPER_OFF,
    WRIPER,
    LEFT,
    RIGHT,
    UP,
    DOWN,
    TILT,
    GET_TILT,
    PAN,
    GET_PAN,
    ECHO,
    STATUS,
    PARKING,
    MODE,
    TEST,
    USER,
    EXIT
};

static std::map<std::string,command> str2command =
{
    {"reset"        ,RESET      },
    {"x"            ,RESET      },
    {"otk_on"       ,OPU_ON     },
    {"otk_off"      ,OPU_OFF    },
    {"opu_on"       ,OPU_ON     },
    {"opu_off"      ,OPU_OFF    },
    {"opu"          ,OPU        },
    {"video_on"     ,VIDEO_ON   },
    {"video_off"    ,VIDEO_OFF  },
    {"zoom_in"      ,ZOOM_IN    },
    {"zoom_out"     ,ZOOM_OUT   },
    {"zoom_reset"   ,ZOOM_RESET },
    {"term_on"      ,TERM_ON    },
    {"term_off"     ,TERM_OFF   },
    {"term"         ,TERM       },
    {"t"            ,TERM       },
    {"wriper_on"    ,WRIPER_ON  },
    {"wriper_off"   ,WRIPER_OFF },
    {"wriper"       ,WRIPER     },
    {"w"            ,WRIPER     },
    {"l"            ,LEFT       },
    {"left"         ,LEFT       },
    {"r"            ,RIGHT      },
    {"right"        ,RIGHT      },
    {"u"            ,UP         },
    {"up"           ,UP         },
    {"d"            ,DOWN       },
    {"down"         ,DOWN       },
    {"tilt"         ,TILT       },
    {"get_tilt"     ,GET_TILT   },
    {"gt"           ,GET_TILT   },
    {"pan"          ,PAN        },
    {"get_pan"      ,GET_PAN    },
    {"gp"           ,GET_PAN    },
    {"echo"         ,ECHO       },
    {"ping"         ,ECHO       },
    {"p"            ,ECHO       },
    {"status"       ,STATUS     },
    {"s"            ,STATUS     },
    {"home"         ,PARKING    },
    {"parking"      ,PARKING    },
    {"mode"         ,MODE       },
    {"test"         ,TEST       },
    {"user"         ,USER       },
    {"exit"         ,EXIT       }
};

#include "template_proj_lib.h"

#include "log.h"



using namespace std;
short int isValid=0;
short int cycl_ex=0;

static void catchSignal(int sig);
void BlockAllSignals(sigset_t& sigmask);
void SetChildSignals();
void SetDaemonSignals(void);
/*! Обработчик прерываний */

std::list<int> ch_pid;


int main(int argc, char **argv) {
    
    
    int listenSocket = 0;
    struct sockaddr_in  listenSocketParam;
    struct sockaddr_in  client;
    
    string ConfigFile, LogFile;
    uint16_t Port = 0;
    unsigned int time_out = 0;
    
    

    {
        option long_options[] =
          {
            {"port",     1,0,'p'},
            {"timeout",  1,0,'t'},
            {"help",     0,0,'h'},
            {"config",   1,0,'c'},
            {"logfile",  1,0,'l'},
            {0, 0, 0, 0}
          };

        while(true)
          {
            int ch = getopt_long (argc, argv, "hp:t:c:l:",long_options, NULL);
            if (ch == EOF)
              break;

            switch (ch)
              {
              case '?':
                //cerr<< "Опция '"<<(char)optopt<<"' некорректна\n"  ;
              case 'h':
                cerr << "usage: simple_telnetd [-pcht] [port] \n\t-c, --config\t: Configuration file\n\t-t, --time\t: Time out\n\t-p, --port\t: Internet/Unix Port\n\t-l, --logfile\t: Log File\n\t-h, --help\t: Print this\n";
                exit(0);
              case 'c':
                //ConfigFile=ResolveFile(3,optarg,ConfigFile.c_str(),PACKAGE ".conf");
                ConfigFile=optarg;//ConfigFile=ResolveFile(1,optarg);
                break;
              case 't':
                if(optarg&&*optarg)
                  {
                    istringstream(optarg) >> time_out;
                    if(!time_out)
                      time_out =5;             // Time out по умолчанию
                  }
                break;
              case 'l' :
                LogFile=optarg;
                break;
              case 'p':
                Port= atoi(optarg);
                break;
              default :
                break;
              }
          }


      }
      
      
      
      
      
      
      
     
     //***********************************************************
     // Обработка сигналов
     //*********************************************************** 
     // if handler is epsand a signal block is reqiered
      SetDaemonSignals();
/*     
    pid_t pid = fork();
    
    
    
    if (0 == pid) {
    

        sleep(3);
        cout << getpid()<< ": Goodbuy" << endl;
       
        exit(EXIT_SUCCESS);
    }
    
  
    setsid();
   */    
   // alarm(5);
    
   
     
    listenSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
      
    if ( listenSocket == -1 ) exit(printf("socket"));
     
    memset((char *) &listenSocketParam, 0, sizeof(listenSocketParam));
    
    listenSocketParam.sin_family        = AF_INET;
    listenSocketParam.sin_port          = htons(Port);
    listenSocketParam.sin_addr.s_addr   = INADDR_ANY; 
    
    if (bind(listenSocket, (struct sockaddr*)&listenSocketParam, sizeof(listenSocketParam))==-1) {
       printf("bind");
        exit(EXIT_FAILURE);
    }
    
    char buf[BUFSIZ];
    unsigned int sockaddr_in_size = sizeof( sockaddr_in);
    
    listen(listenSocket, 5);
     
    cout << "SERVER PID: " << getpid() << endl;
    
    while(true) {
         
        // LOG("WORLD" __ cycl_ex __ pid __ "HELLO");
       //  LOG1(cycl_ex);
         
        // if (cycl_ex == SIGTERM)  break;
         
        {
            
            fd_set set;
            struct timeval timeout;
            int rv;
            FD_ZERO(&set); /* clear the set */
            FD_SET(listenSocket, &set); /* add our file descriptor to the set */

             timeout.tv_sec = 2000; //for client
             timeout.tv_usec = 0;

            rv = select(listenSocket + 1, &set, NULL, NULL, &timeout);
            
            if (rv == -1)
            {
            perror("select"); /* an error occurred */
            continue;
            }
            else if (rv == 0)
            {
            printf("timeout occurred (20 second) \n"); /* a timeout occurred */
            continue;
            }
        }
         
         int sock_d = accept(listenSocket, NULL, NULL);
         
         LOG1(sock_d);
         
//          if (sock_d == -1) {
//              continue;
//          }
         
         
         pid_t pid_d = fork();
         
         if (pid_d < 0) {
            perror("fork abort");
            continue;
         }
         
         if (0 != pid_d) { //base
            close(sock_d);
            ch_pid.push_back(pid_d);
            continue;
         }
         else { //filial
            cout << "In a filial: " << getpid() << endl;
 
            
            
            SetChildSignals();

            
             
         //   recvfrom(sock_d, buf, 20, 0, 
       //             (struct sockaddr *)&client, &sockaddr_in_size);
             
        //    cout << buf << endl;
            
            while (strcmp(buf, "exit")) {
                memset(buf, 0, 1024);

               // time_t ticks = time(NULL);
               // snprintf(buf, sizeof(buf), "%.24s\r\n", ctime(&ticks));

                read(sock_d, buf, 1024);
                
               if (str2command.find(buf) != str2command.end()) {

                cout << buf __ str2command[buf] << endl;
                
                switch(str2command[buf]){
                    
                    case EXIT :
                        
                    break;
                
                
               }
    
            }
            
            
       //     close(listenSocket);
            shutdown(sock_d, SHUT_RDWR);
            close(sock_d);
            break;
         }
         
         
     }
     
     
     close(listenSocket);
    
    return 0;
}


/*! Обработчик прерываний */
static void catchSignal(int sig)
{
    
    errno = 0;
    printf( "Получен сигнал: %i\n", sig );
    
    isValid=sig;
    cycl_ex = sig;
    
    LOG1(getpid());
    
    switch (sig) {
        case SIGINT:
            
       
        case SIGPIPE :
            
            
         case SIGTERM :
             exit(EXIT_SUCCESS);
         break;
        case SIGCHLD :
        { 
            
            int status = 0;
            
             LOG1(*ch_pid.begin());
//             
//             if(ch_pid < 0){
//                 LOG("Error");
//             }
//             else if(ch_pid==0){
//                     // Child Process
//                  for(int i=0;i<100;i++){
//                          value-=1;
//                          LOG1("%d",value);      
//                      
//                 }
//                 
//                 break;
//             }
            
            list<int>::iterator j = ch_pid.begin();
            
            for (list<int>::iterator i = ch_pid.begin(); i != ch_pid.end(); ++i) {
                waitpid(*i, &status,0);
                
                if (WIFSIGNALED(status)){
                    LOG("Error");
                }
                else if (WEXITSTATUS(status)){
                   LOG("Exited Normally");
                   j = i;
                  
                }
            }
            
            if (!ch_pid.empty())
                ch_pid.erase(j);
            
            
            
             // WAIT till child gets over
            // Parent process
//             for(int i=0;i<100;i++){
//                         value-=1;
//                         LOG("%d",value);
//             }
//            printingFunction();
                
            
            
            
            
            
                   
        }
       
        break;
    }
    
    //if (sig == SIGINT || sig == 17) exit(EXIT_SUCCESS);
}



void SetDaemonSignals(void)
{
  static sigset_t sigmask;
  static struct sigaction action;

  BlockAllSignals(sigmask);

  if (
    sigdelset(&sigmask, SIGINT)  == -1 ||
    sigdelset(&sigmask, SIGTERM) == -1 ||    // Ручное прерывание
    sigdelset(&sigmask, SIGSEGV) == -1 ||    // Если что-то пойдет не так
    sigdelset(&sigmask, SIGALRM) == -1 ||    // Для выхода по таймауту
    sigdelset(&sigmask, SIGPIPE) == -1 ||    // Если хост разорвал связь
    sigdelset(&sigmask, SIGHUP)  == -1 ||    // Чтение конфигурации
    sigdelset(&sigmask, SIGCHLD) == -1 ||    // Завершение потомка
    sigprocmask(SIG_SETMASK, &sigmask, 0) == -1
  )
    exit(errno) ;

  sigfillset(&action.sa_mask);              // Блокируем все сигналы в обработчике
  action.sa_handler = catchSignal ;


  if (
    sigaction(SIGINT,   &action, NULL) == -1 ||
    sigaction(SIGTERM,  &action, NULL) == -1 ||
    sigaction(SIGALRM,  &action, NULL) == -1 ||
    sigaction(SIGPIPE,  &action, NULL) == -1 ||
    sigaction(SIGSEGV,  &action, NULL) == -1 ||
    sigaction(SIGCHLD,  &action, NULL) == -1 ||
    sigaction(SIGHUP,   &action, NULL) == -1
  )
    exit(errno) ;
}


void SetChildSignals()
{
  static sigset_t sigmask;
  static struct sigaction action;

  BlockAllSignals(sigmask);


  if (
    sigdelset(&sigmask, SIGTERM) == -1 ||    // Ручное прерывание
    sigdelset(&sigmask, SIGSEGV) == -1 ||    // Если что-то пойдет не так
    sigdelset(&sigmask, SIGALRM) == -1 ||    // Для выхода по таймауту
    sigdelset(&sigmask, SIGPIPE) == -1 ||    // Если хост разорвал связь
    sigdelset(&sigmask, SIGHUP) == -1  ||    // Чтение конфигурации
    sigprocmask(SIG_SETMASK, &sigmask, 0) == -1
  )
    exit(errno) ;

  sigfillset(&action.sa_mask);              // Блокируем все сигналы в обработчике
  action.sa_handler = catchSignal ;

  if (
    sigaction(SIGTERM, &action, NULL) == -1 ||    // Ручное прерывание
    sigaction(SIGALRM, &action, NULL) == -1 ||
    sigaction(SIGPIPE, &action, NULL) == -1 ||
    sigaction(SIGSEGV, &action, NULL) == -1 ||
    sigaction(SIGHUP,  &action, NULL) == -1
  )
    exit(errno) ;
}


void BlockAllSignals(sigset_t& sigmask)
{
  static struct sigaction action;
  sigfillset (&sigmask) ;
  sigprocmask(SIG_SETMASK, &sigmask, 0);
}
