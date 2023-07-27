#ifndef HZAXLE_H
#define HZAXLE_H

#include <QMainWindow>
#include <QByteArray>
#include <QStringList>





class hzaxle
{

public:
    void  StringToHex(QString str, QByteArray & senddata);
    char ConvertHexChar(char ch);
    static void AppendCRC16(QByteArray &datas);
    static unsigned short CalcCRC16(const QByteArray &datas);
    static void UInt2ByteArrayR(uint num, QByteArray& byteArray, int startIndex, int nBytes = 4);
  void sendspeed(QString speed, QByteArray & sendspeed);
    void Sleep(int msec);
    static QString ByteArray2String(const QByteArray& byteArray, bool split=true);
};

#endif // HZAXLE_H
