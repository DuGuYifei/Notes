#include <unordered_map>
#include <string>
using namespace std;
/*
 * @lc app=leetcode.cn id=535 lang=cpp
 *
 * [535] TinyURL 的加密与解密
 */

// @lc code=start
class Solution {
public:
    unordered_map<int,string> db;
    int id = 0;
    // Encodes a URL to a shortened URL.
    string encode(string longUrl) {
        string res = to_string(id);
        db[id++] = longUrl;
        return "http://tinyurl.com/" + res;
    }

    // Decodes a shortened URL to its original URL.
    string decode(string shortUrl) {
        int position = shortUrl.rfind('/') + 1;

        return db[stoi(shortUrl.substr(position,shortUrl.size()-position))];
    }
};

// Your Solution object will be instantiated and called as such:
// Solution solution;
// solution.decode(solution.encode(url));
// @lc code=end

