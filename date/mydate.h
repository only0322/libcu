#ifndef _MYDATE_H_
#define _MYDATE_H_
#include"../common/common.h"
namespace LibcuDate
{
    class MyDate
    {
        public:
            void getNowDateStr(char * today)  //返回YYYYMMDD的日期字符串
            {
                time_t lt;
                struct tm * local;
                lt = time(0);
                local = localtime(&lt);
                strftime(today,9,"%Y%m%d",local);
            }

            void getNowDateTimeStr(char * today)  //返回YYYYMMDDHHmmss的日期字符串
            {
                time_t lt;
                struct tm * local;
                lt = time(0);
                local = localtime(&lt);
                strftime(today,14,"%Y%m%d%H%M%S",local);
            }
            
            void Get_TimeStamp(char * stamp)   //生成系统时间戳，返回15位日期
            {	
            time_t current;
            struct tm *tmCurrentTime;

            tzset();
            time(&current);
            tmCurrentTime = localtime(&current);
            sprintf(stamp, "%4d%02d%02d%02d%02d%02d",
                    tmCurrentTime->tm_year + 1900, tmCurrentTime->tm_mon + 1,
                    tmCurrentTime->tm_mday, tmCurrentTime->tm_hour,
                    tmCurrentTime->tm_min, tmCurrentTime->tm_sec);
            }


    };


}
#endif
