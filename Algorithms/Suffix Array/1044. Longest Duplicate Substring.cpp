//https://www.geeksforgeeks.org/suffix-array-set-1-introduction/
//https://www.geeksforgeeks.org/%C2%AD%C2%ADkasais-algorithm-for-construction-of-lcp-array-from-suffix-array/
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

struct suffix {
	int index;
	int rank[2];
	suffix() : index(0) {};
};

bool cmp(const suffix& a, const suffix& b) {
	return (a.rank[0] == b.rank[0]) ? (a.rank[1] < b.rank[1]) : (a.rank[0] < b.rank[0]);
};


vector<int> buildSuffixArray(const string& txt) {
	int size = txt.size();
	suffix suffixes[size];
	for(int i = 0; i < size; i++)
	{
		suffixes[i].index = i;
		suffixes[i].rank[0] = txt[i];
		suffixes[i].rank[1] = ((i + 1) < size) ? txt[i + 1] : -1;
	}
	sort(suffixes, suffixes + size, cmp);
	int index[size];
	for(int k = 4; k < 2 * size; k *= 2)
	{
		int rank = 0;
		int preRank = suffixes[0].rank[0];
		suffixes[0].rank[0] = rank;
		index[suffixes[0].index] = 0;
		
		for(int i = 1; i < size; i++)
		{
			if(suffixes[i].rank[0] == preRank && suffixes[i].rank[1] == suffixes[i - 1].rank[1])
			{
				suffixes[i].rank[0] = rank;
			}
			else
			{
				preRank = suffixes[i].rank[0];
				suffixes[i].rank[0] = ++rank;
			}
			index[suffixes[i].index] = i;
		}

		for(int i = 0; i < size; i++)
		{
			int next = suffixes[i].index + k / 2;
			suffixes[i].rank[1] = next < size ? suffixes[index[next]].rank[0] : -1;
		}
		sort(suffixes, suffixes + size, cmp);
	}

	vector<int> suffixArr(size);
	for(int i = 0; i < size; i++)
	{
		suffixArr[i] = suffixes[i].index;
	}
	return suffixArr;
}

//kasai's algorithm
vector<int> buildLCP(const string& txt, const vector<int>& suffixArr) { // longest common prefix
	int size = suffixArr.size();
	vector<int> LCP(size);
	int invSuff[size];
	for(int i = 0; i < size; i++)
	{
		invSuff[suffixArr[i]] = i;	
	}

	int k = 0;
	for(int i = 0; i < size; i++)
	{
		if(invSuff[i] == size - 1)
		{
			k = 0;
			continue;
		}
		int j = suffixArr[invSuff[i] + 1];
		while(i + k < size && j + k < size && txt[i + k] == txt[j + k])
		{
			k++;
		}
		LCP[invSuff[i]] = k;
		if(k > 0) k--;
	}
	return LCP;
}

class Solution {
public:
    string longestDupSubstring(string S) {
		int size = S.size();
		vector<int> suffixArr = buildSuffixArray(S);
		vector<int> lcp = buildLCP(S, suffixArr);

		int start = 0;
		int Max = 0;
		
		for(int i = 0; i < size; i++)
		{
			if(lcp[i] > Max)
			{
				Max = lcp[i];
				start = suffixArr[i];
			}
		}

		return S.substr(start, Max);
    }
};

//Binary Search and Rabin-Karp(Rolling Hash)
class Solution {
public:
	Solution () {
		MOD = 1e9 + 7;//prime
		p = 113;//prime
		pinv = pow(p, MOD - 2, MOD); //the mod inverse of p(MOD should be prime), by FERMAT's little therorem
	}

    string longestDupSubstring(string S) {
		int size = S.size();
		int low = 0, high = size; //length of duplicated substring
		int res = -1;
		while(low < high)
		{
			int mid = (low + 1 + high) / 2;
			int pos = search(S, mid);
			if(pos == -1)
			{
				high = mid - 1;
			}
			else
			{
				low = mid;
				res = pos;
			}
		}
		return res == -1 ? "" : S.substr(res, low);
    }

private:
	long MOD;
	int p;
	int pinv;
	int search(string& S, int len) {
		if(len > S.size()) return -1;
		long hash = 0;
		long power = 1;
		for(int i = 0; i < len; i++)
		{
			hash = (hash + S[i] * power) % MOD;
			power = (power * p) % MOD;
		}
		unordered_map<long, int> seen; //in case of hash collision
		seen[hash] = 0;
		power = (power * pinv) % MOD;
		for(int i = len; i < S.size(); i++)
		{
			hash -= S[i - len];
			hash *= pinv;
			hash += S[i] * power;
			hash %= MOD;
			if(seen.count(hash) && S.substr(seen[hash], len) == S.substr(i - len + 1, len)) return i - len + 1; //there's still possibility of third hash collision. 
			seen[hash] = i - len + 1;
		}
		return -1;
	}

	int pow(int x, int y, int m) {
		if(y == 0) return 1;
		long p = pow(x, y / 2, m);
		p = (p * p) % m;
		return (y % 2 == 0) ? p : (p * x) % m;
	}
};
