#include <bits/stdc++.h>
#include <algorithm>
#define MIN(a,b)  (a<b?a:b)
#define MAX(a,b)  (a>b?a:b)
#define pi 3.14159265358979323846264338327950288419716939937510582097494459230

//BIT operation
#define SET_BIT  (a, x)   (a |= ((1<<x)))
#define CLEAR_BIT(a, x)   (a &= (~(1<<x)))
#define IS_SET   (a, x)   ((a>>x) & 1)
#define swap(a, b) do{ int t=a; a=b; b=t;}while(0);
using namespace std;
typedef unsigned long long ull;
typedef long long ll;
int modifyBit(int n, int p, bool b)
{
    int mask = 1 << p;
    return (n & ~mask) | ((b << p) & mask);
}
#define GC getchar_unlocked()
int scan()
{
    int ret=0,sign=1;
    int ip=GC;
    for(;ip<'0'||ip>'9';ip=GC)
        if(ip=='-')
        {
            sign=-1;
            ip=GC;
            break;
        }
    for(;ip>='0'&&ip<='9';ip=GC)
        ret=ret*10+ip-'0';
    return (ret*sign);
}


#define vii vector<int, int>
#define vpii vector<pair<int, int>>
#define NO_OVERLAP 0
int lazy[600000]={0};
int segmentTree[600000]={0};
int N;
/*
@segmentTree : segment Tree 
@i : low range 
@ j : high range
@ low: subtree low
@ high: subtree high
@ index: index in segmentTree array, Each Node will contain result of input array [low, high] operation
*/
int query(int i, int j, int low=0, int high=0, int index=0)
{
	//Trick to detect first call and update high
	if(!low && !high && !index)
		 high = N-1;
	// complete overlap
	if((low>= i) && (high <=j))
		return segmentTree[index];
	else if ((high < i) || (low > j))
		return NO_OVERLAP;
	// partial overlap
	else
	{
		int mid = (low + high ) /2;
		int a = query(i, j, low, mid, (2*index)+1); 
		int b = query(i, j, mid+1, high, (2*index)+2);
		return (a+ b);
	}
}
/*
 @i :   low index for updateRange
 @j :   high index for updateRange
 @value:value to be updated 
 @low:  low index for SegTree
 @high: high index for SegTree
 @index: for saving
 */
void updateRange(int idx, int value, int low=-1, int high=-1, int index=0)
{
	if( (low==-1) && (high==-1)) //TRick to detect first call
		{low =0 ; high = N-1;}
	if ((idx < low)  || (idx > high))
		return;
	if(low == high)
		segmentTree[index] = value;
	else if(low<= idx && idx <=high)
	{
		int mid = (low + high ) /2;
		if(idx<=mid)
			updateRange(idx, value, low, mid, (2*index)+1); 
		else
			updateRange(idx, value, mid+1, high, (2*index)+2);
		segmentTree[index] = (segmentTree[2*index+1]+ segmentTree[2*index+2]);
	}
	else 
		return ;
}
uint getAbs(int n)
{
  uint const mask = n >> (sizeof(uint) * CHAR_BIT - 1);
  return ((n + mask) ^ mask);
}
// stores smallest prime factor for every number
#define MAXN   100001
int factor[MAXN];

void sieve()
{
    factor[1] = 1;
    for (int i=2; i<MAXN; i++)
        factor[i] = i; // initialize
 
    for (int i=4; i<MAXN; i+=2)//Aint even starting from 4
        factor[i] = 2;
 
    for (int i=3; i*i<MAXN; i++)
    {
        if (factor[i] == i)
        {
            for (int j=i*i; j<MAXN; j+=i) // loop tiint root
 
                if (factor[j]==j)
                    factor[j] = i;
        }
    }
}

//TODO : pair , string, priority_queue, set, map, sort, algorithm 
int binary_search(vector<int> & A, int val)
{
	int l =0, r= A.size()-1, m;
	m = (l+r)/2;
	while(l<=r)
	{
		m = (l+r)/2;
		if(A[m]==val)
			return m;
		else if( val > A[m])
			l = m+1;
		else
			r = m-1;
			
	}
	return m;
}
int main(int argc, char*argv[])
{
	int Q;
	Q=scan();
	vector<pair<char, int> > q;
	vector<int> M;
	for (int i=0; i< Q; i++)
	{
		char type; int val;
		scanf("%c",&type);
		val = scan();
		q.push_back(make_pair(type, val));
		M.push_back(val);
	}
	sort(M.begin(), M.end());
	vector <int> O;// unique value's of queries in ascending order, segment tree wiint be created with size of this array and aint value as 0.
	O.push_back(M[0]);
	for (int i=1; i<Q; i++)
	{
		if(M[i]!=M[i-1])
			O.push_back(M[i]);
			
	}
	// At this stage we know that query contains distinct value
	//memset(&segmentTree, 0, 600000*sizeof(int));
	//memset(&lazy, 0, 600000*sizeof(int));
	N = O.size();
	int index, l, r, m, x, res;
	for (int i=0; i<Q; i++)
	{
		switch(q[i].first)
		{
			case 'I':
				// Do a bsearch in N to find the index and then go and update that index as 1
				index = binary_search(O, q[i].second);
				//cout <<"push "<< index<<endl;
				updateRange(index, 1);
			break;
			case 'D':
				index = binary_search(O, q[i].second);
				//cout <<"push "<< index<<endl;
				updateRange(index, 0);
			break;
			case 'K':
			x = q[i].second;
			res = query(0,N-1);
            if(x>res) printf("invalid\n");
            else
            {
                l = 0;
                r = N-1;
                while(x>0 && l<r)
                {
                    m = (l+r)/2;
                    res = query(l, m);
                    if(x>res){
                        x -= res;
                        l=m+1;
                    }
                    else{
                        r=m;
                    }
                }
                printf("%d\n",O[l]);;
            }
			
			break;
			case 'C':
				index = binary_search(O, q[i].second);
				if(index==0)
					printf("0\n");
				else
					printf("%d\n",query(0, index-1));
			break;
		}
	}
}
