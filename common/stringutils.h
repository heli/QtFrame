#ifndef STRINGUTILS_H
#define STRINGUTILS_H

#include <QObject>
#include <QDateTime>

class StringUtils
{
public:
    StringUtils();

    static const char* qStrToConstChar(QString str);
    static const char* dateTimeToConstChar(QDateTime dv);
    static const char* longToConstChar(long lv);
};

#endif // STRINGUTILS_H
