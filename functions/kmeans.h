#ifndef KMEANS_H
#define KMEANS_H

#define intmax pow(2, 16)


int euclid_dist(unsigned char *Im, unsigned char *centroids, int indexIm, int indexCt){
	int res = 0;
	for(int i=0;i<3;i++){
		res+=(int)(Im[indexIm+i]-centroids[indexCt+i])*(Im[indexIm+i]-centroids[indexCt+i]);
	}
	return res;
}

void set_mean_centroids(unsigned char *centroids, unsigned char *img, int *labels, int Imside, int k){
	//compute totals
	int means[3*k];
	for(int i=0;i<3*k;i++)means[i]=0;

	for(int i=0;i<Imside*3;i+=3){
		int whichCluster = 3*labels[i/3];
		for(int j=0;j<3;j++){
			means[whichCluster+j]+=img[i+j];
		}
	}


	//normalize the means (divide the color by size of cluster)
	int clusterSizes[k];
	for(int i=0;i<k;i++)clusterSizes[i]=0;
	for(int i=0;i<Imside;i++)
		clusterSizes[labels[i]]++;

	for(int i=0;i<k*3;i+=3){
		int current_cluster_size = clusterSizes[i/3];
		for(int j=0;j<3;j++){
			if (current_cluster_size>0)
				means[i+j]/=current_cluster_size;
		}
	}

	//input the new colors into the centroids array
	for(int i=0;i<k*3;i+=3){
        centroids[i]=(unsigned char)means[i];
        centroids[i+1]=(unsigned char)means[i+1];
        centroids[i+2]=(unsigned char)means[i+2];
	}
}

void assign_pixels_to_clusters(int *labels, unsigned char *centroids, unsigned char *img, int Imsize, int k){
	for(int i=0;i<3*Imsize;i+=3){
		int mindist = intmax;
		int minCentroid;
		for(int j=0;j<k;j++){
			int centroidDist = euclid_dist(img, centroids, i, j*3);
			if(centroidDist<mindist){
				mindist=centroidDist;
				minCentroid=j;
			}
		}
		labels[i/3]=minCentroid;
	}
}

void assign_cluster_colors(unsigned char *Im, unsigned char *colors, int *labels, int size, int k){
	for(int i=0;i<size;i++){
		int cluster = labels[i];
		Im[i*3]=colors[3*cluster];
		Im[i*3+1]=colors[3*cluster+1];
		Im[i*3+2]=colors[3*cluster+2];
	}
}

void kmeans(unsigned char *Im, unsigned char *centroids, int *freq, int sizeimg){
	int *labels = new int[sizeimg];
	//fait 20 itÃ©rations par dÃ©faut. Voir s'il faut paramÃ©trer
	int nbIt = 0;
	while(nbIt++<20){
		assign_pixels_to_clusters(labels, centroids, Im, sizeimg, 3);

		set_mean_centroids(centroids, Im, labels, sizeimg, 3);
	}
	freq[0]=freq[1]=freq[2]=0;
	for(int i=0;i<sizeimg;i++){
		freq[labels[i]]++;
	}
	delete(labels);
}

#endif
