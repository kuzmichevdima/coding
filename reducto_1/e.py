d=1
m=1
while m<13:
 x=30 if m%2 else 31
 print('{}.{}.2017'.format(d,m));d+=7;
 if d>x:
  d-=x
  m+=1
