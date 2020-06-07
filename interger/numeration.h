#pragma once
#include"../common/common.h"
namespace LibcuNum
{
    //二进制转10进制
    long Bin2Dec(char *str)
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

    std::string Dec2A(int n,int radix)    //n是待转数字，radix是指定的进制
    {
        std::string ans="";
        do{
            int t=n%radix;
            if(t>=0&&t<=9)	ans+=t+'0';
            else ans+=t-10+'a';
            n/=radix;
        }while(n!=0);	//使用do{}while（）以防止输入为0的情况
        reverse(ans.begin(),ans.end());
        return ans;	
    }


}