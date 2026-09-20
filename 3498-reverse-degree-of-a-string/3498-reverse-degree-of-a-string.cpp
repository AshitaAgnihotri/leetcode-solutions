class Solution {
public:
    int reverseDegree(string s) {
        int reverseDegree = 0;
        int prod = 1;
        for(int i=0 ; i<s.size() ; i++){
            int revIndex = 'z' - s[i] + 1;
            prod = revIndex * (i+1);
            reverseDegree += prod;
        }
        return reverseDegree;
    }
};