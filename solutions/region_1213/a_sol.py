a = int(input())
first_ans = a // 6
if (a % 6) != 0:
	first_ans += 7 - a % 6
print(first_ans, end = ' ')
print(a * 6)