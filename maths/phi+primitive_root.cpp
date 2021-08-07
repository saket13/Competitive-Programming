// <--------------------------------------------------------------------------------PHI IMPLEMENTATION--------------------------------------------------------------------->

// There are two ways in which ϕ(n) has been implemented (2 methods)
// 1. ϕ (n) - O(sqrt(n)) complexity
// 2. ϕ (n) - O(log(n))  complexity

/*
                        ϕ (ab) = ϕ(a)*ϕ(b)
                for Primes,
                        ϕ(p) = p-1
                and     ϕ(p^k) = p^k (1-1/p)
                for general N = p1^k1 * p2^k2 * .... pn^kn
                        ϕ(N) = N * (1-1/p1)*(1-1/p2)*....(1-1/pn)
*/

// 1)
// ϕ (n) - O(sqrt(n)) complexity but no need of prime number list

long long phi(long long n) {
            ll a = n, k = sqrt(n);
            if (n % 2 == 0) {
                    a -= a/2;
                    while (n%2==0) n >>= 1;
            }
            for (ll j = 3; j <= k; j += 2) {
                    if (n % j == 0) {
                        a -= a/j;
                        while (n % j == 0) n /= j;
                    }
            }
            if (n > 1) a -= a/n; //number left is prime
                return a;
}



// 2)
// ϕ (n) - O(log(n)) complexity by generating list of primes till sqrt(n)

/*
Useful even when we need to calculate ETF for given n for large number of test cases.
Since maximum number of prime factors of n is approximately log(n), so is the complexity
*/

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

int phi(int n) {
            if (n == 1) return 1;
            int etf = n, val;
            while (n != 1) {
                    val = lp[n];
                    etf -= etf/val;
                    while (n % val==0) n /= val;
            }
            return etf;
}





// <---------------------------------------------------------------------------ϕ(n) list for all numbers till given n-------------------------------------------------------->

// There are two ways in which this can be calculated (2 methods)
// 1. O(n loglog n) complexity
// 2. O(n)          complexity


// 1)
// O(n loglog n) complexity

const int MAX = 100005;

int phi[MAX];

void generate_etf() {
            phi[1] = 1;
            for(int i = 2; i < MAX; i++) {
                if(!phi[i]) {
                    phi[i] = i-1;
                    for(int j = (i<<1); j<MAX; j += i) {
                        if(!phi[j]) phi[j] = j;
                            phi[j] = phi[j]/i*(i-1);
                    }
                }
            }
}



// 2)
// O(n) complexity

//Improved Complexity : O(n)
//taken from http://codeforces.com/blog/entry/10119
const int MAX = 1000001;

vector<int> lp, primes, phi;

void generate_etf() {
            lp.resize(MAX);
            phi.resize(MAX);
            lp[1] = phi[1] = 1;
            for (int i = 2; i < MAX; ++i) {
                    if (!lp[i]) {
                        lp[i] = i;
                        phi[i] = i-1;
                        primes.emplace_back(i);
                    }
                    for (int j = 0; j < primes.size(); ++j) {
                            int x = i * primes[j];
                            if (x >= MAX) break;
                                lp[x] = primes[j];
                            if (i % primes[j] == 0) {
                                phi[x] = phi[i] * primes[j];
                                break;
                            }
                            else {
                                phi[x] = phi[i] * (primes[j]-1);
                            }
                    }
            }
}







// <--------------------------------------------------------------------------------PRIMITIVE ROOT IMPLEMENTATION----------------------------------------------------------->


//Primitive root implementations for general n

int mul(int a, int b, int c) {
            long long res = (long long)a * b;
            return (res >= c ? res % c : res);
}

int power(int a, int b, int c) {
            int x = 1, y = a;
            while(b) {
                    if (b & 1) x = mul(x, y, c);
                        y = mul(y, y, c);
                        b >>= 1;
            }
            return x;
}


int phi(int n) {
            int up = sqrt(n), ph = n;
            for(int i = 2; i <= up; ++i) {
                    if (n % i == 0) {
                        ph /= i;
                        ph *= (i - 1);
                        while(n % i == 0) n /= i;
                    }
                    if (n == 1) break;
            }
            if (n > 1) {
                    ph /= n;
                    ph *= (n-1);
            }
            return ph;
}

int primitive_root(int p) {
            vector<int> factors;
            int n = phi(p), up = sqrt(n);
            for(int i = 2; i <= up; ++i) {
                    if (n % i == 0) {
                        factors.push_back(i);
                        if (n != i*i) factors.push_back(n/i);
                    }
            }
            for(int i = 2; i < p; ++i) {
                    if (__gcd(i, p) != 1) continue;
                        bool done = true;
                    for(auto it : factors) {
                        if (power(i, n / it, p) == 1) {
                            done = false;
                            break;
                        }
                    }
                    if (done) return i;
            }
            return -1;
}


