m=9e+7
n=29
def hash(s):
    cur_p=1
    h=0
    pref_hesh = [0 for i in range(len(s))]
    nn=[0 for i in range(len(s))]
    for i in range(0,len(s)):
        h=(h+(ord(s[i])-96)*cur_p%m)%m
        pref_hesh[i]=int(h)
        nn[i]=int(cur_p)
        cur_p=(cur_p*n)%m
    return pref_hesh,nn
def harshstd(l,r,pref_hesh,lp,nn):
    if l!=0:
        return (pref_hesh[r]-max((pref_hesh[l-1]+m),0))%m*nn[lp-l-1]%m
    else:
        return (pref_hesh[r] - 0) % m * nn[lp - l - 1] % m

a=input()
rph,mm=hash(a)
lp=len(a)
b=input()
rr,mn=hash(b)
q=(rr[-1]*mm[-1])%m
f=len(b)
for i in range(0,lp-f+1):
    bbb=harshstd(i,i+f-1,rph,lp,mm)
    if bbb==q:
        print(i,end=" ")


