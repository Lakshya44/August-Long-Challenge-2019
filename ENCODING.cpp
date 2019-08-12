#include <bits/stdc++.h>

#define go(i,n) for(ll i=0;i<n;++i)
#define gor(i,a,n) for(ll i=a;i<=n;++i)
#define ll long long
#define mod  1000000007
#define show(x) cout<<x<<'\n'

using namespace std;

bool prime[100001];
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
    show(prime[89]);
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


ll p[100005];
vector<vector<ll> >dp(100005, vector<ll> (10,0));

string Diff(string s1, string s2="1")
{
    string s = "";
    int n1 = s1.length(), n2 = 1;
    reverse(s1.begin(),s1.end());
    int car = 0;
    for(int i=0;i<n2;i++){
        int subst = ((s1[i]-'0') - (s2[i]-'0') - car);
        if(subst < 0){
            subst = subst + 10;
            car = 1;
        }
        else
            car = 0;
        s.push_back(subst + '0');
    }
    for(int i=n2;i<n1;i++){
        int subst = ((s1[i]-'0')-car);
        if(subst < 0){
            subst = subst + 10;
            car = 1;
        }
        else
            car = 0;
        s.push_back(subst + '0');
    }
    reverse(s.begin(),s.end());
    return s;
}

ll cal(string s){
    ll n = s.length();
    vector<vector<ll> >nop(n, vector<ll> (10,0));
    go(i,10) nop[0][i] = 1;
    
    gor(i,1,n-1){
        gor(j,0,(s[i]-'0')){
            ll x=0;
            if(j==(s[i]-'0')){
                gor(k,0,(s[i-1]-'0')) x = (x + nop[i-1][k])%mod;
            }else{
                x = p[i];
            }
            nop[i][j]=x;
        }
    }
    
    vector<vector<ll> >v(n, vector<ll> (10,0));
    go(i,10) v[0][i]=i;
    
    gor(i,1,n-1){
        gor(j,0,(s[i]-'0')){
            ll x = 0;
            if(j==(s[i]-'0')){
                ll s1 = 0;
                gor(k,0,(s[i-1]-'0')) s1 = (s1 + v[i-1][k])%mod;
                ll s2 = j;
                s2 = (s2 * p[i])%mod;
                s2 = (s2 * nop[i][j])%mod;
                ll s3 = j;
                s3 = (s3 * p[i-1])%mod;
                s3 = (s3 * nop[i-1][j])%mod;
                if(j>(s[i-1]-'0')) s3=0;
                x = (s1+s2-s3)%mod;
                if(x<0) x+=mod;
            } else{
                ll s1=0;
                gor(k,0,9) s1 = (s1 + dp[i-1][k])%mod;
                ll s2 = j;
                s2 = (s2 * p[i])%mod;
                s2 = (s2 * p[i])%mod;
                ll s3=j;
                s3 = (s3 * p[i-1])%mod;
                s3 = (s3 * p[i-1])%mod;
                x = (s1+s2-s3)%mod;
                if(x<0) x+=mod;
            }
            v[i][j]=x;
        }
    }
    return v[n-1][s[n-1]-'0'];
}
int main() {
    ios_base::sync_with_stdio(false);
    p[0]=1;
    gor(i,1,100004) p[i] = (p[i-1]*10)%mod;
    go(i,10) dp[0][i]=i;
    gor(i,1,100004){
        go(j,10){
            ll s1 = 0;
            go(k,10) s1 = (s1 + dp[i-1][k])%mod;
            ll s2 = j;
            s2 = (s2 * p[i])%mod;
            s2 = (s2 * p[i])%mod;
            ll s3 = j;
            s3 = (s3 * p[i-1])%mod;
            s3 = (s3 * p[i-1])%mod;
            dp[i][j] = (s1+s2-s3)%mod;
            if(dp[i][j]<0) dp[i][j]+=mod;
        }
    }
    ll t;
    cin>>t;
    while(t--){
        int nl,nr;
        string stl,str;
        cin>>nl>>stl>>nr>>str;
        stl = Diff(stl);
        ll s1 = 0;
        go(i,(stl[0]-'0')) s1 = (s1+dp[stl.length()-1][i])%mod;
        reverse(stl.begin(),stl.end());
        s1 = (s1+cal(stl))%mod;
        ll s2=0;
        go(i,(str[0]-'0')) s2 = (s2+dp[str.length()-1][i])%mod;
        reverse(str.begin(),str.end());
        s2 = (s2+cal(str))%mod;
        ll result = (s2-s1+mod)%mod;
        show(result%mod);
    }
	return 0;
}
