import os
import sys
import shutil
import time
from PIL import Image

help = """

Welcome to pig (personal image generator), below you will find all the information you need to start converting your images today!

#########################################

Call "pig"...

> pig

OR

> pig --help

...to load this help page, maybe that is how you got here. 

#########################################

Arguments List:
-----------------------------------------

1. Image: Actual file in current directory. 
2. Output Name: The name of the new file to be created. 
3. Image Type: The type of image you would like the new image to be.
4. Flags: Infinite flags can be used, though they may not all work together!


Convert a File:
-----------------------------------------
I have a local file called banana.jpg.
I want to turn this image into a png called wow.png.

    filename   newname ext
___|__________|_______|___|______
pig banana.jpg wow.png png <flags>...


Flags:
-----------------------------------------
You can also add flags to your call to change specific values within the program.

Convert:		-c <String>
Select Frame:		-f <Integer>
Types:			-t | --types <>
Help:			-h | --help <>

Examples:
------------------------------------------
Convert (-c):
				convert mode
___|__________|________|____|__|___
pig banana.jpg wow.palm palm -c "P"

Select Frame (-f):
				frame
___|__________|________|____|__|_
pig banana.gif wow.jpeg jpeg -f 3

If you want to convert a gif or multi-frame image to a different image type that does not support multiple frames and don't want to use the first frame, you can select a specific frame by using -f. Note that there is no call to -c, this is because the default encoding type is "RGB" so our conversion to JPEG will work.

Types (-t):
    flag
___|_______
pig -t
pig --types

Provides a list of the various types of images you can convert your image to.

Help (-h):
    flag
___|_______
pig -h
pig --help

You are viewing help, you get it.

"""

valid_formats = Image.registered_extensions()

modes = {
        "palm": ["1", "L", "P"],
        "gif":  ["P", "L"],
        "ico":  ["1", "L", "P", "RGBA"],
        "xbm":  ["1"]
}

values = {
	"image": "",
	"outputname": "",
	"type": "",
	"convert": "RGB"
}

def printFormats():
	print("\nA list of valid image types:\n")
	for key in valid_formats:
		print(key, valid_formats[key])

def checkValidType(file_extension):

	values["type"] = file_extension.lower()

	if f".{values["type"]}" in valid_formats:
		return True

	return False

def pathDoesntExistHere(image):
	cwd = os.getcwd()
	path = os.path.join(cwd, image)

	if not os.path.exists(path):
		print("Path does not exist")
		return True

	return False

def convertFlags(argv):
	# Convert submitted flags into usable values
	for i in range(len(argv)):
		match argv[i]:
			case '-c':
				values["convert"] = argv[i + 1].upper()
			case '-f':
				values["frame"] = argv[i + 1]

def parseArgs(argv):

	# help and types: not very clean, but needs to be general incase someone does not use any arguments (other then the flag itself)

	if '--help' in argv or '-h' in argv:
		print(help)

	if '--types' in argv or '-t' in argv:
		printFormats()

	if len(argv) < 4:
		print("Insufficient arguments, try 'pig --help'")
		return False

	# The image file submitted does not exist in the current working directory
	if pathDoesntExistHere(argv[1]):
		print('\nFile does not exist, try --help.\n')
		return False

	# Map arguments to keys
	mapArgumentsToKeys(argv)

	convertFlags(argv)

def mapArgumentsToKeys(argv):
	values["image"] = argv[1]
	values["outputname"] = argv[2]
	values["type"] = argv[3]

def saveToGif():
	im = Image.open(values["image"])
	frames = [frame.convert(values["convert"]) for frame in ImageSequence.Iterator(im)]

	frames[0].save(
		values["outputname"],
		save_all = True,
		append_images = frames[1:],
		duration = im.info.get("duration", 100),
		loop = im.info.get("loop", 0)
	)

def saveFrame():
	# save a specific frame
	print('save a specific frame')

def convertImage():
	im = Image.open(values["image"]).convert(values["convert"])
	im.save(values["outputname"], values["types"])

def main():

	if not parseArgs(sys.argv):
		return

	if not checkValidType(values["type"]):
		return

	# Convert multi-frame image to gif is specialist case (so far)
	if values["type"].lower() == 'gif':
		saveToGif()
		return

	convertImage()

if __name__ == '__main__':
	main()
