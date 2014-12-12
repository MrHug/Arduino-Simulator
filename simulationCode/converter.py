#!/usr/bin/python

inputName = "logic.ino"
outputName = inputName.replace(".ino", ".c")

with (open(inputName, 'r')) as inputFile:
	with (open(outputName, 'w+')) as outputFile:
		inputString = inputFile.read()
		inputString = inputString.replace("Serial", "//Serial")
		inputString = inputString.replace("pinMode", "//pinMode")
		inputString = inputString.replace("digitalWrite", "//digitalWrite")
		inputString = inputString.replace("pulseIn", "//pulseIn")
		outputString = '#include "logic.h"\n'+ inputString + """\n void main() { 
			setup();
			while(1) { usleep(100000); loop();}
		}"""

#		print outputString
		outputFile.write(outputString)

print "done with conversion"
