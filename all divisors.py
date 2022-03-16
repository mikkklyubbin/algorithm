x=int(input())
ans=[]
ans2=[]
i=1
while (i*i<abs(x)):
    if x%i==0:
        ans.append(i)
        ans.append(x//i)
    i+=1
if i*i==abs(x):
    ans.append(i)
for el in ans:
    ans2.append(-el)
for ell in ans2:
    ans.append(ell)
ans=sorted(ans)
print(*ans)