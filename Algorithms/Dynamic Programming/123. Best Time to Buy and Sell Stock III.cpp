class Solution {
public:
	int maxProfit(vector<int>& prices)
	{
		if(prices.size() == 0) return 0;
		int tn = 2;
		int maxPro = 0;
		vector<vector<int>> dp(tn+1, vector<int>(prices.size(), 0));
		for(int k = 1; k <= tn; k++)
		{
			int minBuy = prices[0] - dp[k-1][0];
			for(int i = 1; i < prices.size(); i++)
			{
				dp[k][i] = max(dp[k][i-1], prices[i] - minBuy);
				minBuy = min(minBuy, prices[i] - dp[k-1][i]);
			}
		}
		return dp[tn][prices.size()-1];
	}
};

class Solution {
public:
    int maxProfit(vector<int>& prices)
	{
		if(prices.size() == 0) return 0;
		int tn = 2; //transation number
		vector<int> dp(tn + 1, 0);
		vector<int> Min(tn + 1, prices[0]);
		for(int i = 1; i < prices.size(); i++)
		{
			for(int k = 1; k <= tn; k++)
			{
				Min[k] = min(Min[k], prices[i] - dp[k-1]);
				dp[k] = max(dp[k], prices[i] - Min[k]);
			}
		}
		return dp[tn];
    }
};

class Solution {
public:
	int maxProfit(vector<int>& prices)
	{
		int buy1 = INT_MAX, buy2 = INT_MAX;
		int sell1 = 0, sell2 = 0;
		for(int i = 0; i < prices.size(); i++)
		{
			buy1 = min(buy1, prices[i]);
			sell1 = max(sell1, prices[i] - buy1);
			buy2 = min(buy2, prices[i] - sell1);
			sell2 = max(sell2, prices[i] - buy2);
		}
		return sell2;
	}	
};
