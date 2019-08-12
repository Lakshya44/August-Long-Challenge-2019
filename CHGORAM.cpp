#include <bits/stdc++.h>
using namespace std;
#define ll long long int
#define fast ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
#define big 123456
#define show(x) cout<<x<<'\n'
#define showh(x) cout<<x<<' '
#define go(i,a,n) for(ll i=a;i<n;i++)
#define gor(i,a,n) for(ll i=n-1;i>=a;i--)
#define pb push_back
#define mp make_pair
#define mod 1000000007

struct BIT
{
	ll n;
	vector<ll> bit;

	void init(ll N)
	{
		n = N;
		bit.assign(N + 1, 0);
	}

	void update(ll idx, ll val)
	{
		while(idx <= n)
		{
			bit[idx] += val;
			idx += idx & -idx;
		}
	}

	ll prefix(ll idx)
	{
		ll ans = 0;
		while(idx > 0)
		{
			ans += bit[idx];
			idx -= idx & -idx;
		}
		return ans;
	}

	ll query(ll l, ll r)
	{
		return prefix(r) - prefix(l - 1);
	}
};

vector<ll> G[big];
ll start[big],last[big],cnt;

void dfs(ll node,ll par)
{
	start[node]=++cnt;
	for(ll i=0;i<G[node].size();i++)
	{
		if(G[node][i]==par)
		{
			continue;
		}
		dfs(G[node][i],node);
	}
	last[node]=cnt;
}

int main()
{
	fast
	ll t;
	cin>>t;
	while(t--)
	{
		ll  result=0;
		go(i,0,big)
		{
		    G[i].clear();
		}
		cnt=0;
		ll n,x,y,p;
		cin>>n>>x>>p>>y;
		go(i,0,n-1)
		{
			cin>>x>>y;
			G[x].push_back(y);
			G[y].push_back(x);
		}
		BIT sql;
		sql.init(n+10);
		dfs(1,0);

		gor(i,1,n+1)
		{
			ll temp1=0,temp2=0,s1=0,s2=0,b1=0,b2=0;
			ll sub=last[i]-start[i];
			ll temp,op,hemp,sum;
			go(j,0,(ll)G[i].size())
			{
				if(start[i]>start[G[i][j]])
				{
					temp=sql.query(0,start[i]-1)+sql.query(last[i]+1,n);
					b1+=temp; 
					b2+=(temp*temp);
					temp2+=(n-sub-1)*(n-sub-1);
					temp=n-sub-1-temp;
					s1+=temp;
					s2+=(temp*temp);
					continue;
				}
				temp=sql.query(start[G[i][j]],last[G[i][j]]);
				b1+=temp; 
				b2+=(temp*temp);
				temp2+=(last[G[i][j]]-start[G[i][j]]+1)*(last[G[i][j]]-start[G[i][j]]+1);
				temp=last[G[i][j]]-start[G[i][j]]+1-temp;
				s1+=temp;
				s2+=(temp*temp);		
			}
			temp1=n-1;
			op=((b1*b1)-b2)/(2LL);
			hemp=((s1*s1)-s2)/(2LL);
			sum=((temp1*temp1)-temp2)/(2LL);
			if(p==1)
			{
				result+=op;
			}
			else if(p==2)
			{
				result+=(sum-op-hemp);
			}
			else
			{
				result+=hemp;
			}
			sql.update(start[i],1);
		}
		show(result);
	}
	return 0;
}