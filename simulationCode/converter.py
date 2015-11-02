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
		inputString = inputString.replace("delay", "//delay")
		outputString = '#include "logic.h"\n'+ inputString + """\n int main() { 
			setup();
			while(1) { usleep(100000); loop();}
			return 1;
		}"""

#		print outputString
		outputFile.write(outputString)

print "done with conversion"
