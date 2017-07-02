n=int(input());x=0
for k in range(n):
 x+=2**k
 for j in range(n-k):
  print(x*2**j,end=' ')
