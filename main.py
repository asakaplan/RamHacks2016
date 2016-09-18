import numpy as np
import argparse
import imutils
import glob
import cv2
import os
import urllib2
import urllib
import re
import requests
import json
 




mainUrl = "https://s3.amazonaws.com/elephant-ramhacks-dev/"
postUrl = "https://ramhacks-2016.herokuapp.com/certifies"
response = urllib2.urlopen(mainUrl)
html = response.read()
root = [a for a in re.findall("<Key>(.*?)<", html)]
outputDict = {}
for i in range(len(root)-1,-1,-1):
	if root[i].endswith("/"):
		root.pop(i)





for element in root:
	target_folder, ignore = element.split("/",1)

	if not os.path.exists(target_folder):
		os.makedirs(target_folder)
	urllib.urlretrieve(mainUrl+element, element)







listOfFiles = [filename for filename in os.listdir('source') if filename.endswith('jpg')]
listOfTemplateFiles = [filename for filename in os.listdir('targets') if filename.endswith('png')]
maxFileName = ""
maxNum = 0
maxFileIndex = 0

smallImages = [cv2.imread("targets/" + filename) for filename in listOfTemplateFiles]
smallImages = map(lambda a: cv2.cvtColor(a, cv2.COLOR_BGR2GRAY), smallImages)
smallImages = map(lambda a: cv2.Canny(a, 50, 200), smallImages)


for mainImgName in  listOfFiles:
	mainImg = cv2.imread("source/" + mainImgName)
	mainImg = cv2.cvtColor(mainImg, cv2.COLOR_BGR2GRAY)
	mainImg = cv2.Canny(mainImg, 50, 200)

	for i in range(len(smallImages)):
		result = cv2.matchTemplate(mainImg, smallImages[i], cv2.TM_CCOEFF)
		(_, maxVal, _, maxLoc) = cv2.minMaxLoc(result)
		if(maxVal > maxNum):
			maxNum = maxVal
			maxFileName = listOfTemplateFiles[i]
			maxFileIndex = i
	smallImages.pop(maxFileIndex)
	print listOfTemplateFiles[maxFileIndex] + " is a subimage of " + mainImgName
	outputDict[listOfTemplateFiles[maxFileIndex][:listOfTemplateFiles[maxFileIndex].find(".")]] = mainImgName[:mainImgName.find(".")]
	listOfTemplateFiles.pop(maxFileIndex)
	maxNum = 0
	maxFileIndex = 0

print outputDict

payload = {	'env': 'dev',
			'answers': outputDict}
headers = {'Content-Type': 'application/json'}

response = requests.post(postUrl, data=json.dumps(payload), headers=headers)

for element in response:
	print element




