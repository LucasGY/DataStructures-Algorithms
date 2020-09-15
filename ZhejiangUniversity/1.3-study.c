/*
最大子列和问题
给定整数序列A = {A1,...Ai,...Aj,...AN}
求max(0, sum(A[from i to j]))
*/
#include<math.h>
#include<time.h>
#include<stdio.h>

/*1、O(N**3) 遍历所有可能的子列进行求和，将最大的保存到buf里面，最后与0比较*/
int MaxSubseqSum1(int A[], int N)
{
    //int N;
    int MAX_sum_buf,THIS_sum = 0 ;//分别是最大子列和的buf，和此次求出的子列和
    int i,j,k;
    //N = (sizeof(A)/sizeof(int)); //求数组的长度
    printf("N = %d\n", N);
    for(i=0; i<N; i++)
    {
        for(j=i; j<N; j++)
        {
            THIS_sum = 0;
            for(k=i; k<=j; k++)
                THIS_sum += A[k];
            if (THIS_sum > MAX_sum_buf)
                MAX_sum_buf = THIS_sum;
        }
    }
    return MAX_sum_buf;
}

/*2、O(N**2) 在确定左面的索引的情况下,在计算子序列和时可以利用上一个值*/
int MaxSubseqSum2(int A[], int N)
{
    //int N;
    int MAX_sum_buf,THIS_sum = 0 ;//分别是最大子列和的buf，和此次求出的子列和
    int i,j;
    //N = (sizeof(A)/sizeof(int)); //求数组的长度
    printf("N = %d\n", N);
    for(i=0; i<N; i++)
    {
        THIS_sum = 0;
        for(j=i; j<N; j++)
        {
            THIS_sum += A[j];
            if (THIS_sum > MAX_sum_buf)
                MAX_sum_buf = THIS_sum;
        }
    }
    return MAX_sum_buf;
}
/*3、O(N*logN) 分而治之*/
int Max3( int A, int B, int C )
{ /* 返回3个整数中的最大值 */
    return A > B ? A > C ? A : C : B > C ? B : C;
}
int DivideAndConquer( int List[], int left, int right )
{/* */
    int MaxLeftSum, MaxRightSum; /* 存放左右子问题的解 */
    int MaxLeftBorderSum, MaxRightBorderSum; /*存放跨分界线的结果*/
    int LeftBorderSum, RightBorderSum;//子问题子序列和
    int center, i;

    if(left == right)
        return (List[left] > 0) ? List[left] : 0 ;
    /* 下面是"分"的过程 */
    center = ( left + right ) / 2; /* 找到中分点 */
    /* 递归求得两边子列的最大和 */
    MaxLeftSum = DivideAndConquer( List, left, center );
    MaxRightSum = DivideAndConquer( List, center+1, right );
 
    /* 下面求跨分界线的最大子列和 */
    MaxLeftBorderSum = 0; LeftBorderSum = 0;
    for( i=center; i>=left; i-- ) { /* 从中线向左扫描 */
        LeftBorderSum += List[i];
        if( LeftBorderSum > MaxLeftBorderSum )
            MaxLeftBorderSum = LeftBorderSum;
    } /* 左边扫描结束 */
 
    MaxRightBorderSum = 0; RightBorderSum = 0;
    for( i=center+1; i<=right; i++ ) { /* 从中线向右扫描 */
        RightBorderSum += List[i];
        if( RightBorderSum > MaxRightBorderSum )
            MaxRightBorderSum = RightBorderSum;
    } /* 右边扫描结束 */
 
    /* 下面返回"治"的结果 */
    return Max3( MaxLeftSum, MaxRightSum, MaxLeftBorderSum + MaxRightBorderSum );

}
int MaxSubseqSum3( int List[], int N )
{ /* 保持与前2种算法相同的函数接口 */
    return DivideAndConquer( List, 0, N-1 );
}




/*4、O(N) 在线处理*/
int MaxSubseqSum4(int A[], int N)
{
    int MAX_sum_buf,THIS_sum = 0 ;//分别是最大子列和的buf，和此次求出的子列和
    int i,j;

    for(i=0; i<N; i++)
    {
        THIS_sum += A[i];
        if (THIS_sum > MAX_sum_buf)
            MAX_sum_buf = THIS_sum;
        else if (THIS_sum < 0) //如果当前子列和为负，并不能使后面的子列和变大，
            THIS_sum = 0; //故丢弃，但之前最大的仍然保存在MAX_sum_buf中
    }
    return MAX_sum_buf;
}

int main()
{
    int sum = 0;
    int A[] = {1,2,-99,4,5};
    sum = MaxSubseqSum3(A, 5);
    printf("sum: %d\n", sum);
    return 0;
}