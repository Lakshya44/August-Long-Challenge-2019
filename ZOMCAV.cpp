#include <bits/stdc++.h>
using namespace std;
#define ll long long int
#define ld long double
#define show(x) cout<<x<<'\n'
#define showh(x) cout<<x<<' '
#define go(i,a,n) for(ll i=a;i<n;i++)
#define gor(i,a,n) for(ll i=n-1;i>=a;i--)
#define pb push_back
#define mp make_pair
#define mod 1000000007
bool prime[100001];
ll pre[2001][2001];
bool ispoweroftwo(ll x)
{
    return x && !(x & (x-1));
}
ll xorcal(ll n)
{
    if(n%4==0)
        return n;
    if(n%4==1)
        return 1;
    if(n%4==2)
        return n+1;
    if(n%4==3)
        return 0;
}
void sieve(ll n)
{
    memset(prime,true,sizeof(prime));
    prime[0]=false;
    prime[1]=false;
    for(ll i=2;i*i<=n;i++)
    {
        if(prime[i]==true)
        {
            for(ll j=i*i;j<=n;j+=i)
            {
                prime[j]=false;
            }
        }
    }
}
bool isprime(ll n)
{
    if (n<=1) return false;
    if (n<=3) return true;

    if(n%2==0 or n%3==0) return false;

    for(ll i=5;i*i<=n;i+=6)
    {
        if(n%i==0 or n%(i+2)==0) return false;
    }
    return true;
}

ll modinverse(ll a,ll m)
{
    ll m0 = m;
    ll y = 0, x = 1;

    if (m == 1)
      return 0;

    while (a > 1)
    {
        ll q = a / m;
        ll t = m;

        m = a % m; a = t;
        t = y;

        y = x - q * y;
        x = t;
    }

    if (x < 0)
       x += m0;

    return x;
}

ll gcd(ll a,ll b)
{
    if(a==0)
    {
        return b;
    }
    return(b%a,a);
}

ll power(ll A, ll B)
{
    if (A == 0)
        return 0;
    if (B == 0)
        return 1;

    ll y;
    if (B % 2 == 0) {
        y = power(A, B / 2);
        y = (y * y) % mod;
    }

    else {
        y = A % mod;
        y = (y * power(A, B - 1) % mod) % mod;
    }

    return (ll)((y + mod) % mod);
}
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    ll t;
    cin>>t;
    while(t--)
    {
        ll n;
        cin>>n;
        vector<ll>c(n+1),h(n+1),diff(n+1,0);
        go(i,1,n+1)
        {
            cin>>c[i];
        }
        go(i,1,n+1)
        {
            cin>>h[i];
        }
        go(i,1,n+1)
        {
            ll left = max(1LL,i-c[i]);
            ll right = i + 1LL + c[i];
            diff[left]++;
            if(right<=n)
            {
                diff[right]--;
            }
        }
        go(i,1,n+1)
        {
            diff[i] += diff[i-1];
        }
        sort(h.begin(),h.end());
        sort(diff.begin(),diff.end());
        if(h == diff)
        {
            show("YES");
        }
        else
        {
            show("NO");
        }
    }
    return 0;
}

