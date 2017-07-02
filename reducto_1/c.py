i=7
x=0
for c in input():
 x+=int(c)*2**i;i=(i+7)%8
 if i==7:
  print(chr(x),end='');x=0
