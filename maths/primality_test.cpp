

// Uses the fact that a composite number has a factor less than or equal to sqrt(n)
bool is_prime(int n){
            for(int i=2; i*i<=n; i++)
                    if (n % i == 0)
                        return false;
            return true;
}
/*    FERMET LITTLE THEOREM ( Modified)
 *  Uses the fact that if p is a prime then:
          a^p-a  is divisible by p             (1<a<=p)
    
   If a^p -a is not divisible by p, its for sure a composite number.
            (Concept of FERMET LIARS AND WITNESSES AND CARMICHAEL NUMBERS)

*/
// How (a^p-a)%p==0 is same as a^(p-1)=1 mod p(Different versions of FLT)??

/*  If (a^p -a ) is divisible by p, it means that Rem(a^p/p) == Rem(a/p)
    Also, a^(p-1) = 1 mod p(Fermet little theorem) 
          Multiplying by a:
            a^p = a mod p
            Rem(a^p/p) == Rem(a/p)
*/

bool  probablyPrimeFermet(int n, int iter=5){
            if (n < 4)
                    return n==2 || n==3;
            for (int i=0;i<iter;i++){
                    int a = 2 + rand() % (n-3);
                    if (binpower(a,n-1,n) != 1)
                        return false;
            }
            return true;
}

//MILER RABIN TEST
/* Taken from Wikipedia
Special cases- (No use of random int)
if n < 2,047, it is enough to test a = 2;
if n < 1,373,653, it is enough to test a = 2 and 3;
if n < 9,080,191, it is enough to test a = 31 and 73;
if n < 25,326,001, it is enough to test a = 2, 3, and 5;
if n < 4,759,123,141, it is enough to test a = 2, 7, and 61;
if n < 1,122,004,669,633, it is enough to test a = 2, 13, 23, and 1662803;
if n < 2,152,302,898,747, it is enough to test a = 2, 3, 5, 7, and 11;
if n < 3,474,749,660,383, it is enough to test a = 2, 3, 5, 7, 11, and 13;
if n < 341,550,071,728,321, it is enough to test a = 2, 3, 5, 7, 11, 13, and 17.
*/

//(a*b)%m for a,b,m<=10^18
long long mulmod(long long a,long long b, long long MOD) {
            long long q=(long long)(((long double)a*(long double)b)/(long double)MOD);
            long long r=a*b-q*MOD;
            if (r>MOD) r %= MOD;
            if (r<0) r += MOD;
            return r;
}

//(a^b)%m in log(b)
long long power(long long b, long long n, long long mod) {
            long long x=1, p=b;
            while(n) {
                    if(n&1) x = mulmod(x, p, mod);
                            p = mulmod(p, p, mod);
                            n >>= 1;
            }
            return x;
}

bool rabin_miller(long long p) {
            if (p < 2) return false;
            if (p != 2 && p % 2 == 0) return false;
            if (p < 8) return true;
            long long s = p-1, val = p-1, a, m, temp;
            
            while (s % 2 == 0) s >>= 1;
            for (int i = 0; i < 3; ++i) {
                    a = 1ll*rand()%val + 1ll;
                    temp = s;
                    m = power(a, temp, p);
                    while (temp != (p-1) && m != 1 && m != (p-1)) {
                            m = mulmod(m, m, p);
                            temp <<= 1;
                    }
                    if (m != (p-1) && temp % 2 == 0) return false;
            }
            return true;
}












