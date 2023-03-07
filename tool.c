#include <time.h>
#include <stdio.h>
// 希望将time_t类型转换成字符串,字符串格式为"年-月-日 时:分"
void timeToString(time_t t, char *pBuf)
{
    struct tm *pTimeInfo;
    pTimeInfo = localtime(&t);
    strftime(pBuf, 20, "%Y-%m-%d %H:%M", pTimeInfo);
}
time_t stringToTime(char *pTime)
{
    struct tm tm1;
    time_t time1;

    sscanf(pTime, "%d-%d-%d %d:%d", &tm1.tm_year, &tm1.tm_mon, &tm1.tm_mday, &tm1.tm_hour, &tm1.tm_min);
    time1 = mktime(&tm1);
    return time1;
}