x=int(input())
f=x*20
prime = []
for i in range(f):
    prime.append(1)
prime[0] = prime[1] = 0
ans = []
for i in range(2, f):
    if (prime[i] == 1):
        ans.append(i)
        for j in range(2 * i, f,i):
            prime[j] = 0
print(*prime)