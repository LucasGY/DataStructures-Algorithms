/*
f = a0 + a1*x + a2*x^2 + an*x^n
*/
#include<math.h>
#include<time.h>
#include<stdio.h>

clock_t start, stop; //clock函数返回的数据类型
double duration; //记录函数的运行时间，以秒为单位
#define MAXN 10 //多项式n的值，即多项式阶数+1
#define MAXK 1e7 //被测函数最大调用次数
double f1(int n, double a[], double x);
double f2(int n, double a[], double x);

/*
f = a0 + a1*x + a2*x^2 + an*x^n
*/
double f1(int n, double a[], double x)
{
    int i;
    double p = a[0];
    for(i=1; i<=n; i++)
        p += a[i] * pow(x, n);
    return p;
}
/*
f = a0 + x*(a1 + x*(a2 + ... x*(an-1 + x*(an))))
*/
double f2(int n, double a[], double x)
{
    int i;
    double p = a[n];
    for(i=n; i>0; i--)
        p = a[n-1] + x*p;
    return p;
}

int main()
{
    int i;
    double a[MAXN];
    for(i=0; i<MAXN; i++)
        a[i] = (double)i;
    start = clock();
    for(i=0; i<=MAXK; i++)
        f1(MAXN-1, a, 1.1);
    stop = clock();
    duration = ((double)(stop - start))/CLOCKS_PER_SEC/MAXK;
    printf("f1 duration = %6.2e\n", duration);

    start = clock();
    for(i=0; i<=MAXK; i++)
        f2(MAXN-1, a, 1.1);
    stop = clock();
    duration = ((double)(stop - start))/CLOCKS_PER_SEC/MAXK;
    printf("f2 duration = %6.2e\n", duration);
    return 0;
}