#include <iostream>
#include <vector>
#include <math.h>
#include <stdlib.h>
#include <string.h>

using namespace std;
typedef long long ll;
// Define this based on problem type , for RMQ this should be a big value, for problems sum of range this would be 0
#define NO_OVERLAP 0
ll lazy[450000];
ll segmentTree[450000];
ll N;
void updateRangeLazy(ll value, ll low, ll high,ll seg_start=-1, ll seg_end=-1, ll index =0)
{
	if( (seg_start==-1) && (seg_end==-1)) //TRick to detect first call
		{seg_start =0 ; seg_end = N-1;}
	
	//cout << "seg_start ="<<seg_start << " seg_end"<<seg_end<<endl;	
		
	// check in lazy array, if non-zero, add that value and push the value to child nodes
	if(lazy[index])
	{
		segmentTree[index] += ((seg_end-seg_start+1)*lazy[index]); //Update and also push to child nodes
		if(seg_start!=seg_end)
		{
			lazy[2*index+1] += lazy[index];
			lazy[2*index+2] += lazy[index];
		}
		lazy[index] =0;
	}
	
	if((seg_start > seg_end) || (seg_end < low) || (seg_start > high))
		return;
	// if there is a `complete overlap` stop and update the segmentTree index return
	// complete overlap i.e. segment start & end should fit in the low & high range
	if(seg_start >= low && seg_end<= high)
	{
		segmentTree[index] += ((seg_end-seg_start+1)*value);
		if(seg_start!=seg_end)
		{
			lazy[2*index+1] += value;
			lazy[2*index+2] += value;
		}
		return;
	}
	
	
	// recur further only if the given range partially overlap in segment range.
	ll mid = (seg_start + seg_end ) /2;
	updateRangeLazy(value, low, high, seg_start, mid, 2*index+1);
	updateRangeLazy(value, low, high, mid+1, seg_end, 2*index+2);
	segmentTree[index] = (segmentTree[2*index+1]+ segmentTree[2*index+2]);
}
ll queryLazy(ll low, ll high, ll seg_start=0, ll seg_end=0, ll index=0)
{
	
	//Trick to detect first call and update high
	if(!seg_start && !seg_end && !index)
		 seg_end = N-1;
	if ( (seg_start > seg_end) ||(seg_end < low) || (seg_start > high))
		return NO_OVERLAP;
	if(lazy[index])
	{
		segmentTree[index] += ((seg_end-seg_start+1)*lazy[index]); //Update and also push to child nodes
		if(seg_start!=seg_end)
		{
			lazy[2*index+1] += lazy[index];
			lazy[2*index+2] += lazy[index];
		}
		lazy[index] =0;
	}
	// complete overlap i.e. segment start & end should fit in the low & high range
	if(seg_start>= low && seg_end <=high)
		return segmentTree[index];
	// no overlap
	else
	{
		ll mid = (seg_start + seg_end ) /2;
		ll a = queryLazy(low, high, seg_start, mid, (2*index)+1); 
		ll b = queryLazy(low, high, mid+1, seg_end, (2*index)+2);
		return (a+ b);
	}
}
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	ll t;
	cin >>t;
	for (ll i=0; i<t;i++)
	{
		//cout <<"#Test case "<<i<<endl;
		ll C;
		cin >> N>> C;
		memset(&segmentTree, 0, 450000*sizeof(ll));
		memset(&lazy, 0, 450000*sizeof(ll));
		for (ll j =0; j<C; j++)
		{
			ll type, start, end , value;
			cin >> type; 
			if(type) // Query
			{
				cin >> start>>end;
				cout << queryLazy(start-1, end-1)<<"\n";
			}
			else //update
			{
				cin >> start>>end>>value;
				updateRangeLazy(value, start-1, end-1);
			}
		}
		
	}
}
