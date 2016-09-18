#include <map>
#include <iostream>
#include <stdlib.h>
#include <string>
#include <Magick++.h>
#include "main.h"
#define INF 1000000000

using namespace std;
using namespace Magick;


int numSubImages = 29;
int* lineNumber;//[numSubImages];
int*** subImages;//[numSubImages][100][100];
int** dimSub;//[numSubImages][2];
map<int, int> hashSubImages;
int main(int argc, char **argv)
{	
	
	InitializeMagick(*argv);
	lineNumber = new int[numSubImages];
	subImages = new int**[numSubImages];
	string* imageNamesTarget = new string[numSubImages]{"targets/177193_orig.jpg","targets/1899165_orig.jpg","targets/2424954_orig.jpg","targets/3070528_orig.jpg","targets/3200588_orig.jpg","targets/3246675_orig.jpg","targets/3276680_orig.jpg","targets/4532418_orig.jpg","targets/5168782_orig.jpg","targets/5215015_orig.jpg","targets/6244913_orig.jpg","targets/7344429_orig.jpg","targets/7543724_orig.jpg","targets/7702229_orig.jpg","targets/7915429_orig.jpg","targets/7925109_orig (1).jpg","targets/7925109_orig.jpg","targets/8301660_orig.jpg","targets/9024148_orig.jpg","targets/9797938_orig.jpg","targets/Ebner-LTRs-1943-04-27-to-Mom-1-Version-2-e1371745673560.jpg","targets/Letter-to-TFI-500x646.jpg","targets/Letters-to-Home-2history-500x655.jpg","targets/RC2b1f11 salvage 1.jpg","targets/Thumbs.db","targets/firstimage.jpg","targets/g1941Jul00A.jpg","targets/uaa-hmc-0814-p1.jpg","targets/wwiilett.jpg"};
	string* imageNameSources = new string[numSubImages]{"source/177193_orig.jpg","source/1899165_orig.jpg","source/2424954_orig.jpg","source/3070528_orig.jpg","source/3200588_orig.jpg","source/3246675_orig.jpg","source/3276680_orig.jpg","source/4532418_orig.jpg","source/5168782_orig.jpg","source/5215015_orig.jpg","source/6244913_orig.jpg","source/7344429_orig.jpg","source/7543724_orig.jpg","source/7702229_orig.jpg","source/7915429_orig.jpg","source/7925109_orig (1).jpg","source/7925109_orig.jpg","source/8301660_orig.jpg","source/9024148_orig.jpg","source/9797938_orig.jpg","source/Ebner-LTRs-1943-04-27-to-Mom-1-Version-2-e1371745673560.jpg","source/Letter-to-TFI-500x646.jpg","source/Letters-to-Home-2history-500x655.jpg","source/RC2b1f11 salvage 1.jpg","source/Thumbs.db","source/firstimage.jpg","source/g1941Jul00A.jpg","source/uaa-hmc-0814-p1.jpg","source/wwiilett.jpg"};
	for(int i = 0;i<numSubImages;i++){
		Image image;
		image.read(imageNamesTarget[i]);
		int w = (int) image.columns();
		int h = (int) image.rows();
		dimSub[i] = new int[2]{w,h};
		subImages[i] = new int*[h];
		for(int j = 0;j<w;j++){
			subImages[i][j] = new int[w];
		}
		Magick::PixelPacket *pixels = image.getPixels(0, 0, w, h);
		for(int j=0;j<h;j++){
			for(int k=0;k<w;k++){
				Magick::Color color = pixels[w*j+k];
				cout << color.redQuantum() << endl;
				//subImages[i][j][k] = color.redQuantum()<<16+color.greenQuantum()<<8+color.blueQuantum();
			}
		}
		Pixels view(image);
	}
	dimSub = new int*[numSubImages];
	
	for(int i = 0;i<numSubImages;i++){
		dimSub[i] = new int[2];
	}
	
	for(int i = 0;i<numSubImages;i++){
		dimSub[i][0]=100;
		dimSub[i][1]=100;
	}
	
	for(int i = 0;i<numSubImages;i++){
		for(int j = 0;j<100;j++){
			for(int k=0;k<100;k++){
				subImages[i][j][k]=100*rand();
			}
		}
	}
	int minLength = INF;
	for(int i=0;i<numSubImages;i++){
		//TODO: Resolve size(i)
		if(dimSub[i][0]<minLength){//Replace size(i)
			minLength = dimSub[i][0];//size(i)
		}
	}
	//TODO: Test difference between unordered map and ordered, or even array
	//Generate hash table
	for(int i =0; i<numSubImages; i++){
		int rowSize = dimSub[i][0];
		int middle = rowSize/2;
		for(int j=0;j<rowSize;j++){
			//Start at the middle until a row without collision is reached
			int hash = findHash(subImages[i][(middle+j)%rowSize], minLength);
			if(!hashSubImages.count(hash)){
				//If the row isn't a collision, add it
				hashSubImages[hash] = i;
				lineNumber[i]=(middle+j)%rowSize;
				break;
			}
			if(j==rowSize-1){
				//Fucks it
				return -1;
			}
		}
	}
	int numLargeImages = 10;
	for(int i=0;i<numLargeImages; i++){
		int width = 1000;
		int height = 1000;
		int** data = new int*[height];//[height][width];	
		for(int i = 0;i<height;i++){
			data[i] = new int[width]();
		}
		
		int val = -1;
		int tempVal = -1;
		
		for(int j = 0;j<height;j++){
			int start = findHash(data[j],minLength);
			if((tempVal = checkStart(data, i,j, start))!=-1){
				val = tempVal;
				break;
			}
			for(int k=1;k<width-minLength;k++){
				start-=data[j][k-1];
				start+=data[j][k+minLength];
				if((tempVal = checkStart(data, i,j, start))!=-1){
					val = tempVal;
					break;
				}
			}
			if(val!=-1){
				break;
			}
		}
		if(val==-1){
			//Its fuck
			return -2;
		}
	}
	
	return 0;
}
int findHash(int* row, int size){
	int accum = 0;
	for(int i = 0;i<size;i++){
		accum += row[i];
	}
	return accum;
}
int skip = 5;
int checkStart(int** data, int x,int y, int hash){
	std::map<int,int>::iterator it = hashSubImages.find(hash);
	int pos;
	if(it == hashSubImages.end()){
		return -1;
	}
	else{
		pos = it->second;
	}
	//Check grid
	for(int i=0;i<dimSub[pos][0];i+=skip){
		for(int j=0;j<dimSub[pos][1];j+=skip){
			if(subImages[pos][i][j]!=data[x+i][y+j]){
				return -1;
			}
		}
	}
	//Check full
	for(int i=0;i<dimSub[pos][0];i++){
		for(int j=0;j<dimSub[pos][1];j++){
			if(subImages[pos][i][j]!=data[x+i][y+j]){
				return -1;
			}
		}
	}
	return pos; 
}