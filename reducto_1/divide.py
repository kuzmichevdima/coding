for i in range(1,999):
 x=i
 w=[0]
 while x:
  d=x%10;
  if d in w or i%d:
   break
  w+=[d];x//=10
 if x<1:
  print(i,end=' ')
