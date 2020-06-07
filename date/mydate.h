#ifndef _MYDATE_H_
#define _MYDATE_H_
#include"../common/common.h"
namespace LibcuDate
{
    void getNowDateStr(char * today)  //返回YYYYMMDD的日期字符串
    {
        time_t lt;
        struct tm * local;
        lt = time(0);
        local = localtime(&lt);
        strftime(today,9,"%Y%m%d",local);
    }

    void getNowTimeStr(char * today)  //返回HHmmss
    {
        time_t lt;
        struct tm * local;
        lt = time(0);
        local = localtime(&lt);
        strftime(today,7,"%H%M%S",local);
    }

    long getNowTimeLong()
    {
        char	now[7];
        memset(now,0,sizeof(now));
        getNowTimeStr(now);

        return atol(now);
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
        getNowDateStr(now);

        return atol(now);
    }

    long getNowDateTimeLong()
    {
        char	now[15];
        memset(now,0,sizeof(now));
        getNowDateTimeStr(now);

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

    //进行日期的加减
    long  addDate(long origindate,int add)
    {
        time_t	timebuf;
        tm *tptr;
        tm  oldtime;
        long	nowdate;
        memset(&oldtime,0,sizeof(struct tm));
        oldtime.tm_year = origindate / 10000 - 1900;
        oldtime.tm_mon = (origindate % 10000) / 100 -1;
        oldtime.tm_mday = (origindate % 100);
        timebuf = mktime(&oldtime);
        timebuf += 24*3600*add;
        tptr = localtime(&timebuf);
        nowdate = (long)(tptr->tm_year+1900) * 10000;
        nowdate += (tptr->tm_mon + 1) * 100 + tptr->tm_mday;
        return nowdate;
    }

    //进行小时的加减
    long  addHour(long origidate, long origitime, long add)
    {
        time_t	timebuf;
        struct tm *tptr;
        struct tm  oldtime;
        long	nowdate;
        memset(&oldtime,0,sizeof(struct tm));
        oldtime.tm_year = origidate / 10000 - 1900;
        oldtime.tm_mon = (origidate % 10000) / 100 -1;
        oldtime.tm_mday = (origidate % 100);
        oldtime.tm_hour = origitime/10000;
        oldtime.tm_min  = (origitime%10000)/100; 
        oldtime.tm_sec  = origitime%100;
        timebuf = mktime(&oldtime);
        timebuf += 3600*add;
        tptr = localtime(&timebuf);
        nowdate = (long)((tptr->tm_year+1900) * 10000)*1000000;
        nowdate += ((tptr->tm_mon + 1) * 100 + tptr->tm_mday)*1000000;
        nowdate += tptr->tm_hour * 10000;
        nowdate += tptr->tm_min * 100;
        nowdate += tptr->tm_sec;
        
        return nowdate;
    }

    //传入两个YYYYMMDD格式的时间 返回间隔的天数
    long decDate(long oridate,long newdate) 
    {
        time_t timebuf1;
        time_t timebuf2;
        
        struct tm oldtime;
        struct tm newtime;
        long dec;
        memset(&oldtime,0,sizeof(struct tm));
        oldtime.tm_year = oridate / 10000 - 1900;
        oldtime.tm_mon = (oridate % 10000) / 100 -1;
        oldtime.tm_mday = (oridate % 100);
        timebuf1 = mktime(&oldtime);
        
        memset(&newtime,0,sizeof(struct tm));
        newtime.tm_year = newdate / 10000 - 1900;
        newtime.tm_mon = (newdate % 10000) / 100 -1;
        newtime.tm_mday = (newdate % 100);
        timebuf2 = mktime(&newtime);
        
        dec = (timebuf2-timebuf1)/(24*3600);
        return dec;
    }
    

    


}
#endif
