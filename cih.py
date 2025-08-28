import os
import shutil
import time
import sys

PYfile = """def main():
	print('it works')

if __name__ == '__main__':
	main()

"""

HTMLfile = """<!doctype html>

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


def main():
	if len(sys.argv) < 1:
		exit()

	name = sys.argv[1]
	type = sys.argv[2]

	if type in ('html', 'HTML'):
		createHTMLFile()

	elif type in ('py', 'PY'):
		createPYFile()

	# print('I love you Gracie <3')

def createHTMLFile():
	with open('index.html', 'w') as f:
		f.write(HTMLfile)


def createPYFile():
	with open('main.py', 'w') as f:
		f.write(PYfile)



if __name__ == '__main__':
  main()
