#include "harmonie.h"
double hue_distance(double hue1, double hue2){
  int counter_clockwise = hue1>hue2?hue1-hue2:360-hue2+hue1;
  int clockwise = hue1<hue2?hue2-hue1:hue2+(360-hue1);
  return clockwise>counter_clockwise?counter_clockwise:clockwise;
}
double norm_in_palette(double *paletteLoc){
  return sqrt(pow(paletteLoc[0],2)+pow(paletteLoc[1], 2) + pow(paletteLoc[2],2));
}

void normalize_in_palette(double *paletteLoc){
  double norm = norm_in_palette(paletteLoc);
  for(int i=0;i<3;i++){
    paletteLoc[i]/=norm;
  }
}

void make_palette_image_array(unsigned char *img, unsigned char *palette, int nbColors){
  double step = 600;
  for(int w = 0;w<1800;w+=3){
    //index, in palette, of color being drawn
    int idx=w/600;
    for(int h = 0;h<200;h++){
      img[h*1800 + w]=palette[idx*3];
      img[h*1800 + w +1]=palette[idx*3+1];
      img[h*1800 + w +2]=palette[idx*3+2];
    }
  }
}

//will be of size w*(3*h) (pixels)
void make_decomposition_images(double *coeff_img, unsigned char *oimg, double *fpalette, int w, int h){

  //normalize coefficients to get a sensible result
  double max=0;
  double min=pow(2,16);
  for(int i=0;i<w*h*3;i++){
    if(max<coeff_img[i])max=coeff_img[i];
    if(min>coeff_img[i])min=coeff_img[i];
  }



  //make the first one
  int channel=0;
  int offset=0;

  double rgbPalColor[3];
  for(int l=0;l<3;l++)rgbPalColor[l]=fpalette[channel*3+l];
  //ajuster saturation, juste pour l'affichage
  LAB_to_LCH(&rgbPalColor[0],&rgbPalColor[1],&rgbPalColor[2]);
  rgbPalColor[1]=rgbPalColor[1]>3.?rgbPalColor[1]:3.;
  LCH_to_LAB(&rgbPalColor[0],&rgbPalColor[1],&rgbPalColor[2]);
  //passer en RGB
  LAB_to_RGB(&rgbPalColor[0],&rgbPalColor[1],&rgbPalColor[2]);

  for(int i=0;i<h;i++){
    for(int j=0;j<w*3;j+=3){
      for(int k=0;k<3;k++){
        double coeff = (coeff_img[i*w*3+ j + channel]-min)/(max-min);
        oimg[(offset+i)*w*3 +j  +k] = coeff * rgbPalColor[k];
        if(coeff * rgbPalColor[k]>255. || coeff * rgbPalColor[k]<0.)std::cout<<coeff * rgbPalColor[k]<<std::endl;
      }
    }
  }

  //make the second one
  channel=1;
  offset=h;

  rgbPalColor[3];
  for(int l=0;l<3;l++)rgbPalColor[l]=fpalette[channel*3+l];
  //ajuster saturation, juste pour l'affichage
  LAB_to_LCH(&rgbPalColor[0],&rgbPalColor[1],&rgbPalColor[2]);
  rgbPalColor[1]=rgbPalColor[1]>3.?rgbPalColor[1]:3.;
  LCH_to_LAB(&rgbPalColor[0],&rgbPalColor[1],&rgbPalColor[2]);
  //passer en RGB
  LAB_to_RGB(&rgbPalColor[0],&rgbPalColor[1],&rgbPalColor[2]);

  for(int i=0;i<h;i++){
    for(int j=0;j<w*3;j+=3){
      for(int k=0;k<3;k++){
        double coeff = (coeff_img[i*w*3+ j + channel]-min)/(max-min);
        oimg[(offset+i)*w*3 +j  +k] = coeff * rgbPalColor[k];
        if(coeff * rgbPalColor[k]>255. || coeff * rgbPalColor[k]<0.)std::cout<<coeff * rgbPalColor[k]<<std::endl;
      }
    }
  }

  //make the third one
  channel=2;
  offset=2*h;

  rgbPalColor[3];
  for(int l=0;l<3;l++)rgbPalColor[l]=fpalette[channel*3+l];
  //ajuster saturation, juste pour l'affichage
  LAB_to_LCH(&rgbPalColor[0],&rgbPalColor[1],&rgbPalColor[2]);
  rgbPalColor[1]=rgbPalColor[1]>3.?rgbPalColor[1]:3.;
  LCH_to_LAB(&rgbPalColor[0],&rgbPalColor[1],&rgbPalColor[2]);
  //passer en RGB
  LAB_to_RGB(&rgbPalColor[0],&rgbPalColor[1],&rgbPalColor[2]);

  for(int i=0;i<h;i++){
    for(int j=0;j<w*3;j+=3){
      for(int k=0;k<3;k++){
        double coeff = (coeff_img[i*w*3+ j + channel]-min)/(max-min);
        oimg[(offset+i)*w*3 +j  +k] = coeff * rgbPalColor[k];
        if(coeff * rgbPalColor[k]>255. || coeff * rgbPalColor[k]<0.)std::cout<<coeff * rgbPalColor[k]<<std::endl;
      }
    }
  }

}

void move_hue_towards_hue(double *hstart, double hend, int amount){
      //get direction of closest distance between the two hues in chromatic circle.
      int counter_clockwise = hend>*hstart?hend-*hstart:360-*hstart+hend;
      int clockwise = hend<*hstart?*hstart-hend:*hstart+(360-hend);
      int direction = clockwise>counter_clockwise?1:-1;
      for(int k=0;k<amount&&int(*hstart)!=int(hend);k++){
        (*hstart)=int((*hstart)+direction)%360;
        if((*hstart)<0.)(*hstart)+=360.;
      }
}

void harmonize_monochromatic(int max_cluster, int second_cluster, int smallest_cluster, double *hues, int rotation){
  double dominant_H = hues[max_cluster];
  for(int i=0;i<3;i++){
    if(i!=max_cluster){
      move_hue_towards_hue(&hues[i],hues[max_cluster],rotation);
    }
  }
}

void harmonize_complementary(int max_cluster, int second_cluster, int smallest_cluster, double *hues, int rotation){
  double dominant_H = hues[max_cluster];
  double complementary_hues[2];
  complementary_hues[0]=hues[max_cluster];
  complementary_hues[1]=int(complementary_hues[0]+180)%360;
  //if the second biggest cluster doesn't shift to the complementary, the third one has to
  if(hue_distance(hues[second_cluster],complementary_hues[1])>hue_distance(hues[second_cluster],complementary_hues[0])){
    move_hue_towards_hue(&hues[second_cluster],complementary_hues[0],rotation);
    move_hue_towards_hue(&hues[smallest_cluster],complementary_hues[1],rotation);
  }//otherwise it goes to closest hue
  else{
    move_hue_towards_hue(&hues[second_cluster],complementary_hues[1],rotation);
    if(hue_distance(hues[smallest_cluster],complementary_hues[1])>hue_distance(hues[smallest_cluster],complementary_hues[0])){
    move_hue_towards_hue(&hues[smallest_cluster],complementary_hues[0],rotation);
    }else move_hue_towards_hue(&hues[smallest_cluster],complementary_hues[1],rotation);
  }
}

void harmonize_triadic(int max_cluster, int second_cluster, int smallest_cluster, double *hues, int rotation){
  double dominant_H = hues[max_cluster];
  double triadic_hues[3];
  triadic_hues[0]=hues[max_cluster];
  triadic_hues[1]=int(triadic_hues[0]+120)%360;
  triadic_hues[2]=int(triadic_hues[0]+240)%360;
  //second cluster is assigned to its closest color that isn't the main cluster's color.
  //third cluster goes to whichever is left.
  if(hue_distance(hues[second_cluster],triadic_hues[1])>hue_distance(hues[second_cluster],triadic_hues[2])){
    move_hue_towards_hue(&hues[second_cluster],triadic_hues[2],rotation);
    move_hue_towards_hue(&hues[smallest_cluster],triadic_hues[1],rotation);
  }
  else{
    move_hue_towards_hue(&hues[second_cluster],triadic_hues[1],rotation);
    move_hue_towards_hue(&hues[smallest_cluster],triadic_hues[2],rotation);
  }
}



void harmonize_palette(double *fpalette, int *freq){
  //get palette hues
  double hues[3];
  for(int i=0;i<9;i+=3){
    double L,C,H;
    LAB_to_LCH(&fpalette[i],&fpalette[i+1],&fpalette[i+2]);
    hues[i/3]=fpalette[i+2];
  }

  //get order of size of clusters
  int max_cluster=0;
  for(int i=0;i<3;i++)if(freq[i]>freq[max_cluster])max_cluster=i;
  int smallest_cluster=0;
  for(int i=0;i<3;i++)if(freq[i]<freq[max_cluster])smallest_cluster=i;
  int second_cluster=0;
  for(int i=0;i<3;i++)if(i!=max_cluster && i!=smallest_cluster)second_cluster=i;
  

  std::cout<<"max cluster : "<<max_cluster<<" hue : "<<hues[max_cluster]<<std::endl;
  std::cout<<"second cluster : "<<second_cluster<<" hue : "<<hues[second_cluster]<<std::endl;
  std::cout<<"smallest cluster : "<<smallest_cluster<<" hue : "<<hues[smallest_cluster]<<std::endl;

  //ask user to pick harmony type
  int nb_colors_harmony=2;

  int rotation=10;

  if(nb_colors_harmony==1){
    std::cout<<"monochromatic harmony"<<std::endl;
    harmonize_monochromatic(max_cluster, second_cluster, smallest_cluster, hues, rotation);
  }else if(nb_colors_harmony==2){
    std::cout<<"complementary harmony"<<std::endl;
    harmonize_complementary(max_cluster, second_cluster, smallest_cluster, hues, rotation);
  }else if(nb_colors_harmony==3){
    std::cout<<"triadic harmony"<<std::endl;
    harmonize_triadic(max_cluster, second_cluster, smallest_cluster, hues, rotation);
  }else std::cout<<"you picked something else than 1,2 or 3."<<std::endl;

  std::cout<<"after : "<<std::endl;
  std::cout<<"max cluster : "<<max_cluster<<" hue : "<<hues[max_cluster]<<std::endl;
  std::cout<<"second cluster : "<<second_cluster<<" hue : "<<hues[second_cluster]<<std::endl;
  std::cout<<"smallest cluster : "<<smallest_cluster<<" hue : "<<hues[smallest_cluster]<<std::endl;

  double L,C,H;
  for(int i=0;i<3;i++){
    int r,g,b;
    fpalette[i*3+2] = hues[i];
    LCH_to_LAB(&fpalette[i*3],&fpalette[i*3+1],&fpalette[i*3+2]);
  }
}
