t = int(input())
while t > 0:
    n , k = [int(i) for i in input().split()]
    if n % (k * k) == 0:
        print("NO")
    else:
        print("YES")
    t -= 1