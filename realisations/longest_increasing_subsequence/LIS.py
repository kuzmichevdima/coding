

def main():
    (n, a1, k, b, m) = (int(x) for x in raw_input().split())
    a = [-1]
    a.append(a1)
    for i in range(2, n + 1):
        a.append((a[-1] * k + b) % m)
    #print(a)
    inf = 1e9
    d = [inf] * (n + 1)
    d[0] = -inf
    answer = 0

    def get(x):
        start = 0
        finish = n
        while(start < finish):
            middle = (start + finish) // 2 + 1
            if (d[middle] < x):
                start = middle
            else:
                finish = middle - 1
        return start

    for i in range(1, n + 1):
        start = get(a[i])
        #print("start = " + str(start))
        if d[start + 1] == inf:
            answer += 1
        d[start + 1] = a[i]
        #print(d[start + 1])
    print(answer)
main()