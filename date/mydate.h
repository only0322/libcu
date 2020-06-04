#ifndef __MYDATE_H_
#define __MYDATE_H_

namespace Date{
    class MyDate
    {
        public:
            char * getNowDateStr()  //返回YYYYMMDD的日期字符串
            {
                char * today;
                #ifdef _WIN32
                
                #else
                
                time_t lt;
                struct tm * local;
                lt = time(NULL);
                local = localtime(&lt);
                strftime(today,0,"%Y%m%d",local);
                
                #endif
                return today;
            }
    };
}
#endif
