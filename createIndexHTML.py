import os
import shutil
import time

def main():
  	print('I love you Gracie <3')
	createFile()

def createIndexFile():

	# Get the current location that the program is running in
	# Program should use absolute paths to be compatible with other systems
	cwd = os.getcwd()
	print "CWD: %s\r\n" % (cwd)

	# List all the files in the directory
	files = os.listdir(".")
	print (files)

def createFile():

	f = open("index.html", "w")

	file = """<!doctype html>

<html lang="en">

<head>

	<meta charset="utf-8">

	<meta name="viewport" content="width=device-width, initial-scale=1.0">

	<meta name="author" content="Warren Chemerika">

	<meta name="description" content="">

	<title></title>

</head>

<body>

	<header>
		<nav>
			<ul>
				<li>
					<a href=""></a>
				</li>
			</ul>
		</nav>
	</header>

	<main>

		<header>
			
			<h1>This is the real title</h1>

		</header>

	</main>

</body>

</html>
"""

	f.write(file)

	f.close()



if __name__ == '__main__':
  main()
