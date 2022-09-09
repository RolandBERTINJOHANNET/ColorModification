#include "paletteimageprovider.h"
#include "functions/test.h"
#define STB_IMAGE_IMPLEMENTATION
#include "functions/stb_image.h"

#include <iostream>




void PaletteImageProvider::receivePalette(QList<unsigned char> palette){
    qDebug()<<"function was called";
    this->palette = new unsigned char[9];
    for(int i=0;i<9;i++){
        this->palette[i]=palette[i];
    }
}

QPixmap PaletteImageProvider::requestPixmap(const QString &id, QSize *size, const QSize &requestedSize)
{
   int x=0,y=0,num_channels;
   qDebug()<<id;
   QUrl temp(id);
   QString path = temp.toLocalFile();
   QByteArray ba = path.toLocal8Bit();
   const char *c_str2 = ba.data();
   unsigned char *img = stbi_load(c_str2,&x,&y,&num_channels,3);

   unsigned char *deco = new unsigned char [x*y*3*3];
   this->coeffs = new double[x*y*3];
   getDecompositionImages(img, deco, this->coeffs, palette,x,y);
   emit sendData(coeffs,x,y);

   QImage image(deco,x,y*3,QImage::Format_RGB888);
   int height =500;
   int width = 500 * (float(x)/(3.*float(y)));
   image = image.scaled(width,height);


   QPixmap pixmap;
   pixmap = QPixmap::fromImage(image);

   return pixmap;
}
