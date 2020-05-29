//
//   “Daḷhaṃ sikkhatha santiyā.” - Utthana Sutta (Sutta Nipata)
//   "Life is a manifestation of where your energy is flowing" - Dandapani
//    Sāket Sāumyā
//    MAY 29 2020
//

#include<bits/stdc++.h>
#include <string> 
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
// Its a range query that is in the range where the price is greter than Y and a point update of -1 since we have to remove 
// one occuerence of the particular item i.e simple / normal implementation

ll bit[N];
void update(ll idx, ll val){
		    while(idx <= n){
			        bit[idx] += val;
			        idx += idx & -idx;
		    }
}

ll query(ll idx){
            ll sum = 0;
		    while(idx > 0){
			        sum += bit[idx];
			        idx -= idx & -idx;
		    }
            return sum;
}

string s;
char c1;

signed  main(){
            
            ios_base::sync_with_stdio(false);
            cin.tie(nullptr);cout.tie(nullptr);
            
            cin >> t;
            for (int i=1; i<=t; ++i){
                    cin >> s >>  n;
                    mp[s] = n;
                    arr[s] = 0;
            }

            cin >> y;
            while (y-- ){
                    cin >> c1;
                    if (c1 == '+'){
                            cin >> s;
                            arr[s]++;
                            update(mp[s], 1);
                    }
                    else if (c1 == '-'){
                            cin >> s;
                            if (arr[s] > 0){
                                    arr[s]--;
                                    update(mp[s], -1);
                            }
                    }
                    else {
                            cin >> a;
                            cout << (query(N-1) - query(a)) << endl;
                            for (int i=0; i<=10; ++i)
                                what_is(bit[i]);
                    }


            
            }

            


























































}       
       
 
 
       
       
       
       
