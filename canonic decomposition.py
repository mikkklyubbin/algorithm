x=int(input())
ans=[]
i=2
a=x
while i*i<=x:
    while a%i==0:
        ans.append(i)
        a//=i
    i+=1
if a!=1:
    ans.append(a)
print(*ans)