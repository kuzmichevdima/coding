T = int(input())
eps = 1.0 / 120
for test in range(T):
    need = float(input())
    for hours in range(12):
        for minutes in range(60):
            A = hours * 30 + (minutes / 60) * 30
            B = minutes * 6
            if abs(abs(A - B) - need) < eps or abs(abs(A - B + 360) - need) < eps or abs(abs(A - B - 360) - need) < eps:
                h1 = hours // 10
                h2 = hours % 10
                m1 = minutes // 10
                m2 = minutes % 10
                print(h1, h2, ":", m1, m2, sep = '')
