import re
f = open('gendata.txt', 'r')
p = '^(\w{3}) (\w{3}).*:(\d+-\d+-\d+)'
for line in f:
    print(re.match(p, line).groups())
