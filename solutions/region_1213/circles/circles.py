import random, math

EPS = 1.0e-7

def sqr(x):
    return x * x

class Point:
    def __init__(self, _x, _y):
        self.x = _x
        self.y = _y
    def distTo(self, another):
        return math.sqrt(sqr(self.x - another.x) + sqr(self.y - another.y))
    def onCircle(self, center, R):
        return abs(self.distTo(center) - R) < EPS

class Line:
    def __init__(self, _a, _b, _c):
        self.a = _a
        self.b = _b
        self.c = _c
    def parallel(self, another):
        return abs(self.a * another.b - self.b * another.a) < EPS
    def intersect(self, another):
        y = (another.c * self.a - self.c * another.a) / (self.b * another.a - another.b * self.a)
        x = (another.c * self.b - self.c * another.b) / (self.a * another.b - another.a * self.b)
        return Point(x, y)

def pointsToLine(firstP, secondP):
        a = secondP.y - firstP.y
        b = firstP.x - secondP.x
        c = -firstP.x * a - firstP.y * b
        return Line(a, b, c)
def orthagonal(line, firstP, secondP):
        middleP = Point((firstP.x + secondP.x) / 2, (firstP.y + secondP.y) / 2)
        a = -line.b
        b = line.a
        c = -a * middleP.x - b * middleP.y
        return Line(a, b, c)

def findCenter(firstP, secondP, thirdP):
    L1 = pointsToLine(firstP, secondP)
    L2 = pointsToLine(secondP, thirdP)
    if L1.parallel(L2):
        return (False, -1, Point(0, 0))
    L3 = orthagonal(L1, firstP, secondP)
    L4 = orthagonal(L2, secondP, thirdP)
    O = L3.intersect(L4)
    R = O.distTo(firstP)
    return (True, R, O)

n = int(input())
a = []
for i in range(n):
    (x, y) = (int(c) for c in input().split())
    a.append(Point(x, y))
if n <= 4:
    print("1 2")
    print(str(n) + " " + str(n - 1))
    exit(0)
while True:
    first = random.randint(0, n - 3)
    second = random.randint(first + 1, n - 2)
    third = random.randint(second + 1, n - 1)
    #first = 0
    #second = 1
    #third = 2
    (result, R1, O1) = findCenter(a[first], a[second], a[third])
    #print("center" + str(O1.x) + " " + str(O1.y) + " radious " + str(R1))
    if not result:
        continue
    lst1 = []
    lst2 = []
    for j in range(n):
        if a[j].onCircle(O1, R1):
            lst1.append(j)
        else:
            lst2.append(j)
    '''print("lst1")
    print(lst1)
    print("lst2")
    print(lst2)'''
    fail = False
    if len(lst2) > 2:
        (result, R2, O2) = findCenter(a[lst2[0]], a[lst2[1]], a[lst2[2]])
        #print("center" + str(O2.x) + " " + str(O2.y) + " radious " + str(R2))
        if not result:
            fail = True
        else:
            for j in range(3, len(lst2)):
                if not a[lst2[j]].onCircle(O2, R2):
                    fail = True
        lst2 = []
        for j in range(n):
            if a[j].onCircle(O2, R2):
                lst2.append(j)
    if fail:
        continue
    for j in range(len(lst1)):
        print(lst1[j] + 1, end = ' ')
    print()
    for j in range(len(lst2)):
        print(lst2[j] + 1, end = ' ')
    exit(0)



