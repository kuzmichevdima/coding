import math

class Point:
    def __init__(self, x, y):
        self.x = x
        self.y = y
class Vector:
    #def __init__(self, x, y):
    #    self.x = x
    #    self.y = y
    def __init__(self, pFrom, pTo):
        self.x = pTo.x - pFrom.x
        self.y = pTo.y - pFrom.y
    def crossP(self, another):
        return self.x * another.y - self.y * another.x
    def length(self):
        return math.sqrt(self.x * self.x + self.y * self.y)

n = int(input())
p = []
for i in range(n):
    tmp = [int(x) for x in input().split()]
    p.append(Point(tmp[0], tmp[1]))
sideP = 0
for i in range(1, n):
    if p[i].y < p[sideP].y or ((p[i].y == p[sideP].y) and (p[i].x < p[sideP].x)):
        sideP = i
p[0], p[sideP] = p[sideP], p[0]
lst = []
for i in range(n):
    dx = p[i].x - p[0].x
    dy = p[i].y - p[0].y
    first = math.atan2(dy, dx)
    second = math.hypot(dx, dy)
    lst.append((first, second, p[i].x, p[i].y))
lst.sort()
#print(lst)
#exit(0)
st = []
#(t1, t2, tx, ty) = lst[0]
#st.append(Point(tx, ty))
#st.append(lst[1])
for i in range(n):
    (t1, t2, newx, newy) = lst[i]
    newp = Point(newx, newy)
    while (len(st) >= 2):
        v1 = Vector(st[-2], st[-1])
        v2 = Vector(st[-1], newp)
        crossProd = v1.crossP(v2)
        if (crossProd < 0):
            flag = True
        else:
            if (crossProd > 0):
                flag = False
            else:
                flag = (v1.length() < v2.length())
        if flag:
            st.pop()
        else:
            break
    st.append(newp)
#for p in st:
#    print(str(p.x) + " " + str(p.y))
L = len(st)
st.append(st[0])
per = 0
area = 0
zeroP = Point(0, 0)
for i in range(L):
    dx = st[i + 1].x - st[i].x
    dy = st[i + 1].y - st[i].y
    per += math.sqrt(dx * dx + dy * dy)
    v1 = Vector(zeroP, st[i])
    v2 = Vector(zeroP, st[i + 1])
    area += v1.crossP(v2)
#area = math.abs(area) / 2.0
area = abs(area) / 2.0
print(per)
print(area)

