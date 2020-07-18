#include "timethread.h"

timeThread::timeThread(QObject *parent) :
    QThread(parent)
{

}
//接受发送来的src和target信息
void timeThread::recvInfoSlot(QString src, QString target)
{
    this->target=target;
    this->src=src;
}

void timeThread::run( ){
    qDebug() << "调试4:";

    //建个文件信息类
    QFileInfo info(src);
    //获得文件大小
    qint64 bytes = info.size();

    QFile fileRead(src);
    fileRead.open(QIODevice::ReadOnly);

    QFile fileWrite(target);
    fileWrite.open(QIODevice::WriteOnly);

    QByteArray buf;
    double value=0;
    int i=0;


    while(!fileRead.atEnd())
    {
//      qDebug()<<"1";
        buf = fileRead.read(1024);

        fileWrite.write(buf);
        i++;
        value= double(1024*i)/double(bytes)*100;
        emit sendValueSign(value,i);

    }

    i=0;
    fileWrite.flush();
    fileWrite.close();
    fileRead.close();




}

