#include "modifimageprovider.h"
#include "functions/test.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "functions/stb_image_write.h"

#include <iostream>

void ModifImageProvider::receivePalette(QList<unsigned char> palette){
    this->palette = new unsigned char[9];
    for(int i=0;i<9;i++){
        this->palette[i]=palette[i];
    }
}

void ModifImageProvider::receiveDecomposition(double *coeffs, int w, int h) {
    this->coeffs = coeffs;
    this->w = w;
    this->h = h;
}

QPixmap ModifImageProvider::requestPixmap(const QString &id, QSize *size, const QSize &requestedSize)
{
   unsigned char *img = new unsigned char[this->w * this->h * 3];


   qDebug()<<"first 4 of coeffs : "<<coeffs[0]<<coeffs[1]<<coeffs[2]<<coeffs[3];
   qDebug()<<"first 4 of palette : "<<(int)palette[0]<<(int)palette[1]<<(int)palette[2]<<(int)palette[3];

   qDebug()<<"treating the image";
   //modify the values in a hardcoded way for now
   treatTheImage(img,this->coeffs,this->palette,w,h);
   qDebug()<<"treated the image";
   //save the image to a file
   stbi_write_png("result.png",w,h,3,img,w*3);

   QImage image(img,w,h,QImage::Format_RGB888);
   int height =500;
   int width = 500 * (float(w)/float(h));
   image = image.scaled(width,height);


   QPixmap pixmap;
   pixmap = QPixmap::fromImage(image);

   return pixmap;
}
