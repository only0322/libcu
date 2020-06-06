//#include"common/common.h"

#include"date/mydate.h"
using namespace LibcuDate;

int main(int argc,char* argv[])
{
    MyDate date;
    char  today[14+1];
    memset(today,0x00,sizeof(today));
    date.getNowDateTimeStr(today); 
    std::cout<<"date = "<<today<<std::endl;

    return 0; 
}