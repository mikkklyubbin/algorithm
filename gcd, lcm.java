package com.company;
import java.util.Scanner;
public class Main {
    public static int gcd(int a, int b) {
        int tmp;
        while(b!=0){
            tmp=a%b;
            a=b;
            b=tmp;

        }
        return a;
    }
    public static int lcm(int a, int b) {
        int f=gcd(a,b);
        return a*b/f;
    }
    public static void main(String[] args) {
        System.out.println(gcd(20,30));
        System.out.println(lcm(20,30));
    }
}