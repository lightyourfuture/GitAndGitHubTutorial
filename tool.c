#include <time.h>
//希望将time_t类型转换成字符串,字符串格式为"年-月-日 时:分"
void timeToString(time_t t, char* pBuf)
{
    struct tm* pTimeInfo;
    pTimeInfo = localtime(&t);
    strftime(pBuf, 20,"%Y-%m-%d %H:%M", pTimeInfo);
}