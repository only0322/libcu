//#include"common/common.h"

#include"date/mydate.h"
#include"string/trim.h"
#include"interger/numeration.h"
using namespace LibcuDate;
using namespace std;
using namespace LibcuTrim;
using namespace LibcuNum;
int main(int argc,char* argv[])
{
    
    
    char test[100] = "100001001000100";
    long des = Bin2Dec(test);
    cout<<des<<endl;
    return 0; 
}