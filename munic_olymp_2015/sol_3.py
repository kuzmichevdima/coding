def main():
    n = int(input())
    a = list(map(int, input().split()))
    answer = []
    for start in range(n):
        dict = {}
        last = n
        for j in range(start, n):
            if a[j] in dict:
                last = j
                break
            else:
                dict[a[j]] = True
        if last - start > len(answer):
            answer = a[start : last]
    print(len(answer))
    for x in answer:
        print(x, end = " ")
main()
            
