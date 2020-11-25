#include "commonutility.h"
#include <QtCore/QtCore>

CommonUtility::CommonUtility()
{

}

bool CommonUtility::writeTextToFile(QString &aFileName, QString &aContent)
{
    QFile aFile(aFileName);
    if (!aFile.open(QIODevice::WriteOnly | QIODevice::Text))
        return false;
    QTextStream aStream(&aFile); //用文本流读取文件
    aStream<<aContent; //写入文本流
    aFile.close();//关闭文件
    return true;
}

QString CommonUtility::readTextFromFile(QString &aFileName)
{
    QFile aFile(aFileName);
    if (!aFile.exists()) //文件不存在
        return "";
    if (!aFile.open(QIODevice::ReadOnly | QIODevice::Text))
        return "";
    QTextStream aStream(&aFile); //用文本流读取文件
    aStream.setAutoDetectUnicode(true); //自动检测Unicode,才能正常显示文档内的汉字
    return aStream.readAll();
}

QJsonObject CommonUtility::readJsonFromFile(QString &aFileName)
{
    //打开文件
    //QString path = QCoreApplication::applicationDirPath() + "/" + aFileName;
    QString path = aFileName;
    qDebug() << path;
    QFile file(path);
    file.open(QIODevice::ReadOnly);
    QByteArray data=file.readAll();
    file.close();
    //使用json文件对象加载字符串
    QJsonDocument doc=QJsonDocument::fromJson(data);
    //判断是否对象
    if(doc.isObject())
    {
        //把json文档转换为json对象
        QJsonObject obj=doc.object();
        return obj;
    }
    return QJsonObject();
}

bool CommonUtility::writeJsonToFile(QString &aFileName, QJsonObject &obj) {

    QJsonDocument document;
    document.setObject(obj);
    QByteArray byteArray = document.toJson();
    QString srJson(byteArray);
    return writeTextToFile(aFileName, srJson);
}

void CommonUtility::writeSettingFile(const QString &aFileName, const QString &key, const QString &val)
{
    QSettings *configIni = new QSettings(aFileName, QSettings::IniFormat);
    configIni->setValue(key, val);
    delete configIni;
}

QSettings *CommonUtility::readSettingFile(const QString &aFileName)
{
    QString path = QCoreApplication::applicationDirPath() + "/" + aFileName;
    QSettings *configIni = new QSettings(path, QSettings::IniFormat);
    return configIni;
}

QString CommonUtility::readSettingFile(const QString &aFileName, const QString &key)
{
    QString path = QCoreApplication::applicationDirPath() + "/" + aFileName;
    QSettings *configIni = new QSettings(path, QSettings::IniFormat);
    QString val = configIni->value(key).toString();
    delete configIni;
    return val;
}

QStringList CommonUtility::listFileNameDir(const QString &szPath) {
    QDir dir(szPath);
    if( !dir.exists() )
    {
        dir.mkpath(szPath);
    }
    QStringList list;
    foreach(QFileInfo fileInfo, dir.entryInfoList(QDir::Dirs|QDir::Files))
    {
        QString strName = fileInfo.fileName();
        if((strName == QString(".")) || (strName == QString("..")))
            continue;
        if(fileInfo.isFile()) {
            QString strPath = fileInfo.filePath();
            list << strName;
        }
    }
    return list;
}

QStringList CommonUtility::listFilePathDir(const QString &szPath) {
    QDir dir(szPath);
    if( !dir.exists() )
    {
        dir.mkpath(szPath);
    }
    QStringList list;
    foreach(QFileInfo fileInfo, dir.entryInfoList(QDir::Dirs|QDir::Files))
    {
        QString strName = fileInfo.fileName();
        if((strName == QString(".")) || (strName == QString("..")))
            continue;
        if(fileInfo.isFile()) {
            QString strPath = fileInfo.filePath();
            list << strPath;
        } else {
            list << listFilePathDir(fileInfo.filePath());
        }
    }
    return list;
}

bool CommonUtility::delFileByName(const QString &szPath, const QString &fileName) {
    QString filePath = szPath + fileName;
    QFileInfo fileInfo(filePath);
    if (fileInfo.isFile() || fileInfo.isSymLink())
    {
        QFile::setPermissions(filePath, QFile::WriteOwner);
        if (!QFile::remove(filePath))
        {
            return false;
        }
    }
    else if (fileInfo.isDir())
    {
        if (!delDirByPath(filePath))
        {
            return false;
        }
    }
    return true;
}

bool CommonUtility::delFileByPath(const QString &szPath) {
    QFileInfo fileInfo(szPath);
    if (fileInfo.isFile() || fileInfo.isSymLink())
    {
        QFile::setPermissions(szPath, QFile::WriteOwner);
        if (!QFile::remove(szPath))
        {
            return false;
        }
    }
    else if (fileInfo.isDir())
    {
        if (!delDirByPath(szPath))
        {
            return false;
        }
    }
    return true;
}

bool CommonUtility::delFilesInPath(const QString &szPath) {
    if (szPath.isEmpty())
        return false;

    QDir dir(szPath);
    if(!dir.exists())
        return true;

    dir.setFilter(QDir::AllEntries | QDir::NoDotAndDotDot);
    QFileInfoList fileList = dir.entryInfoList();
    foreach (QFileInfo fi, fileList)
    {
        if (fi.isFile())
            fi.dir().remove(fi.fileName());
        else
            delDirByPath(fi.absoluteFilePath());
    }
    return true;
}

bool CommonUtility::delDirByPath(const QString &szPath) {
    if (szPath.isEmpty())
        return false;

    QDir dir(szPath);
    if(!dir.exists())
        return true;

    dir.setFilter(QDir::AllEntries | QDir::NoDotAndDotDot);
    QFileInfoList fileList = dir.entryInfoList();
    foreach (QFileInfo fi, fileList)
    {
        if (fi.isFile())
            fi.dir().remove(fi.fileName());
        else
            delDirByPath(fi.absoluteFilePath());
    }
    return dir.rmpath(dir.absolutePath());
}

//拷贝文件：
bool CommonUtility::copyFileToFile(const QString &srcFile ,const QString &toFile,bool coverFileIfExist)
{
    //toFile.replace("\\","/");
    if (srcFile == toFile)
    {
        return true;
    }
    if (!QFile::exists(srcFile))
    {
        return false;
    }
    QDir *createfile = new QDir;
    bool exist = createfile->exists(toFile);
    if (exist)
    {
        if(coverFileIfExist)
        {
            createfile->remove(toFile);
        }
    }//end if

    if(!QFile::copy(srcFile, toFile))
    {
        return false;
    }
    return true;
}

//拷贝文件：
bool CommonUtility::copyFileToPath(const QString &srcPath ,const QString &toPath, QString &fileName)
{
    QString srcFile = srcPath + fileName;
    if(fileName.startsWith(srcPath)) {
        srcFile = fileName;
        fileName = fileName.replace(srcPath,"");
    }

    QString toFile = toPath + fileName;
    int idx = toFile.lastIndexOf("/");
    QString toDir = toFile.left(idx);
    QDir targetDir(toDir);
    if(!targetDir.exists())
    {
        if(!targetDir.mkdir(targetDir.absolutePath()))
        {
            return false;
        }
    }
    return copyFileToFile(srcFile, toFile, true);
}

bool CommonUtility::copyDirectoryFiles(const QString &fromDir, const QString &toDir, bool coverFileIfExist)
{
    QDir sourceDir(fromDir);
    QDir targetDir(toDir);
    if(!targetDir.exists())    /**< 如果目标目录不存在，则进行创建 */
    {
        if(!targetDir.mkdir(targetDir.absolutePath()))
            return false;
    }

    QFileInfoList fileInfoList = sourceDir.entryInfoList();
    foreach(QFileInfo fileInfo, fileInfoList)
    {
        if(fileInfo.fileName() == "." || fileInfo.fileName() == "..")
            continue;

        if(fileInfo.isDir())    /**< 当为目录时，递归的进行copy */
        {
            if(!copyDirectoryFiles(fileInfo.filePath(),
                                   targetDir.filePath(fileInfo.fileName()),
                                   coverFileIfExist))
                return false;
        }
        else            /**< 当允许覆盖操作时，将旧文件进行删除操作 */
        {
            if(coverFileIfExist && targetDir.exists(fileInfo.fileName()))
            {
                targetDir.remove(fileInfo.fileName());
            }

            /// 进行文件copy
            if(!QFile::copy(fileInfo.filePath(), targetDir.filePath(fileInfo.fileName())))
            {
                return false;
            }
        }
    }
    return true;
}
