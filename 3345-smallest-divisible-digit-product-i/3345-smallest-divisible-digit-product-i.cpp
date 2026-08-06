class Solution {
public:
    int prod(int n){
        int product = 1;
        while(n>0){
            int lastDig = n % 10;
            product *= lastDig;
            n /= 10;
        }
        return product;
    }
    int smallestNumber(int n, int t) {
        while(true){
            if(prod(n) % t == 0){
                return n;
            }
            n++;
        }
    }
};