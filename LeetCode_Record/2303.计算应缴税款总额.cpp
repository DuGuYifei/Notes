#include <vector>
using namespace std;

class Solution {
public:
    double calculateTax(vector<vector<int>>& brackets, int income){
        double ans = 0;
        int prevUpper = 0;
        for(auto&& i : brackets){
            if(income < i[0]){
                return (ans + (income - prevUpper) * i[1]) / 100;
            }
            ans += (i[0] - prevUpper) * i[1];
            prevUpper = i[0];
        }
        return ans / 100;
    }
};