


f = open("masterSMSTree.list", "r")
lines = f.readlines()
MaxEntriesPerFile = 100;
entryCount = 0;
outCount = 1;
out = open("SSTreeList"+str(outCount)+".list","w+")
for line in lines:
	if entryCount > MaxEntriesPerFile:
		outCount = outCount+1
		out.close()
		out = open("SSTreeList"+str(outCount)+".list","w+")
		entryCount = 0

	out.write(str(line))
	entryCount=entryCount+1
			
