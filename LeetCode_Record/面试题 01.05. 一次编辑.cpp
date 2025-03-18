#include <string>
using namespace std;
class Solution {
public:
    bool oneEditAway(string first, string second) {
        if(first == second)
            return true;
        int fn = first.size();
        int sn = second.size();
        if(fn == sn)
        {
            int i = 0;
            while(i<sn)
            {
                if(first[i]!=second[i])
                {
                    i++;
                    while(i<fn)
                    {
                        if(first[i]!=second[i])
                            return false;
                        i++;
                    }
                    return true;
                }
                i++;
            }
        }
        if(fn - sn == 1)
        {
            int i = 0;
            while(i<sn)
            {
                if(first[i]!=second[i])
                {
                    i++;
                    while(i<fn)
                    {
                        if(first[i]!=second[i-1])
                            return false;
                        i++;
                    }
                    return true;
                }
                i++;
            }
            return true;
        }
        if(sn - fn == 1)
        {
            int i = 0;
            while(i<fn)
            {
                if(first[i]!=second[i])
                {
                    i++;
                    while(i<sn)
                    {
                        if(first[i-1]!=second[i])
                            return false;
                        i++;
                    }
                    return true;
                }
                i++;
            }
            return true;
        }

        return false;
    }
};