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
            
            long getNowDateLong()
            {
                char	now[9];
                memset(now,0,sizeof(now));
                this->getNowDateStr(now);

                return atol(now);
            }

            long getNowDateTimeLong()
            {
                char	now[15];
                memset(now,0,sizeof(now));
                this->getNowDateTimeStr(now);

                return atol(now);
            }

            int getKimLarsen(char * date)  //传入8位日期，返回当前是星期几，1为周一，7为周日，0为日期不合法
            {
                if(strlen(date)!=8)
                {
                    return -1;
                }
                char cYear[4+1];
                char cMonth[2+1];
                char cDay[2+1];
                memset(cYear,0x00,sizeof(cYear));
                memset(cMonth,0x00,sizeof(cMonth));
                memset(cDay,0x00,sizeof(cDay));
                memcpy(cYear,date,4);
                memcpy(cMonth,date+4,2);
                memcpy(cDay,date+6,2);
                int year = atoi(cYear);
                int month = atoi(cMonth);
                int day = atoi(cDay);
                if(month == 1)
                {
                    month = 13;
                    year--;
                }
                else if(month ==2)
                {
                    month = 14;
                    year--;
                }
                //(iday+2*imonth+3*(imonth+1)/5+iyear+iyear/4-iyear/100+iyear/400)%7
                int week= (year + year /4 + year / 400 - year / 100 + 2 * month + 3 * (month + 1)/5 + day) % 7;
                week++;
                return week;
            }

    };


}
#endif
