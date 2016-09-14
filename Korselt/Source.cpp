#pragma comment(linker, "/STACK:100000000")
#define _SCL_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#pragma GCC ostarimize("O500")
#define _USE_MATH_DEFINES
#include <unordered_map>
#include <unordered_set>
#include <functional>
#include <algorithm>
#include <memory.h>
#include <iostream>
#include <iterator>
#include <ostream>
#include <iomanip>
#include <cstring>
#include <sstream>
#include <cassert>
#include <cstdlib>
#include <istream>
#include <fstream>
#include <climits>
#include <complex>
#include <memory>
#include <string>
#include <bitset>
#include <vector>
#include <cstdio>
#include <ctime>
#include <cmath>
#include <deque>
#include <queue>
#include <stack>
#include <set>
#include <map>

using namespace std;

typedef long long ll;
typedef long double ld;
typedef unsigned long long ull;
typedef complex <ld> cd;

const bool db = false;

#define fs first
#define sd second
#define mp make_pair
#define pb push_back
#define ppb pop_back

#define inf 1000000007
#define nmax 100100
#define mmax 10100
#define eps 1e-12

ull gcd(ull a, ull b)
{
	while (a && b)
	{
		if (a >= b)
			a %= b;
		else b %= a;
	}
	return a + b;
}

ull modular_mul(ull left_side, ull right_side, ull modulus)
{
	if (!left_side || !right_side)
		return 0;
	if (left_side & 1)
		return (right_side + modular_mul(left_side - 1, right_side, modulus)) % modulus;
	return (modular_mul(left_side / 2, right_side, modulus) * 2) % modulus;
}

ull modular_pow(ull base, ull exponent, ull modulus)
{
	ull result = 1;
	while (exponent > 0)
	{
		if (exponent & 1)
			result = modular_mul(result, base, modulus);
		exponent = exponent >> 1;
		base = modular_mul(base, base, modulus);
	}
	return result;
}

int cnt = 0;

ull PollardRho(ull n)
{
	srand(time(NULL));
	cnt++;
	if (cnt == 20)
		return n;
	if (n == 1)
		return n;
	if (n % 2 == 0) 
		return 2;
	ull x = (rand() % (n - 2)) + 2, y = x;
	ull c = (rand() % (n - 1)) + 1, d = 1;
	ull cnt_max_local = min(ull(sqrt(ull(sqrt(n)))), ull(mmax)), cnt_local = 0;
	while (d == 1 && cnt_local < cnt_max_local)
	{
		x = (modular_pow(x, 2, n) + c + n) % n;
		y = (modular_pow(y, 2, n) + c + n) % n;
		y = (modular_pow(y, 2, n) + c + n) % n;
		d = gcd(llabs(x - y), n);
		if (d == n)
			return PollardRho(n);
		cnt_local++;
	}
	if (cnt_local == cnt_max_local)
		return n;
	return d;
}

vector<ull> divisor, better_divisor;

bool check_Korselt(ull Korselt)
{
	if (Korselt < 2 || !(Korselt % 2) || divisor.size() == 1)
		return false;
	for (int i = 0; i<int(divisor.size()); i++)
	{
		if (!(Korselt%ull(divisor[i] * divisor[i])) || (Korselt - 1) % (divisor[i] - 1))
			return false;
	}
	return true;
}

int lowest_prime[nmax + 1];

vector<int> prime;

void Erastofena()
{
	for (int i = 2; i < nmax; ++i)
	{
		if (lowest_prime[i] == 0)
		{
			lowest_prime[i] = i;
			prime.push_back(i);
		}
		for (int j = 0; j < (int)prime.size() && prime[j] <= lowest_prime[i] && i*prime[j] < nmax; ++j)
			lowest_prime[i * prime[j]] = prime[j];
	}
}

bool check_simplicity(vector<ull> div)
{
	for (int i = 0; i<int(div.size()); i++)
	{
		for (int j = 0; j<int(prime.size()); j++)
			if (!(div[i] % ull(prime[j])) && div[i] != prime[j])
				return false;
	}
	return true;
}

void find_all_divisors(ull Korselt_num)
{
	ull div;
	divisor.clear();
	divisor.push_back(Korselt_num);
	while (true)
	{
		sort(divisor.begin(), divisor.end());
		better_divisor.clear();
		for (int i = 0; i<int(divisor.size()); i++)
		{
			Korselt_num = divisor[i];
			while (Korselt_num != 1)
			{
				cnt = 0;
				div = PollardRho(Korselt_num);
				if ((Korselt_num / div) != 1)
					div = min(div, Korselt_num / div);
				if (div != 1)
				{
					better_divisor.push_back(div);
					while (Korselt_num % div == 0)
						Korselt_num /= div;
				}
			}
		}
		if (better_divisor.size() > divisor.size())
			divisor = better_divisor;
		else if (check_simplicity(divisor))
			break;
	}
}

int main()
{
#ifdef Ahoma
	freopen("input.txt", "r", stdin); freopen("output.txt", "w", stdout);
#endif
	ull Korselt_num;
	Erastofena();
	while (cin >> Korselt_num)
	{
		find_all_divisors(Korselt_num);
		if (check_Korselt(Korselt_num))
			puts("TRUE\nIt's a Korselt num!");
		else puts("FALSE\nIt isn't a Korselt num!");
	}
	return 0;
}