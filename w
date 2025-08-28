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

def main():

	if len(sys.argv) < 4 or '--help' in sys.argv:
		print(help)
		return

	image = sys.argv[1]
	outputname = sys.argv[2]
	type = sys.argv[3]


	im = Image.open(image).convert("RGB")
	im.save(outputname, type)

if __name__ == '__main__':
	main()

