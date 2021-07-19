// <--------------------------------------------------------------------------------O(logn) Fibonacci IMPLEMENTATION--------------------------------------------------------------------->

// Fibonacci implementation where fibo[MAX] will store fibonacci values upto MAX in
// O(log n) complexity

/*
Fibonacci sequence defined by the following recusion
f[0] = 0, f[1] = 1
f[n] = f[n-1] + f[n-2]
*/

const int MAX = 1e5 + 5;
const int MOD = 1e9 + 7;

int add(int a, int b, int c){int res=a+b;return(res>=c?res-c:res);}
int mod_neg(int a, int b, int c){int res;if(abs(a-b)<c)res=a-b;else res=(a-b)%c;return(res<0?res+c:res);}
int mul(int a, int b, int c){long long res=(long long)a*b;return(res>=c?res%c:res);}

int fibo[MAX];

void init() {
            fibo[0] = 0, fibo[1] = 1;
            for(int i = 2; i < MAX; ++i) {
                fibo[i] = add(fibo[i-1], fibo[i-2], MOD);
            }
}

//Complexity: O(log n)
inline int fib(int& x, int& y, long long n) {
            if (n < 100000) {
                x = fibo[n], y = fibo[n+1];
            }
            else {
                int a, b;
                fib(a, b, n >> 1);
                int z = (b << 1) - a;
                if (z < 0) z += MOD;
                x = mul(a, z, MOD);
                y = add(mul(a, a, MOD), mul(b, b, MOD), MOD);
                if (n & 1) {
                    x = add(x, y, MOD);
                    x ^= y ^= x ^= y;
                }
            }
            return x;
}

inline int fib(long long n) {
            int x = 0, y = 1;
            return fib(x, y, n);
}




// <--------------------------------------------------------------------------------FAST DOUBLING IMPLEMENTATION----------------------------------------------------------->


// Normal fibonacci algo runs in O(n) complexity which for n=1e9, operations might take upto 10-15 seconds
// so two methods are used 1. Matrix exponentiation 2. Fast Doubling Method

ll a,b,c,d;
void fast_doubling(ll n, ll ans[])
{
            if(n == 0){
                ans[0] = 0;
                ans[1] = 1;
                return;
            }
            fast_doubling((n/2),ans);
            a = ans[0];             /* F(n) */
            b = ans[1];             /* F(n+1) */
            c = 2*b - a;
            
            if(c < 0)
                c += MOD;
            c = (a * c) % MOD;      /* F(2n) */
            d = (a*a + b*b) % MOD;  /* F(2n + 1) */
            
            if(n%2 == 0){
                ans[0] = c;
                ans[1] = d;
            }
            else{
                ans[0] = d;
                ans[1] = c+d;
            }
}

int main()
{       
        ll n,t;
        cin >> t;             // nth value of fibonacci to be found
        while(t--){
            int flag=0;
            cin >> n;
            ll ans[2]={0};                      // Will store the fibonacci numbers 
            rf(i,0,10000){
                fast_doubling(i,ans);
                if( ans[0]==n)
                { cout <<"IsFibo" <<endl;
                   flag=1;
                    break;} 
            }
            if (flag==0)
                cout << "IsNotFibo" <<endl;
        }









}
