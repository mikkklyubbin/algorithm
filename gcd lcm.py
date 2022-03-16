def gcd(a,b):
    while b!=0:
        tmp=a%b
        a=b
        b=tmp
    return a
lcm=n*k/gcd(n,k)