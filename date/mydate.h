#ifndef _MYDATE_H_
#define _MYDATE_H_
#include"../common/common.h"
namespace LibcuDate{
    class MyDate
    {
        public:
            void getNowDateStr(char * today)  //返回YYYYMMDD的日期字符串
            {

                #ifdef _WIN32
                
                #else
                
                time_t lt;
                struct tm * local;
                lt = time(NULL);
                local = localtime(&lt);
                strftime(today,0,"%Y%m%d",local);
                
                #endif

            }
    };
}
#endif
