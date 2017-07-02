import datetime
d=datetime.date(2017,1,1)
while d.year<2018:
 print(d)
 d+=datetime.timedelta(7)
