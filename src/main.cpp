#include <map>
#include <iostream>
#include <stdlib.h>
#include "main.h"
#define INF 1000000000

int numSubImages = 50;
int* lineNumber;//[numSubImages];
int*** subImages;//[numSubImages][100][100];
int** dimSub;//[numSubImages][2];
std::map<int, int> hashSubImages;

int main(int argc, char **argv)
{	
	lineNumber = new int[numSubImages];
	subImages = new int**[numSubImages];
	for(int i = 0;i<numSubImages;i++){
		subImages[i] = new int*[100];
		for(int j = 0;j<100;j++){
			subImages[i][j] = new int[100]();
		}
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