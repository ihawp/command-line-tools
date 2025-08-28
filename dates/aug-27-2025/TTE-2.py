import os
import sys
import tempfile
import shutil

def checkArguments(argv):

	if len(argv) < 3 or 0 in (len(argv[1]), len(argv[2])):
		print('Missing arguments.')
		return False

	# Writemode starts as 'a' (append) for safety :)
	values = {
		"file": argv[1],
		"text": argv[2],
		"writemode": 'a',
	}

	for i in range(len(argv)):
		match argv[i]:
			case "-w":
				values["writemode"] = argv[i + 1]
			case "-csvrow":
				values["text"] = values["text"].replace(argv[i + 1], ",")
				print('fuck yeah you found it')
			case "-g":
				print("even better")
	return values

def prepend(filename, text):
	# Prepend the new file contents to an old file
	# Call with flag -a p

	dir_name = os.path.dirname(filename)
        
	cwd = os.getcwd()
	path = os.path.join(cwd, filename)
	
	if not os.path.exists(path):
		print('File must exist to prepend')
		return False

	fd, temp_path = tempfile.mkstemp(dir=dir_name)

	with os.fdopen(fd, "w") as tmp:
		tmp.write(text)
		
		with open(filename, "r") as orig:
			shutil.copyfileobj(orig, tmp)

	os.replace(temp_path, filename)

def writewithmode(values):

	filename = values["file"]
	text = values["text"]
	writemode = values["writemode"]

	match writemode:
		case "r" | "R":
			print("This is not a book.\n")
			return
		case "p" | "P":
			prepend(filename, text)
			return
		case "a" | "A":
			values["text"] = "\n" + values["text"]
	
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

	# Get the submitted 'content'
	values = checkArguments(sys.argv)

	if values == False:
		print("Check arguments failed.\n")
		exit()

	# Do the write/append/prepend
	writewithmode(values)

if  __name__ == '__main__':
	main()
