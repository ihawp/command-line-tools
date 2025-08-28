import os
import sys
import shutil
import time
from PIL import Image

help = """

Missing arguments.

Arguments:
1. Image: Actual file in current directory.
2. Output Name: The name of the new file to be created.
3. Image Type: The type of image you would like the new image to be.

Example:

I have a local file called banana.jpg. I want to turn this image into a png called wow.png. The example below displays how to do that.

python3 script.py banana.jpg wow.png png

NOTE: Errors will be thrown for incorrect image types submitted, ensure you know the proper extension for your desired result. This is a simple implementation of the PIL library.

"""

def checkValidType(file_extension):
	valid_formats = Image.registered_extensions()

	formatted = file_extension.lower()

	if f".{formatted}" in valid_formats:
		return True

	print('\nValid Formats:')
	for key in valid_formats:
		print(key, valid_formats[key])

	return False


def main():
	if len(sys.argv) < 4 or '--help' in sys.argv:
		print(help)
		return

	image = sys.argv[1]
	outputname = sys.argv[2]
	type = sys.argv[3]

	if not checkValidType(type):
		print(help)
		print('Error: Type submitted is not possible, change argument 3 to a proper image file extension.\n')
		return

	im = Image.open(image).convert("RGB")
	im.save(outputname, type)

if __name__ == '__main__':
	main()

