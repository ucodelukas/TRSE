#ifndef COMPRESSION_H
#define COMPRESSION_H

#include <QString>
#include <QByteArray>
#include <QFile>
#include "source/LeLib/limage/multicolorimage.h"
#include "source/LeLib/limage/charsetimage.h"
#include <QImage>
#include <math.h>
#include <QtMath>
class Compression
{
public:
    Compression();

    void SaveCharset(QString filename, QImage& img, int w, int h, int div);
    void AddScreen(QByteArray& data, QImage& img, int w, int h, char base, int div, char add1, char add2);
    void AddToDataX(QByteArray& data, CharsetImage& img,int x, int y, int w, int h);

    int Compare(QByteArray& a, QByteArray& b, int p1, int p2, int length);

    void OptimizeAndPackCharsetData(QByteArray& dataIn, QByteArray& out, QByteArray& table, int width, int compression);

    void ConvertToC64(bool dither);


};

#endif // COMPRESSION_H