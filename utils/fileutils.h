#ifndef FILEUTILS_H
#define FILEUTILS_H

#include <QByteArray>
#include <QString>
#include <QUrl>
#include <QFile>
#include <QDebug>

class FilesUtils
{
public:
    FilesUtils();
    static QByteArray buildFileString(QList<QUrl> urls);
};

#endif // FILEUTILS_H
