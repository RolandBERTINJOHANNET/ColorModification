#include <QDebug>
#include "colorOps.h"
//forcément palette de 3 couleurs
void decompose_color(double *outCoeffs, double *color, double *palette){
	double coeff[3][4];
	for(int i=0;i<9;i++){
		coeff[(i%3)][(i/3)]=palette[i];
	}
	for(int i=0;i<3;i++){
		coeff[i][3]=color[i];
	}

	findSolution(coeff, outCoeffs);
	//test
	double reco[3]={0.,0.,0.};
	for(int k=0;k<3;k++){
		reco[0]+=outCoeffs[k]*palette[3*k];
		reco[0+1]+=outCoeffs[k]*palette[3*k+1];
		reco[0+2]+=outCoeffs[k]*palette[3*k+2];
	}
	if(abs(reco[0]-color[0])>1){
		std::cout<<"problem : after : "<<reco[0]<<" before : "<<color[0]<<std::endl;
	}
}

void decompose_image(double *img, double *oimg, double *palette, int w, int h){
	for(int i=0;i<w*h*3;i+=3){
		double coeffs[3];
		decompose_color(coeffs, &img[i], palette);
		oimg[i]=coeffs[0];
		oimg[i+1]=coeffs[1];
		oimg[i+2]=coeffs[2];
	}
}



void recompose_image(double *coeffImg, double *oimg, double *palette, int w, int h){
	for(int i=0;i<w*h*3;i++)oimg[i]=0.;
	for(int i=0;i<w*h*3;i+=3){
		for(int k=0;k<3;k++){
			oimg[i]+=coeffImg[i+k]*palette[3*k];
			oimg[i+1]+=coeffImg[i+k]*palette[3*k+1];
			oimg[i+2]+=coeffImg[i+k]*palette[3*k+2];
            //std::cout<<oimg[i]<<", "<<oimg[i+1]<<", "<<oimg[i+2]<<std::endl;
		}
	}
}


void fully_recompose_image(unsigned char *original_img, double *fimg, double *foimg, double *npalette, int w, int h){
    qDebug()<<"first 4 of img : "<<fimg[0]<<fimg[1]<<fimg[2]<<fimg[3];
    qDebug()<<"first 4 of palette : "<<npalette[0]<<npalette[1]<<npalette[2]<<npalette[3];
	recompose_image(fimg,foimg,npalette,w,h);
	//normalize the values : first find the max and min
	
	double max = 0;
	double min=pow(2,16);
	for(int i=0;i<w*h*3;i++){
		if(foimg[i]>max){
			max=foimg[i];
		}if(foimg[i]<min){
			min=foimg[i];
		}
	}
	std::cout<<max<<", "<<min<<std::endl;
	//center and normalize
	for(int i=0;i<w*h*3;i++){
		//foimg[i] = 100.*(foimg[i])/(max-min);
		//if(foimg[i]>100 || foimg[i]<-100.)
		//	std::cout<<"value went beyond the range : "<<foimg[i]<<std::endl;
	}
/*
	//correct luminance to be same as original image
	for(int i=0;i<w*h*3;i+=3){
		double L,C,H;
		LAB_to_LCH(&foimg[i],&foimg[i+1],&foimg[i+2]);
		double l,c,h;
		RGB_to_LCH((int)original_img[i],(int)original_img[i+1],(int)original_img[i+2],&l,&c,&h);
		//foimg[i]=l;foimg[i+1]=c;
		LCH_to_LAB(&foimg[i],&foimg[i+1],&foimg[i+2]);
	}
	*/
}
