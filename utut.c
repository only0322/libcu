

int Read_Line_From_File(int fdTxnFile,char *linebuf,int bufsize)
{
	int	charnum;
	int	nErr;
	char	ch[1];

	charnum=0;
	do
	{	
		nErr=read(fdTxnFile,ch,1);
		if(nErr<=0)
		{
			BASLOG(LOG_LEVEL_ERROR,"Read File End or Error,%d,%s",errno,strerror(errno));
			return charnum;
		}
		else if(ch[0]!=0x0D &&ch[0]!=0x0A )
			charnum+=nErr;
			
		if(ch[0]==0x0D)
			continue;
			
		if(ch[0]!=0x0A)
		{
			linebuf[charnum-1] = ch[0];
		}
					
	}while((ch[0]!=0x0A)&&(charnum<bufsize));
	return charnum;
}


/*
* 返回形如20041001的日期字符串，以'\0'结尾
*
*/
void get_today_str(char * today)
{
	time_t lt;
	struct tm *local;

	lt = time(NULL);
	local = localtime(&lt);
	strftime(today, 9, "%Y%m%d", local);
}


/**
 * @功能:MMDD格式日期添加YYYY
 * @参数:
 *      buf			--[in|out]MMDD格式日期
 *      size		--buf的内存大小
 * @返回值:
 *      FAILURE--失败
 *      SUCCESS--成功
 */
int ConvMMDDToYYYYMMDD(char *buf, int size)
{
    char tempbuf[20]={0};
    char caCurrDate[8+1] = {0};
	if (size <= 8)
	{
	    BASLOG(LOG_LEVEL_ERROR,"buf size is too small ,size=[%d]",size);
		return -1;
	}
	if(strlen(buf)==8)   /*此处认为已经是8位的日期*/
	{
	    return 0;
	}
	
	if(4!= strlen(buf))
	{
	    BASLOG(LOG_LEVEL_ERROR,"buf data is err ,buf=[%s]",buf);
		return -1;
	}
	strcpy(tempbuf,buf);
	
	get_today_str(caCurrDate);
	
	char caYear[4+1] = {0};
	memcpy(caYear, caCurrDate, 4);
	int nYear = atoi(caYear);
	
	char caTmp[4+1] = {0};
	memcpy(caTmp, tempbuf, 4);

	/* 跨年判断  传入日期的月份与本地日期的月份，判断两个日期是否是同一年*/
	if (0 == memcmp(tempbuf, "12", 2) && 
		0 == memcmp(&caCurrDate[4], "01", 2)) 
	{
		/* 上一年的最后一个月与新一年的第一月,需要减1年 */
		nYear--;
		snprintf(buf, size, "%04d%s", nYear,tempbuf);
	}
	else if (0 == memcmp(tempbuf, "01", 2) && 
			 0 == memcmp(&caCurrDate[4], "12", 2))
	{
		/* 新一年的第一月与上一年的最后一月,需要加1年 */
		nYear++;
		snprintf(buf, size, "%04d%s", nYear,tempbuf);
	}
	else
	{/* 使用当前年份 */
		snprintf(buf, size, "%s%s", caYear, caTmp);
	}
	return 0;
}


/*将YYMMDD的日期补充为YYYYMMDD\
src :YYMMDD
des:YYYYMMDD
*/
void FillYYdate(char *des,char *src)
{
    char tempbuf[20]={0};
    int  i,j;
    char tempbuf1[3]={0};
    char tempbuf2[3]={0};

    get_today_str(tempbuf);    /*获取当前日期*/
    memcpy(tempbuf1,tempbuf+2,2); /*获取当前日期年份后两位*/
    i=atoi(tempbuf1);
    if((i>0)&&(i<99))
    {
        memcpy(des,tempbuf,2);
        memcpy(des+2,src,6); 
        return ;
    }
    memcpy(tempbuf2,src,2);  /*传入数据的年*/
    j=atoi(tempbuf2);
    
    memset(tempbuf2,0,sizeof(tempbuf2));
    memcpy(tempbuf2,tempbuf,2);  /*取系统日期，年高两位*/
    if((i==0)&&(j==99))
    {
        sprintf(tempbuf1,"%02d",atoi(tempbuf2)-1);
    }
    if((i==99)&&(j==0))
    {
        sprintf(tempbuf1,"%02d",atoi(tempbuf2)+1);
    }
    memcpy(des,tempbuf1,2);
    memcpy(des+2,src,6); 
    return ; 
}

time_t str2time(char* src)
{
	struct tm	tmptm;
	long ldate;
	long year;
	long month;
	long day;
	time_t ret;
	
	ldate=atol(src);
	year=ldate/10000;
	month=(ldate/100)%100;
	day=ldate % 100;
	
	memset(&tmptm,0,sizeof(struct tm));
	tmptm.tm_year=year-1900;
	tmptm.tm_mon=month-1;
	tmptm.tm_mday=day;
	
	ret=mktime(&tmptm);
	
	return ret;
}

/* 功能概述	生成系统时间戳
 * 输入参数	无
 * 输出参数	stamp 为字符串型,15位,格式为YYYYMMDDHHMMSS
 * 返回值       无  		
 */
void Get_TimeStamp(char * stamp)
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

/* 功能概述		二进制(无符号)转十进制
 * 输入参数		char *str
 *                      
 * 输出参数		
 * 返回值	    int 十进制数值
 */
int Bin2Dec(char *str)
{
	long i,j,t,len,result=0;
	
	len = strlen(str) -1;
	for (i = len; i >=0 ; i--)
	{
		t = str[i] - 48;
		for (j=0;j < len-i;j++ )
		{
			t*=2;
		}
		result += t;
	}
	return result;
}

/* 功能概述		取字串
 * 输入参数		char *pszString
 *							int iStart
 *							int iSubLength
 *							char *pszSubString               
 * 输出参数		
 * 返回值			> 0 成功
 *							-1 失败 
 */
int MidStr( char *pszString, int iStart, int iSubLength, char *pszSubString )
{
	int		iReturn = 0;
	int		iLength;
	
	iLength = strlen( pszString );
	
	if( (iStart >= iLength) ) 
	{
		return	-1;
	}	
	if( (iStart < 0) ) 
	{
		return	-1;
	}
	if( iSubLength < 0 ) 
	{
		return	-1;
	}
	if( iSubLength > (iLength - iStart) ) 
	{
		iSubLength = iLength - iStart;
		iReturn = -1;
	}	
	strncpy( pszSubString, (pszString + iStart), iSubLength );
	*(pszSubString + iSubLength) = 0;
	
	return	iReturn;	
}




/* 获得当前时间的字符串表示 */
/*
+============================================================================
| Function : void get_now( char *buf,int lenght,char* fmt ) 
| Desc     : 根据用户传入的时间格式fmt返回当前的时间
| Input    : fmt 
|           length
| Output   : buf  - pointer to destination buffer
| Return   : NONE
|
| Modify By:
|   Name  liukougen     Date  20041001      Desc
|
+============================================================================
*/
void get_now(char *buf,int length,char* fmt)
{
	char	today[18]={0};
	time_t lt;
	struct tm *local;
	
	lt = time(NULL);
	local = localtime(&lt);
	strftime(today,length,fmt,local);
	strcpy(buf,today);
}


long  get_full_time()
{
	char time_buf[19];
	long  time_long;
	get_now(time_buf,18,"%Y%m%d%H%M%S");
	time_long=atol(time_buf); 
	return time_long;
}




long get_today_long()
{
	char	now[9];
	
	memset(now,0,sizeof(now));
	get_today_str(now);
	
	return atol(now);
	
}
/*
*  get_nowtime_str的简化版本返回形如091016( 时分秒)的时间字符串，以'\0'结尾
*  
*/

void get_nowtime_str(char * now)
{
	time_t lt;
	struct tm *local;

	lt = time(NULL);
	local = localtime(&lt);
	strftime(now,9,"%H%M%S",local);
}


/*
*  get_nowtime_long的返回形如091016( 时分秒)的时间
*  
*/
long get_nowtime_long()
{
	char	now[9];
	
	memset(now,0,sizeof(now));
	get_nowtime_str(now);
	
	return atol(now);
	
}



/*非线程安全*/
char *strtime()
{
        time_t timebuf;
        struct tm *ptr;
        static char     t_str[20];

        timebuf = time((time_t *) 0);
        ptr = localtime(&timebuf);
        ptr->tm_mon += 1;
        ptr->tm_year += 1900;
        sprintf(t_str,"%04d-%02d-%02d %02d:%02d:%02d",
                ptr->tm_year,ptr->tm_mon,ptr->tm_mday,ptr->tm_hour,
                ptr->tm_min,ptr->tm_sec);
        return t_str;
}

/*
* 获得当前日期的下一个日期
*/
long new_date(long origidate)
{
	time_t	timebuf;
	struct tm *tptr;
	struct tm  oldtime;
	long	nowdate;
	memset(&oldtime,0,sizeof(oldtime));
	oldtime.tm_year = origidate / 10000 - 1900;
	oldtime.tm_mon = (origidate % 10000) / 100 -1;
	oldtime.tm_mday = (origidate % 100);
	timebuf = mktime(&oldtime);
	timebuf += 24*3600;
	tptr = localtime(&timebuf);
	nowdate = (long)(tptr->tm_year+1900) * 10000;
	nowdate += (tptr->tm_mon + 1) * 100 + tptr->tm_mday;
	return nowdate;
}



int mksem_exclusive(key_t key)
{
        int sid;
        union semun
        {
                int val;
                struct sendid_ds *buf;
                unsigned short array[1];
        } arg;
        
        if((sid=semget(key,1,0666))==-1)
        {
        	return -1;
        }
        else
        {
        	 return sid;
		}
		
        return sid;
}



/*
* 根据key获取共享资源,如果指定的共享资源不存在,则创建,并初始化为1
*/
int mksem(key_t key)
{
        int sid;
        union semun
        {
                int val;
                struct sendid_ds *buf;
                unsigned short array[1];
        } arg;
        
        if((sid=semget(key,1,0666))==-1)
        {        	
        	if((sid=semget(key,1,0666|IPC_CREAT))==-1) 
        		return(-1);
			arg.val=1;
			semctl(sid,0,SETVAL,arg);
		}
        return sid;
}




int semcall(int sid,int op)
{
	struct sembuf sbuf;

	sbuf.sem_num=0;
	sbuf.sem_op=op;
	sbuf.sem_flg=0;
	
	if((semop(sid,&sbuf,1))==-1)
	{
		BASLOG(LOG_LEVEL_ERROR,"   failed\n"); 
	    return -1;
	}
	return 0;
}


int P_OP(int sid)
{
    return(semcall(sid ,-1));
}

int V_OP(int sid)
{
        return(semcall(sid,1));
}

int add_process(int sid,long *pint )
{	
	if(P_OP(sid))
	{
		return -1;
	}
	
    *pint+=1;
    
    if(V_OP(sid))
	{
		return -1;
	} 
    return 0;
}

int minus_process(int sid,long *pint)
{
	
	if(P_OP(sid))
	{		
		return -1;
	} 
	
    *pint-=1;
    
    if(*pint <0)
    	*pint=0;    
    	
    if(V_OP(sid))
	{
		return -1;
	}    
   
   return 0;
}


int minus_process_byvalue(int sid,long *pint,int value)
{
	
	if(P_OP(sid))
	{		
		return -1;
	} 
	/*mode by liukougen20100124*/
     *pint-=value;
    
    if(*pint <0)
    	*pint=0;    
    	
    if(V_OP(sid))
	{
		return -1;
	}    
   return 0;
}



/*
* 进行日期的加减。
*origidate ：如20041012
*add>0 日期加 add 天，add<0，日期减 |add|天 
*/
long  add_date(long origidate,int add)
{
	time_t	timebuf;
	struct tm *tptr;
	struct tm  oldtime;
	long	nowdate;
	memset(&oldtime,0,sizeof(struct tm));
	oldtime.tm_year = origidate / 10000 - 1900;
	oldtime.tm_mon = (origidate % 10000) / 100 -1;
	oldtime.tm_mday = (origidate % 100);
	timebuf = mktime(&oldtime);
	timebuf += 24*3600*add;
	tptr = localtime(&timebuf);
	nowdate = (long)(tptr->tm_year+1900) * 10000;
	nowdate += (tptr->tm_mon + 1) * 100 + tptr->tm_mday;
	return nowdate;
}

/*
* 进行小时的加减。
*origidate ：如20041012010101
*add>0 时间加 add 小时，add<0，时间减 |add|小时 
*/
long  add_hour(long origidate, long origitime, long add)
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


/*
* 进行日期的比较，返回天数。
*oridate ：如20041001
*newdate : 如20041101
*           则 dec=30
*dec>0 即 newdate>oridate
*/
long
#if defined(__STDC__) || defined(__cplusplus)
dec_date(long oridate,long newdate)
#else
dec_date(oridate, newdate)
long oridate;
long newdate;
#endif
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

/*
* 进行月份的加减。
*origidate ：如200410  add:月
*add>0 月份加 ，add<0，月份减 |add|
*/
long 
#if defined(__STDC__) || defined(__cplusplus)
add_month(long origidate,int add)
#else
add_month(origidate,add)
long origidate;
int add;
#endif
{
	int month;
	int year;
	int addyear;
	int leftmonth;
	addyear=0;
	year=origidate/100;
	month=origidate%100;
	if(add>0){
        addyear=add/12;
        leftmonth=add%12;
        addyear+=(month+leftmonth)/12;
        month=(month+leftmonth)%12;
        if(month==0)
        {
            month=12;
            addyear=addyear-1;
        }
        year=year+addyear;
        return (year*100+month);
	}else{
        add=-add;
        addyear=add/12;
        leftmonth=add%12;
        if(leftmonth>=month)
        {
              month=(month+12-leftmonth);
              addyear=addyear+1;
        }
        else
             month=month-leftmonth;
        year=year-addyear;
        return(year*100+month);
	}
}


/*
* 完整的日期进行月份的加减。
*origidate ：如20041012  add:月
*add>0 月份加 ，add<0，月份减 |add|
*/
long 
#if defined(__STDC__) || defined(__cplusplus)
add_month_day(long origidate,int add)
#else
add_month_day(origidate,add)
long origidate;
int add;
#endif
{
    int year;
	int yearmonth;
	int day;
	int newmonth;
	int newyearmonth;
	
	
	yearmonth=origidate/100;
	day=origidate%100;
	newyearmonth=add_month(yearmonth,add);
	
	year=newyearmonth/10000;
	newmonth=newyearmonth%100;
	
	switch(newmonth)
	{
		case 4:
		case 6:
		case 9:
		case 11:
		 if(day>=30)
		   day =30;
		   break;
	    case 2:
	        if (((year%4== 0)&&(year%100!=0)) ||(year%400 == 0)) /*闰年*/
	        {
	            if(day>=29)
		         day =29;
	        }else
	        {
		      if(day>=28)
		         day =28;;
	        }
	       break;
	    default:
	      break;          
	}
	return newyearmonth*100+day;
}


/*检查日期是否合法 （日期格式形如20040101)*/
int Checkdate(char *l_date)
{
	int year;
	int month;
	int day;
	char syear[5];
	char smonth[3];
	char sday[3];
	
	memset(syear,0,sizeof(syear));
	memset(smonth,0,sizeof(smonth)); 
	memset(sday,0,sizeof(sday));
	
	if(l_date<=0)
			return -1;
	if(strlen(l_date)!=8)
		return -1;
	memcpy(syear,l_date,4);
	memcpy(smonth,l_date+4,2);
	memcpy(sday,l_date+6,2);
	
	year=atoi(syear);
	month=atoi(smonth);
	day=atoi(sday);
	if((month<1)||(month>12)||(day<1)||(day>31))
		return -1;
	switch(month)
	{
		case 4:
		case 6:
		case 9:
		case 11:
		 if(day==31)
		   return -1;
	}
	if((month==2)&&(day>29))
		return -1;
	if (((year%4== 0)&&(year%100!=0)) ||(year%400 == 0)) /*闰年*/
	{
		;
	}else
	{
		if((month==2)&&(day==29))
		{
			return -1;
		}
	}
	return 0;
}



/*
	返回两个时间之间的相差日子数
	输入时间格式：YYYYMMDD
*/
int nDiffDate( char *date1, char *date2 )
{
   time_t       st1,st2;
   struct tm    s_tm1,s_tm2;
   char         year1[5],year2[5];
   char         mon1[3],mon2[3];
   char         day1[3],day2[3];

   memset(year1,0,5);
   memset(mon1,0,3);
   memset(day1,0,3);
   memset(year2,0,5);
   memset(mon2,0,3);
   memset(day2,0,3);

   memcpy(year1,date1,4);
   memcpy(mon1,date1+4,2);
   memcpy(day1,date1+6,2);
   memcpy(year2,date2,4);
   memcpy(mon2,date2+4,2);
   memcpy(day2,date2+6,2);

   memset(&st1,0,sizeof(st1));
   s_tm1.tm_mday=atoi(day1);
   s_tm1.tm_mon=atoi(mon1)-1;
   s_tm1.tm_year=atoi(year1)-1900;
   s_tm1.tm_isdst=0;

   memset(&s_tm2,0,sizeof(s_tm2));
   s_tm2.tm_mday=atoi(day2);
   s_tm2.tm_mon=atoi(mon2)-1;
   s_tm2.tm_year=atoi(year2)-1900;
   s_tm2.tm_isdst=0;

   st1=mktime(&s_tm1);
   st2=mktime(&s_tm2);

   return ((int)difftime(st2,st1)/(3600*24));
}






/*去除字符串左侧的字符ch*/
int trimformatleft(char* srcstr,char ch)
{
	char *buffer=NULL;
	int beg=-1;
	int i=-1;

    if(srcstr==NULL)
    {
        return 0;   
    }
	/*Locate the left blank*/
	for(i=0;i<strlen(srcstr);i++)
	{
		if(srcstr[i]!=ch)
		{
			beg=i;
			break;
		}
	}
	
	if(beg>0)
	{
	    buffer=(char *)calloc(strlen(srcstr)-beg+100,sizeof(char));
	    if(buffer==NULL)
	       return -1;
		strcpy(buffer,&srcstr[beg]);
		strncpy(srcstr,buffer,strlen(buffer)+1);
		free(buffer);
	}
	return 0;
}

/*去除字符串右侧的字符ch*/
char * trimformatright(char* str,char ch)
{
    char    *s = str;

    if(str==NULL)
    {
        return str;   
    }
    while ( *s )
        ++s;
    if( s == str ) return str;
        --s;
    while ( s >= str )
        if ( *s == ch )
        {
            *s = 0;
            --s;
        }
        else
            break;
    return str;
}

/*去除字符串两侧的字符ch*/
int trimformat(char* srcstr,char ch)
{
    int i=0;
	
	i=trimformatleft(srcstr,ch);
	if(i)
	{
	    return i;   
	}
	
    trimformatright(srcstr,ch);
	return 0;
}


/*去除字符串左侧的字符空格*/
int LeftTrim( char *srcstr )
{
   return trimformatleft(srcstr,' ');
}


/*
 *  去除str结尾处的空格
 */
char * RightTrim ( char *str )
{
   return trimformatright (str,' ');
}

/*
 *  去除str俩头的空格
 */
int Trim( char *str )
{
    if(str==NULL)
    {
        return 0;   
    }
    return trimformat(str,' ');
}

/********************************************************************
* 函数名称:	dec_year
* 函数描述:	计算两个日期之间的年份份间隔
* 输入参数:	long	lDate1		格式 YYYYMMDD Or YYYYMM Or YYYY
*			    long	lDate2		格式 YYYYMMDD Or YYYYMM Or YYYY
* 输出参数:	
* 返回值  :    
*			0:  成功
*			-1: 失败
* 调用者  :
********************************************************************/
int dec_year(long lDate1,long lDate2)
{
	char	strTemp[10],strTemp1[10];
	int 	iYear1,iYear2;
	int 	iMonth1,iMonth2;
	
	memset(strTemp,0x00,sizeof(strTemp));
	sprintf(strTemp,"%d",lDate1);
	
	memset(strTemp1,0x00,sizeof(strTemp1));
	memcpy(strTemp1,strTemp,4);
	iYear1 = atoi(strTemp1);
	
	memset(strTemp,0x00,sizeof(strTemp));
	sprintf(strTemp,"%d",lDate2);
	
	memset(strTemp1,0x00,sizeof(strTemp1));
	memcpy(strTemp1,strTemp,4);
	iYear2 = atoi(strTemp1);
	
	return abs(iYear1 - iYear2);
}

/*****************************************************************
* 函数名称:	dec_month
* 函数描述:	计算两个日期之间的月份间隔
* 输入参数:	long	lDate1		格式 YYYYMMDD Or YYYYMM
*			long	lDate2		格式 YYYYMMDD Or YYYYMM
* 输出参数:	
* 返回值  :    
*			0:  成功
*			-1: 失败
* 调用者  :
********************************************************************/
int dec_month(long	lDate1,long	lDate2)
{
	char	strTemp[10],strTemp1[10];
	int 	iYear1,iYear2;
	int 	iMonth1,iMonth2;
	
	memset(strTemp,0x00,sizeof(strTemp));
	sprintf(strTemp,"%d",lDate1);
	
	memset(strTemp1,0x00,sizeof(strTemp1));
	memcpy(strTemp1,strTemp,4);
	iYear1 = atoi(strTemp1);
	memset(strTemp1,0x00,sizeof(strTemp1));
	memcpy(strTemp1,strTemp + 4,2);
	iMonth1 = atoi(strTemp1);
	
	memset(strTemp,0x00,sizeof(strTemp));
	sprintf(strTemp,"%d",lDate2);
	
	memset(strTemp1,0x00,sizeof(strTemp1));
	memcpy(strTemp1,strTemp,4);
	iYear2 = atoi(strTemp1);
	memset(strTemp1,0x00,sizeof(strTemp1));
	memcpy(strTemp1,strTemp + 4,2);
	iMonth2 = atoi(strTemp1);
	
	return abs((iYear1 * 12 + iMonth1) - (iYear2 * 12 + iMonth2));
}

/*****************************************************************
* 函数名称:	compare_datetime
* 函数描述:	比较日期时间大小
* 输入参数:	long date1    日期1
*			long time1    时间1
*           long date2    日期2
*           long time2    时间2
* 输出参数:	
* 返回值  :    
*			1:   日期时间1 >= 日期时间2
*			0:   日期时间1 < 日期时间2
* 调用者  :
********************************************************************/
int compare_datetime(long date1,long time1,long date2,long time2)
{
   char sDate1[15]={0};
   char sDate2[15]={0};
   int  iVal;
   sprintf(sDate1,"%08ld%06ld",date1,time1);
   sprintf(sDate2,"%08ld%06ld",date2,time2); 
   iVal=strncmp(sDate1,sDate2,14);
   if (iVal >=0
)
    return 1;
    return 0;
}



/********************************************************************
* 函数名称:    Check_Data_Directory
* 函数描述:    检查数据目录是否存在，不存在则建立。                          
* 输入参数: char *dirname
* 输出参数:
* 返回值  :    
	           0:  成功
	           -1: 失败
* 调用者  :    本文件main
********************************************************************/
int Check_Data_Directory(char *dirname)
{
	char	cmd[1024];	
	if(access(dirname,F_OK)!=0)                          
	{
		memset(cmd,0,sizeof(cmd));
		strcpy(cmd,"mkdir -p ");
		strcat(cmd,dirname); 
		system(cmd);
	}
	
	if(access(dirname,F_OK)!=0)
	{
		BASLOG(LOG_LEVEL_ERROR," [%s] Data Directory NOT exist.\n",dirname);
		return -1;		
	}
	
	return 0;
}

/*****************************************************************
* 函数名称:    LeftAddZero
* 函数描述:    左补零
* 输入参数:    char *pstrSrcStr            待补零的字符串
*              int iDstLen                 补零后的字节长度
* 输出参数:    char *pstrDstBuf            补零后的字符串
* 返回值  :    
* 调用者  :    
********************************************************************/
int LeftAddZero (char *pstrDstBuf,char *pstrSrcStr, int iDstLen)
{	
	int     i;
	Trim(pstrSrcStr);
	for (i = 0; i < iDstLen - strlen(pstrSrcStr); i++)    
	{		
		if (pstrDstBuf[i] == 0x00)			
			pstrDstBuf[i] = '0';	
	}		
	strcpy(&pstrDstBuf[i],pstrSrcStr);	
	return 0;
}

/*****************************************************************
* 函数名称:    RightAddZero
* 函数描述:    右补零
* 输入参数:    char *sStr            待补零的字符串
*              int nLen              长度
* 输出参数:    无
* 返回值  :    
* 调用者  :    
********************************************************************/
int RightAddZero (char *sStr, int nLen)
{
	int     i;
	
	for (i = 0; i < nLen; i++)
		if (sStr[i] == 0x00)
			sStr[i] = '0';
	return 0;
}


