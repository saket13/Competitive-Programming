//
//   “Daḷhaṃ sikkhatha santiyā.” - Utthana Sutta (Sutta Nipata)
//   "Life is a manifestation of where your energy is flowing" - Dandapani
//    Sāket Sāumyā
//    JUN 5 2020
//

#include <bits/stdc++.h>

using namespace std;


#define ll long long
#define all(x) x.begin(),x.end()
#define endl '\n'
#define RESET   "\033[0m"
#define RED     "\033[31m"      /* Red */
#define what_is(x) cerr << RED << #x << " is " << x  << RESET << endl;



const long long MOD = 1e9 + 7 ;
const int N = (1e5) + 5;
const long long INF = 1LL << 57;
 
// Data Structures
vector <ll> vec(N), v1, v2, v3;
vector < pair < ll , string > > vp, vp1, vp2;
set < ll > se, se1;
unordered_set <ll > use;
multiset < ll > ms;
map <  string, ll > mp, done, mp1, arr;
unordered_map < string, ll > ump;


ll t, n, m, p, q, x, y, a, b, c, mini= LLONG_MAX, maxi= LLONG_MIN, res, ans;




//<--------------------------------------------------------------------------------------------------------------------------->


// GCD of a and b
inline long long gcd(long long a, long long b){
            return b ? gcd(b, a % b) : a;
}

//Polard-Rho brent Factorisation method in C++ with pruning
//Taken from https://www.hackerearth.com/october-clash-16/algorithm/phi-phi-phi/submission/5703764/
//Call init() first
//Factorisation in O(log n) till MAX
//for number above MAX > O(n^1/4 logn)
//See note on line 35 for more details

namespace factorisation {
int MAX = 1000001;
vector<int> lp, primes;

void init() {
            lp.resize(MAX);
            lp[1] = 1;
            for (int i = 2; i < MAX; ++i) {
                    if (lp[i] == 0) {
                        lp[i] = i;
                        primes.push_back(i);
                    }
                    for (int j = 0; j < primes.size() && primes[j] <= lp[i]; ++j) {
                        int x = i * primes[j];
                        if (x >= MAX) break;
                        lp[x] = primes[j];
                    }
            }
}

long long Rand() {
            return rand()*(1ll<<48)+rand()*(1ll<<32)+rand()*(1ll<<16)+rand();
}

/*If getting TLE comment below function and use below one but
it can have precision error but chances are almost negligible
*/
long long mulmod(long long a, long long b, long long m) {
            // long long i, res = 0;
            // for(i = 1; i <= b; i*=2) {
            //     if (b&i) {
            //         res += a;
            //         if (res >= m) res -= m;
            //     }
            //     a += a;
            //     if (a >= m) a -= m;
            // }
            // return res;
            long long q = (long long)(((long double)a*(long double)b)/(long double)m);
            long long r = a*b - q*m;
            if (r > m) r %= m;
            if (r < 0) r += m;
            return r;
}

long long power(long long a, long long n, long long m) {
            long long x = 1, y = a;
            while(n) {
                    if (n & 1) x = mulmod(x, y, m);
                        y = mulmod(y, y, m);
                        n >>= 1;
            }
            return x;
}

bool witness(long long a, long long n) {
            long long x, y, u = n - 1, t = 0;
            while(u % 2 == 0) {
                    u >>= 1;
                    t += 1;
            }
            x = power(a, u, n);
            while(t--) {
                    y = x;
                    x = power(x, 2, n);
                    if(x == 1 && y != 1 && y != n-1) return 1;
            }
            return x != 1;
}

bool miller_rabin(long long n) {
            if (n < MAX) return lp[n] == n;
            if (witness(28087,n)) return 0;
            return 1;
}

long long absl(long long x) {
            return (x < 0 ? -x : x);
}

int _c = 1;

long long func(long long x,long long n) {
            long long res = mulmod(x, x, n) + _c;
            return (res >= n ? res % n : res);
}

long long go(long long n) {
            long long x, y, d = 1;
            x = y = rand();
            if (x >= n) x %= n, y %= n;
            while(d == 1) {
                    x = func(x, n);
                    y = func(func(y, n), n);
                    d = gcd(absl(y - x), n);
            }
            if (d != n) return d;
            return d;
}

void pollard_rho(long long n, int& m, long long s[]){
            long long x;
            if (n == 1) return ;
            if (n < MAX) {
                    while (n != 1) {
                        int p = lp[n];
                        while(n % p == 0) {
                                n /= p;
                                s[m++] = p;
                        }
                    }
                    return ;
            }
            while (!miller_rabin(n)) {
                    for (_c = 1, x = n; x == n; _c = 1 + rand()%(n-1)) {
                            x = go(n);
                    }
                    if(x < 0) break;
                    n /= x;
                    pollard_rho(x, m, s);
            }
            if(n > 1) s[m++] = n;
}

vector<pair<long long,int>> factorise(long long n) {
            vector<long long> temp;
            while(n % 2 == 0) {
                    temp.push_back(2);
                    n >>= 1;
            }
            int m = 0;
            long long s[70];
            pollard_rho(n, m, s);
            for(int i = 0; i < m; ++i) {
                    temp.push_back(s[i]);
            }
            sort(temp.begin(), temp.end());
            vector<pair<long long,int>> ans;
            for(int i = 0; i < temp.size(); ++i) {
                    int j = i, e = 0;
                    while(j < temp.size() && temp[j] == temp[i]) {
                            e += 1;
                            j += 1;
                    }
                    ans.push_back({temp[i], e});
                    i = j - 1;
            }
            return ans;
}
}
using namespace factorisation;

ll k;

signed  main(){
           
            ios_base::sync_with_stdio(false);
            cin.tie(nullptr);cout.tie(nullptr);
           
            init();
            cin >> n >> k;
            res = n;
            for (int i=0; i<k; ++i){
                    if (res == 1)       break;
                    auto ans_vect = factorise(res); //ans_vect stores primes(p1,p2,p3,...) as 1st & power(a1,a2,a3,...) as 2nd
                    for (auto i: ans_vect){
                            res /= (i.first);
                            res *= (i.first-1);
                    }
            }
            cout << res << endl;
            






























}
            
            











































       
 
       
       
       
       

