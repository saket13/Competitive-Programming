// <--------------------------------------------------------------------------------BASICS--------------------------------------------------------------------->
// Addition, Subtraction, Multiplication, Fast Binary Exponentiation, and
// Factors of a number


// GCD of a and b
inline int gcd(int a, int b){
            return b ? gcd(b, a % b) : a;
}

//(a + b) % c
int add(int a, int b, int c) {
            int res = a + b;
            return (res >= c ? res - c : res);
}

//(a - b) % c
int mod_neg(int a, int b, int c) {
            int res; if(abs(a-b) < c) res = a - b;
            else res = (a-b) % c;
            return (res < 0 ? res + c : res);
}

//(a * b) % c
int mul(int a, int b, int c) {
            long long res = (long long)a * b;
            return (res >= c ? res % c : res);
}

//(a * b) % c for very large numbers, to avoid overflows
//O(1) hack taken from http://codeforces.com/blog/entry/15884
long long mulmod(long long a, long long b, long long m) {
            long long q = (long long)(((long double)a*(long double)b)/(long double)m);
            long long r = a * b - q * m;
            if(r > m) r %= m; if( r < 0) r += m;
            return r;
}

//(a ^ n)
//Complexity: O(log (n))
long long expo(long long a, long long n) {
            long long x = 1, p = a;
            while(n) {
                if(n & 1) x = x * p;
                    p = p * p;
                    n >>= 1;
            }
            return x;
}

//(a ^ n) % m
//Complexity : O(log (n))
int power(long long a, long long n, int m) {
            int x = 1, p = a % m;
            while(n) {
                if(n & 1) x = mul(x, p, m);
                    p = mul(p, p, m);
                    n >>= 1;
            }
            return x;
}

// Count of the total no of divisors of n
// O(sqrt(n)) implementation

long long count_divisors(long long n){
            ll count = 0;
            for(auto i=1;i<=sqrt(n);i++){
                    if(n % i==0){
                            if(n/i==i)      count++;
                            else            count += 2;
                    }
            }
            return count;
}


// It is not prime factorization i.e it includes 1 and n too..,
// start loop from 2 to get prime factors only

// Factorization of a number
vector<ll> factors;
void factorization(ll n){
             for(ll i = 1; i <= (ll)(sqrt(n)); ++i) {
                        if (n % i == 0) {
                                
                        if (i != n/i) factors.push_back(n/i), factors.push_back(i);
                        else factors.push_back(i);
                        }
            }
}


// <--------------------------------------------------------------------------------SIEVE--------------------------------------------------------------------->

//Generating List of Primes through sieve( 3 methods)
// 1. Normal Sieve
// 2. Factor Sieve (Also stores the smallest prime factor of n)
// 3. Faster Bitset Sieve

/*
Prime number Theorem : Number of primes till n is approximately (n/log(n))
Size limits i.e. number of primes below given n
1    10                     4
2    100                    25
3    1,000                  168
4    10,000                 1,229
5    100,000                9,592
6    1,000,000              78,498
7    10,000,000             664,579
8    100,000,000            5,761,455
*/

// 1)

// Normal Sieve
const int MAX = 1000001;
bool prime[MAX+1];

void normal_sieve() {
    
            memset(prime, true, sizeof(prime));
            prime[0] = prime[1] = false;
    
            for (int p=2; p*p<=MAX; p++){
      
                // If prime[p] is not changed, then it is a prime
                if (prime[p] == true){
          
                    // Update all multiples of p greater than or
                    // equal to the square of it
                    // numbers which are multiple of p and are
                    // less than p^2 are already been marked.
                    for (int i=p*p; i<=MAX; i += p)
                            prime[i] = false;
                }
            }
}

// 2)

//Factor sieve algorithm (taken from http://e-maxx.ru/algo/prime_sieve_linear)
//stores smallest prime factor of 'n' in vector 'lp'
//Complexity : O(n)
const int MAX = 1000001;

vector<int> lp, primes;

void factor_sieve() {
            lp.resize(MAX);
            lp[1] = 1;
            for (int i = 2; i < MAX; ++i) {
                    if (lp[i] == 0) {
                        lp[i] = i;
                        primes.emplace_back(i);
                    }
                    for (int j = 0; j < primes.size() && primes[j] <= lp[i]; ++j) {
                        int x = i * primes[j];
                        if (x >= MAX) break;
                            lp[x] = primes[j];
                    }
            }
}

// 3)

//Using C++ bitset and much more optimisations
//Taken from https://github.com/kartikkukreja/blog-codes/blob/master/src/spoj_CPRIME.cpp
const int MAX = 1e8 + 8;

bitset<MAX/2+1> num;
vector<int> primes;

void EratostheneSieve() {
            int x = MAX/2, y =(sqrt(MAX)-1)/2, i, j, z;
            for (i = 1; i <= y; ++i) {
                    if (num[i] == 0) {
                        for (j = (i*(i+1))<<1, z = (i<<1); j <= x; j += z+1) {
                                num[j] = 1;
                        }
                    }
            }
            primes.emplace_back(2);
            for (i = 3; i < MAX; i += 2) {
                    if (!num[i>>1]) primes.emplace_back(i);
            }
}

