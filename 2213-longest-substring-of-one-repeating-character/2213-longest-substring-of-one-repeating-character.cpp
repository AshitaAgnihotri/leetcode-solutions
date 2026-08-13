class Solution{
public:
    struct Node{
        char lc,rc;
        int len,pref,suff,best;
        Node():lc('#'),rc('#'),len(0),pref(0),suff(0),best(0){}
        Node(char c):lc(c),rc(c),len(1),pref(1),suff(1),best(1){}
    };
    vector<Node>seg;
    string s;
    Node merge(Node a,Node b){
        if(a.len==0)return b;
        if(b.len==0)return a;
        Node r;
        r.len=a.len+b.len;
        r.lc=a.lc;
        r.rc=b.rc;
        r.pref=a.pref;
        r.suff=b.suff;
        r.best=max(a.best,b.best);
        if(a.pref==a.len&&a.rc==b.lc)r.pref=a.len+b.pref;
        if(b.suff==b.len&&a.rc==b.lc)r.suff=b.len+a.suff;
        if(a.rc==b.lc)r.best=max(r.best,a.suff+b.pref);
        return r;
    }
    void build(int p,int l,int r){
        if(l==r){
            seg[p]=Node(s[l]);
            return;
        }
        int m=(l+r)/2;
        build(2*p,l,m);
        build(2*p+1,m+1,r);
        seg[p]=merge(seg[2*p],seg[2*p+1]);
    }
    void update(int p,int l,int r,int idx,char c){
        if(l==r){
            seg[p]=Node(c);
            return;
        }
        int m=(l+r)/2;
        if(idx<=m)update(2*p,l,m,idx,c);
        else update(2*p+1,m+1,r,idx,c);
        seg[p]=merge(seg[2*p],seg[2*p+1]);
    }
    vector<int>longestRepeating(string word,string queryCharacters,vector<int>&queryIndices){
        s=word;
        int n=s.size();
        seg.resize(4*n+5);
        build(1,0,n-1);
        vector<int>ans;
        for(int i=0;i<queryCharacters.size();i++){
            update(1,0,n-1,queryIndices[i],queryCharacters[i]);
            ans.push_back(seg[1].best);
        }
        return ans;
    }
};