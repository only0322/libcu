#include"common.h"

#include"date/mydate.h"
using namespace Date;

int main(int argc,char* argv[])
{
    MyDate date;
    char * date = date.getNowDateStr();
    std::cout<<"date = "<<date<<std::endl;
    return 0;
}