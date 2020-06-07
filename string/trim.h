#pragma once
namespace LibcuTrim
{
   
    //去除字符串左侧的字符
    int trimformatleft(char* srcstr,char ch)
    {
        char *buffer=NULL;
        int beg=-1;
        int i=-1;

        if(srcstr==NULL)
        {
            return 0;   
        }
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

    //去除字符串右侧的字符
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

    //去除字符串两侧的字符ch
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


    //去除字符串左侧的字符空格
    int LeftTrim( char *srcstr )
    {
    return trimformatleft(srcstr,' ');
    }


    
    //去除str结尾处的空格
    char * RightTrim ( char *str )
    {
    return trimformatright (str,' ');
    }

    
    //去除str两头的空格
    int Trim( char *str )
    {
        if(str==NULL)
        {
            return 0;   
        }
        return trimformat(str,' ');
    }


} 
