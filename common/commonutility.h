#ifndef COMMONUTILITY_H
#define COMMONUTILITY_H

#include "commonutility_global.h"

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QFile>
#include <QFileInfo>
#include <QDir>
#include <QTextStream>
#include <QSettings>
#include <QList>

class CommonUtility
{

public:
    CommonUtility();
public:
    bool writeTextToFile(QString &aFileName, QString &aContent);
    QString readTextFromFile(QString &aFileName);
    bool writeJsonToFile(QString &aFileName, QJsonObject &aObj);
    QJsonObject readJsonFromFile(QString &aFileName);
    void writeSettingFile(const QString &aFileName, const QString &key, const QString &val);
    QSettings *readSettingFile(const QString &aFileName);
    QString readSettingFile(const QString &aFileName, const QString &key);
    QStringList listFileNameDir(const QString &szPath);
    QStringList listFilePathDir(const QString &szPath);
    bool delFileByName(const QString &szPath, const QString &fileName);
    bool delFileByPath(const QString &szPath);
    bool delFilesInPath(const QString &szPath);
    bool delDirByPath(const QString &szPath);
    bool copyFileToFile(const QString &srcFile ,const QString &toFile, bool coverFileIfExist);
    bool copyFileToPath(const QString &srcPath ,const QString &toPath, QString &fileName);
    bool copyDirectoryFiles(const QString &fromDir, const QString &toDir, bool coverFileIfExist);
};

#endif // COMMONUTILITY_H
