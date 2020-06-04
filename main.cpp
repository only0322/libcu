#include"common/common.h"

#include"date/mydate.h"
using namespace LibcuDate;

int main(int argc,char* argv[])
{
    MyDate date;
    char * today;
    date.getNowDateStr(today);
    std::cout<<"date = "<<today<<std::endl;
    return 0;
}