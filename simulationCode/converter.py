#!/usr/bin/python

inputName = "tasks.ino"
outputName = inputName.replace(".ino", ".c")

with (open(inputName, 'r')) as inputFile:
	with (open(outputName, 'w+')) as outputFile:
		inputString = inputFile.read()
		inputString = inputString.replace("Serial", "//Serial")
		inputString = inputString.replace("pinMode", "//pinMode")
		inputString = inputString.replace("digitalWrite", "//digitalWrite")
		inputString = inputString.replace("analogWrite", "//digitalWrite")
		inputString = inputString.replace("pulseIn", "//pulseIn")
#		inputString = inputString.replace("delay", "//delay")
		outputString = inputString
#		print outputString
		outputFile.write('#include "logic.h"\n')
		outputFile.write(outputString)

print "done with conversion"
