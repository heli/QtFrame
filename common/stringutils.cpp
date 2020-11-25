#include "stringutils.h"

StringUtils::StringUtils()
{

}

const char* StringUtils::qStrToConstChar(QString str)
{
    if(str.isNull() || str.isEmpty()) {
        return "";
    }
    QByteArray ba = str.toLocal8Bit();
    return ba.constData();
    //std::string s = str.toStdString();
    //return s.c_str();
}

const char* StringUtils::dateTimeToConstChar(QDateTime dv)
{
    if(dv.isNull() ) {
        return "";
    }
    QString strBuffer = dv.toString("yyyy-MM-dd hh:mm:ss");
    return qStrToConstChar(strBuffer);
}

const char* StringUtils::longToConstChar(long lv)
{
    if(!lv) {
        return "";
    }
    QString ls = QString::number(lv);
    return qStrToConstChar(ls);
}
