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
}