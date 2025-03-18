/*
 * @lc app=leetcode.cn id=2043 lang=cpp
 *
 * [2043] 简易银行系统
 */

// @lc code=start
class Bank
{
    vector<long long> balances;
    int n;

public:
    Bank(vector<long long> &balance)
    {
        balances = balance;
        n = balance.size();
    }

    bool transfer(int account1, int account2, long long money)
    {
        int index = account1 - 1;
        if (account1 > n || account2 > n)
            return false;
        if (balances[index] < money)
            return false;
        else
        {
            balances[index] -= money;
            balances[account2 - 1] += money;
        }
        return true;
    }

    bool deposit(int account, long long money)
    {
        if (account > n)
            return false;
        balances[account - 1] += money;
        return true;
    }

    bool withdraw(int account, long long money)
    {
        int index = account - 1;
        if (account > n)
            return false;
        if (balances[index] < money)
            return false;
        else
        {
            balances[index] -= money;
        }
        return true;
    }
};

/**
 * Your Bank object will be instantiated and called as such:
 * Bank* obj = new Bank(balance);
 * bool param_1 = obj->transfer(account1,account2,money);
 * bool param_2 = obj->deposit(account,money);
 * bool param_3 = obj->withdraw(account,money);
 */
// @lc code=end
