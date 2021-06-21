#include "fileutils.h"

FilesUtils::FilesUtils()
{

}

QByteArray FilesUtils::buildFileString(QList<QUrl> urls)
{
    QString bound="margin";
    QByteArray data = "";
    data.append(QString("Content-Type: multipart/form-data; boundary=\""+bound+"\"\r\n\r\n").toUtf8()); //data type
    data.append(QString("--" + bound + "\r\n").toUtf8());
    data.append("Content-Disposition: form-data; name=\"codePatient\"\r\n\r\n");
    data.append("000013\r\n");

    for (QUrl url : urls){
        QString path = url.path().replace(0,1,"");
        //path.append("\\\\");
        //path.append(url.fileName());
        data.append(QString("--" + bound + "\r\n").toUtf8());
        data.append(QString("Content-Disposition: form-data; name=\"uploaded[]\"; filename=\"").toUtf8());
        data.append(QString(url.fileName()).toUtf8());
        data.append("\"\r\n");

        QFile file(path);
        if (!file.open(QIODevice::ReadOnly)){
            qDebug() << "QFile Error: File not found!";
            return data;
        } else { qDebug() << "File found, proceed as planned"; }

        data.append(file.readAll());
        data.append("\r\n");
        data.append(QString("--" + bound + "--\r\n").toUtf8());  //closing boundary according to rfc 1867
        file.close();
    }

    return data;
}
