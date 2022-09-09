#include <QDebug>
#include "test.h"
//img will be overwritten with recomposition according to the "deco" coefficients and the fpalette.
int treatTheImage(unsigned char *img, double *deco, unsigned char *palette, int w,int h)
{
    int intpalette[9];for(int i=0;i<9;i++)intpalette[i]=(int)palette[i];
    //force palette colors' luminosity to 3 so coefficients don't get too small or big
    for(int i=0;i<9;i+=3){
        double L,C,H;
        RGB_to_LCH(intpalette[i],intpalette[i+1],intpalette[i+2],&L,&C,&H);
        L=3.;
        LCH_to_RGB(L,C,H,&intpalette[i],&intpalette[i+1],&intpalette[i+2]);
    }
    for(int i=0;i<9;i++)palette[i]=intpalette[i];

    double *fpalette = new double[9];
    //turn palette to LAB for reconstruction
    for(int i=0;i<9;i+=3){
      for(int k=0;k<3;k++)fpalette[i+k]=(double)palette[i+k];
      RGB_to_LAB(&fpalette[i],&fpalette[i+1],&fpalette[i+2]);
    }

    double *foimg = new double[w*h*3];

   //recompose image with harmonized palette
   fully_recompose_image(img,deco,foimg,fpalette,w,h);

   //convert recomposed image back to rgb for display
   for(int i=0;i<w*h*3;i+=3){
   	 LAB_to_RGB(&foimg[i],&foimg[i+1],&foimg[i+2]);
     for(int k=0;k<3;k++){
         img[i+k]=(unsigned char)foimg[i+k];
         //std::cout<<(int)img[i+k]<<std::endl;
       }
   }

   //qDebug()<<"first 4 of img : "<<(int)img[0]<<(int)img[1]<<(int)img[2]<<(int)img[3];
   qDebug()<<"all of palette : ";
   for(int i=0;i<9;i+=3){qDebug()<<(int)fpalette[i+0]<<(int)fpalette[i+1]<<(int)fpalette[i+2];}

   delete[](foimg);
   return 1;
}

//decomposes the image into 3, then fills deco with the displayable rgb decompositions, and deco with the decomposition coefficients.
//"deco" must be 3*h*w*3 big, fpalette 9 big, the others w*h*3.
void getDecompositionImages(unsigned char *img, unsigned char *deco, double *fimg, unsigned char *palette,int w,int h)
    {

        int intpalette[9];for(int i=0;i<9;i++)intpalette[i]=(int)palette[i];
        //force palette colors' luminosity to 3 so coefficients don't get too small or big
        for(int i=0;i<9;i+=3){
            double L,C,H;
            RGB_to_LCH(intpalette[i],intpalette[i+1],intpalette[i+2],&L,&C,&H);
            L=3.;
            LCH_to_RGB(L,C,H,&intpalette[i],&intpalette[i+1],&intpalette[i+2]);
        }
        for(int i=0;i<9;i++)palette[i]=intpalette[i];

        //store the palette result, and the image in double array for conversion to LAB
       double fpalette[9];
       for(int i=0;i<9;i++)fpalette[i]=(double)palette[i];

       for(int i=0;i<w*h*3;i++){
         fimg[i]=(double)img[i];
       }
       //convert image and palette to lab space
       for(int i=0;i<w*h*3;i+=3){
        RGB_to_LAB(&fimg[i],&fimg[i+1],&fimg[i+2]);
       }
       for(int i=0;i<9;i+=3){
        RGB_to_LAB(&fpalette[i],&fpalette[i+1],&fpalette[i+2]);
       }


       //decompose the image into 3 new channels, no longer L,a,b, but the palette colors.
       decompose_image(fimg,fimg,fpalette,w,h);

       //make the decomposition images before harmonizing the palette
       make_decomposition_images(fimg, deco, fpalette, w, h);


       qDebug()<<"all of palette : ";
       for(int i=0;i<9;i+=3){qDebug()<<(int)palette[i+0]<<(int)palette[i+1]<<(int)palette[i+2];}

    }

