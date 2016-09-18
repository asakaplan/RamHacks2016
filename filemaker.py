from PIL import Image
from random import random
import os
files = [f for f in os.listdir('source/') if os.path.isfile("source/"+f)]
print(files)
outText = open("elephant.txt",'w')
if not os.path.exists("targets/"):
    os.makedirs("targets/")
for f in files:
	if not ".jpg" in f:continue
	width = 80 + int(random()*80)
	height = 80 + int(random()*80)
	
	im = Image.open("source/"+f)
	im2 = Image.new("RGB", im.size, (255,255,255))
	im2.paste(im)
	imWidth, imHeight = im2.size
	x = 0#int(random()*(imWidth-width))
	y = 0#int(random()*(imHeight-height))
	
	img2 = im2.crop((x,y,x+width, y+width))
	img2.save("targets/" + f[:-3] + "png" , 'PNG')
	outText.write("targets/" + f[:-3] + "png" + "\n")
		