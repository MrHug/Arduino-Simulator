inputName = "logic.ino"
outputName = inputName.replace(".ino", ".cpp")

with (open(inputName, 'r')) as inputFile:
	with (open(outputName, 'w+')) as outputFile:
		inputString = inputFile.read()
		outputString = '#include "logic.h"\n'+ inputString + """\n void main() { 
			setup();
			while(1) { loop();}
		}"""

		print outputString
		outputFile.write(outputString)

print "done"
