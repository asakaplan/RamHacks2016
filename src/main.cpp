#include <map>
#include <iostream>
#include <curl/curl.h>

#define INF 1000000000
int main(int argc, char **argv)
{
	int numSubImages = 50;
	int subImages[numSubImages][100][100];
	int minLength = INF;
	for(int i=0;i<numSubImages;i++){
		//TODO: Resolve size(i)
		if(size(i)<minLength){
			minLength = size(i)
		}
	}
	int lineNumber[numSubImages];
	//TODO: Test difference between unordered map and ordered
	std::map<int, int> hashSubImages;
	for(int i =0; i<numSubImages; i++){
		int rowSize = sizeRows(i);
		int middle = rowSize/2;
		for(int j=0;j<rowSize;j++){
			int hash = findHash(subImages[i][(middle+j)%rowSize], minLength);
			if(m.find(hash)==m.end()){
				map[hash] = i;
				break;
			}
			if(j==rowSize-1){
				//Fucks it
				return -1;
			}
		}
	}
}
int findHash(int[] row, int size){
	int accum = 0;
	for(int i = 0;i<size;i++){
		accum += row[i];
	}
	return accum;
}