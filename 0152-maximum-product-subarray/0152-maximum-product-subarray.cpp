class Solution {
public:
    int maxProduct(vector<int>& nums) {
        int maxi=nums[0];
        for(int i=0;i<nums.size();i++){
           int prod=1;
            for(int j=i;j<nums.size();j++){
                prod*=nums[j];
                maxi=max(maxi,prod);
            }
        }
        return maxi;
    }
};