import os
import sys
import shutil
import time
from PIL import Image

help = """

Missing arguments.

Arguments List:

1. Image: Actual file in current directory.
2. Output Name: The name of the new file to be created.
3. Image Type: The type of image you would like the new image to be.

Example:

I have a local file called banana.jpg. I want to turn this image into a png called wow.png. The example below displays how to do that.

pig banana.jpg wow.png png

NOTE: Errors will be thrown for incorrect image types submitted, ensure you know the proper extension for your desired result. This is a simple implementation of the PIL library.

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

def printHelp():
	print("\nA list of valid image types:\n")
	for key in valid_formats:
		print(key, valid_formats[key])

	print(help)

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
                                # convert flag
                                values["convert"] = argv[i + 1].upper()

def parseArgs(argv):

	# Not enough arguments to function
	# OR help requested
	if len(argv) < 4 or '--help' in argv:
		printHelp()
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

def main():

	parseArgs(sys.argv)

	if not checkValidType(values["type"]):
		printHelp()
		return

	im = Image.open(values["image"]).convert(values["convert"])
	im.save(values["outputname"], values["type"])

if __name__ == '__main__':
	main()
