// y^e mod n =x 
#include <bits/stdc++.h>
#define ll unsigned long long 
using namespace std;

char power(ll, ll, ll);
string multiply(string, string);
ll mod(string, ll);
ll gcdExtended(ll , ll, ll*, ll*);
ll gcdd(ll, ll);
void factorize(ll, ll*, ll*);
void split(string, char);

string LongToString(ll);
ll StringToLong(string);

string xx, ress, temp, strings[2000]; 
int s_num;
  
// Driver Code
int main()
{
	ll n, e, Q, p, q, e_inverse, t;
	string message;
	ll mtoi[2000];

	cin>>n;
	cin>>e;
	cin>>message;
	
	factorize(n, &p, &q);
	Q=(p-1)*(q-1);
	e_inverse = gcdd(e, Q);
	
	char seperator = ',';
    split(message, seperator);  

    for (int i = 0; i < s_num; i++)
		mtoi[i] = StringToLong(strings[i]);
    
    // Reduce the number n_inverse to a small number
	// using Fermat Little
	ll remainderE = e_inverse % (n-1);

	for(int i = 0; i < s_num; i++)
		cout<<power(mtoi[i], remainderE, n);
	return 0;
}

// Function to find power
char power(ll x, ll y, ll p)
{
	ll res = 1; // Initialize result
	// Update x if it is more than or
	// equal to p
	x = x % p;

	while (y > 0) {
		if(x>2147483647 || res>2147483647)
		{
			xx = LongToString(x);
			ress = LongToString(res);
			
			if (y & 1)
			res = mod(multiply(ress, xx), p);

			// y must be even now
			y = y >> 1; // y = y/2
		
			x = mod(multiply(xx, xx), p);
			// If y is odd, multiply x
			// with the result
		}
		else
		{
			if (y & 1)
				res = (res * x) % p;

			// y must be even now
			y = y >> 1; // y = y/2
		
			x = (x * x) % p;
		}
	}
	char dems;
	dems = res;
	return dems;
}

string multiply(string nums1, string nums2) {
   int n = nums1.size();
   int m = nums2.size();
   string ans(n + m, '0');
   for(int i = n - 1; i>=0; i--){
      for(int j = m - 1; j >= 0; j--){
         int p = (nums1[i] - '0') * (nums2[j] - '0') + (ans[i + j + 1] - '0');
         ans[i+j+1] = p % 10 + '0';
         ans[i+j] += p / 10 ;
      }
   }
   for(int i = 0; i < m + n; i++){
      if(ans[i] !='0')
	  	return ans.substr(i);
   }
   return "0";
}

ll mod(string num, ll a)
{
    // Initialize result
    ll res = 0;
 	
    // One by one process all digits of 'num'
    for (int i = 0; i < num.length(); i++)
        res = (res * 10 + num[i] - '0') % a;
 
    return res;
}

// create custom split() function  
void split(string str, char seperator)  
{  
    int currIndex = 0, i = 0;  
    int startIndex = 0, endIndex = 0;  
    while (i <= str.length())  
    {  
        if (str[i] == seperator || i == str.length())  
        {  
            endIndex = i;  
            string subStr = "";  
            subStr.append(str, startIndex, endIndex - startIndex);  
            strings[currIndex] = subStr;  
            s_num = currIndex + 1;
            currIndex += 1;  
            startIndex = endIndex + 1;  
        }  
        i++;  
    }     
}  
void factorize(ll n, ll *p, ll *q)
{
    int count = 0;
 	bool p_q_value = false;
    // count the number of times 2 divides
    while (!(n % 2)) {
        n >>= 1; // equivalent to n=n/2;
        count++;
    }
 
    // if 2 divides it
    if (count)
    {
		*p=2,*q=n/2;
		return;
	}
        
 
    // check for all the possible numbers that can
    // divide it
    for (ll i = 3; i <= sqrt(n); i += 2) {
        count = 0;
        while (n % i == 0) {
            count++;
            n = n / i; 
           	*p=i;
        }
    }
    // if n at the end is a prime number.
    if (n > 2)
        *q=n;
}
ll gcdExtended(ll a, ll b, ll *x, ll *y)
{
    // Base Case
    if (a == 0)
    {
        *x = 0;
        *y = 1;
        return b;
    }
 
    ll x1, y1; // To store results of recursive call
    ll gcd = gcdExtended(b%a, a, &x1, &y1);
 
    // Update x and y using results of
    // recursive call
    *x = y1 - (b/a) * x1;
    *y = x1;
 
    return gcd;
}

string LongToString(ll long_num)
{
    stack<char> stringStack;
    string signValue = "";
  
    // if long number is negative store the negative sign to
    // the signValue variable
    if (long_num < 0) {
        signValue = "-";
        long_num = -long_num;
    }
  
    // while number is greate than 0, get last digit from it
    // and convert it to character by adding '0' to it, and
    // push to the stack.
    while (long_num > 0) {
        char convertedDigit = long_num % 10 + '0';
        stringStack.push(convertedDigit);
        long_num /= 10;
    }
  
    string long_to_string = "";
  
    // while stack is not empty pop the character one by one
    // and append to the resultant string.
    while (!stringStack.empty()) {
        long_to_string += stringStack.top();
        stringStack.pop();
    }
  
    // return the resulatant string value by appending
    // singValue to it.
    return signValue + long_to_string;
}
ll StringToLong(string ss)
{
	ll long_num=0;
	
	for(int i=0;i<ss.length();i++)
		long_num = long_num*10 + ss[i] - '0';
	
	return long_num;
}
ll gcdd(ll a, ll b){
	long long int xa=1, ya=0, xb=0, yb=1, cur=a/b;
	//ax-by
	//a-=cur*b;
	while(a!=1){
		a-=cur*b;
		xa+=xb*cur*-1;
		ya+=yb*cur*-1;
	
		if(a==1){
			break;
		}
		cur=b/a;
		b-=cur*a;
		//printf("a=%d, b=%d\n", a, b);
		xb+=cur*xa*-1;
		yb+=ya*cur*-1;
		cur=a/b;
		if(b==1){
			cur=a-1;
			xa+=xb*cur*-1;
			ya+=yb*cur*-1;
			break;
		}
	}
	return xa;
}
