import re
f = open('whodata.txt', 'r')
for line in f:
    print(re.findall(r'(\w+)\s+([\w/]+)\s+(\d{4}-\d{2}-\d{2} \d{2}:\d{2}) (.*)', line.rstrip()))
f.close()
