#include <map>
#include <iostream>
#include <curl.h>

#define INF 1000000000
int main(int argc, char **argv)
{
	CURL *curl;
    CURLcode res;
    curl = curl_easy_init ();
    if (curl)
    {
       curl_easy_setopt (curl, CURLOPT_URL, "http://example.com");
       res = curl_easy_perform (curl);
       curl_easy_cleanup (curl);
    }
    std::map<int, int> m;
	numSubImages = 50;
	subImages[numSubImages][100][100];
	minLength = INF;
	for(i=0;i<numSubImages;i++){
		//TODO: Resolve size(i)
		if(size(i)<minLength){
			minLength = size(i)
		}
	}
	lineNumber[numSubImages];
	hashSubImages[numSubImages];
}