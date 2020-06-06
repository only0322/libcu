//#include"common/common.h"

#include"date/mydate.h"
using namespace LibcuDate;

int main(int argc,char* argv[])
{
    MyDate date;
    char  today[8+1];
    memset(today,0x00,sizeof(today));
    date.getNowDateStr(today);
    std::cout<<"date = "<<today<<std::endl;
    
    int i = date.getKimLarsen(today);
    std::cout<<"date = "<<i<<std::endl;

    return 0; 
}