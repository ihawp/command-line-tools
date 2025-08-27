import os
import sys
import tempfile
import shutil

def checkArguments(argv):
	
	values = {
		"file": argv[1],
		"text": argv[2],
		"writemode": 'a',
	}

	for i in range(len(argv)):
	#	match argv[i]:
	#		case "-a":
	#			values["writemode"] = argv[i + 1]
	#			i = i + 1

		if argv[i] == "-w":
			values["writemode"] = argv[i + 1]

	return values

def prepend(filename, text):
	# Prepend the new file contents to an old file
	# Call with flag -a p

	dir_name = os.path.dirname(filename)
	fd, temp_path = tempfile.mkstemp(dir=dir_name)
	
	with os.fdopen(fd, "w") as tmp:
		tmp.write(text)
		
		with open(filename, "r") as orig:
			shutil.copyfileobj(orig, tmp)

	os.replace(temp_path, filename)

def writewithmode(filename, text, writemode):

	if writemode in ('r', 'R'):
		return

	# Check for writemode being submitted as p
	if writemode == "p":
		prepend(filename, text)
		return

	if checkoverwrite(filename, writemode) == False:
		return

	# If not prepend then use the writemode submitted
	with open(filename, writemode) as f:
		f.write(text)

def checkoverwrite(filename, writemode):
	cwd = os.getcwd()
	path = os.path.join(cwd, filename)

	if (os.path.exists(path) and writemode in ('w', 'w+')):

                # Make sure the user wants to overwrite the file.
                print("Are you sure? (Y/n)");
                sure = input()

                if sure not in ('Y', 'y'):
                        return False

	return True


def main():

	# Did the caller give us any info?
	if len(sys.argv) < 1:
		return 0

	# Get the submitted 'content'
	values = checkArguments(sys.argv)

	# Do the write/append/prepend
	writewithmode(
		values["file"],
		values["text"],
		values["writemode"]
	)

if __name__ == '__main__':
	main()
