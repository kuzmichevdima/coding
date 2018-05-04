import sys, random

args = sys.argv

n = int(args[1])
m = int(args[2])
con = int(args[3])
print(str(n) + " " + str(m))
start = []
for i in range(n):
    start.append(random.randint(0, con))
for elem in start:
    print(elem, end = ' ')
print()
for i in range(m):
    typ = random.randint(1, 2)
    if typ == 1:
        pos = random.randint(1, n)
        newVal = random.randint(0, con)
        print("1 " + str(pos) + " " + str(newVal))
    else:
        s = random.randint(1, n)
        f = random.randint(s, n)
        print("2 " + str(s) + " " + str(f))
