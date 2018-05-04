import datetime, calendar, sys
month_list = list(calendar.month_name)
for line in sys.stdin:
    (day, month_name, year) = line.split()
    #print(day, month_name, year)
    print(calendar.day_name[datetime.date(int(year), month_list.index(month_name), int(day)).weekday()])
