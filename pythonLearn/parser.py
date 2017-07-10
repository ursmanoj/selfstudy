#!/usr/bin/python

# init data
STATE_SCENE_NONE = 0
STATE_SCENE_STARTED = 1
STATE_SCENE_TRACE1 = 2
STATE_SCENE_TRACE2 = 3

#Open log file
#open csv output file
logFile = open('testfile.txt', 'r')
csvOutFile = open('output.csv', 'w')
state = STATE_SCENE_NONE
# loop start
while 1==1:
	
	# read line until string 'Scene started' found
	line = logFile.readline()
	if line.count("end") > 0:
		break

	if line.count("Scene started") > 0 and state == STATE_SCENE_NONE:
		state = STATE_SCENE_STARTED
		#scene touple found, now look for timestamp
		ts_index = line.index("ts:") + 3
		#ts = line.split(line.at(ts_index, " ")
		ts_big = line[ts_index:]
		ts = ts_big.split(" ")
		print ts[0]
		csvOutFile.write(ts[0])
		csvOutFile.write(',')

	if line.count("trace1") > 0 and state == STATE_SCENE_STARTED:
		state = STATE_SCENE_TRACE1
		#scene touple found, now look for timestamp
		ts_index = line.index("ts:") + 3
		#ts = line.split(line.at(ts_index, " ")
		ts_big = line[ts_index:]
		ts = ts_big.split(" ")
		print ts[0]
		csvOutFile.write(ts[0])
		csvOutFile.write(',')

	if line.count("trace2") > 0 and state == STATE_SCENE_TRACE1:
		state = STATE_SCENE_NONE
		#scene touple found, now look for timestamp
		ts_index = line.index("ts:") + 3
		#ts = line.split(line.at(ts_index, " ")
		ts_big = line[ts_index:]
		ts = ts_big.split(" ")
		print ts[0]
		csvOutFile.write(ts[0])
		csvOutFile.write('\n')
	#print(line)


# save timestamp in list
#  a touple found
# read line until string 'trace1' & save timestamp2
# read line until string 'trace2' & save timestamp3
# save timestamp triple into csv file in csv format
csvOutFile.close()
logFile.close()
