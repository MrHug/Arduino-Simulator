#!/usr/bin/python

inputName = "tasks.ino"
outputName = inputName.replace(".ino", ".c")

with (open(inputName, 'r')) as inputFile:
	with (open(outputName, 'w+')) as outputFile:
		inputString = inputFile.read()
		inputString = inputString.replace("Serial", "//Serial")
		inputString = inputString.replace("pinMode", "//pinMode")
		inputString = inputString.replace("digitalWrite", "//digitalWrite")
		inputString = inputString.replace("pulseIn", "//pulseIn")
		inputString = inputString.replace("delay", "//delay")

#		print outputString
		outputFile.write(outputString)

print "done with conversion"
