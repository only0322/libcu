//#include"common/common.h"

#include"date/mydate.h"
#include"string/trim.h"
using namespace LibcuDate;
using namespace std;
using namespace LibcuTrim;
int main(int argc,char* argv[])
{
    
    MyDate date;
    long last = 20200506;
    long now = date.getNowDateLong();
    long result = date.decDate(last,now);
    cout<<result<<endl;
    return 0; 
}