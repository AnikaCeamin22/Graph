#include<bits/stdc++.h>
using namespace std;

class DisjointSet{
    vector<int>parent,ranked,sized;
public:

    DisjointSet(int n)
    {
        parent.resize(n+1);
        ranked.resize(n+1,0);
        sized.resize(n+1,1);
        for(int i=0; i<=n; i++) parent[i]=i;
    }
    int findUParent(int node)
    {
        if(node==parent[node]) return node;
        parent[node]=findUParent(parent[node]);
        return parent[node];
    }
    void unionByRank(int u, int v)
    {
        int pu=findUParent(u);
        int pv=findUParent(v);
        if(pu==pv) return;
        if(ranked[pu]<ranked[pv])
            parent[pu]=pv;
        else if(ranked[pu]>ranked[pv])
            parent[pv]=pu;
        else
        {
            parent[pv]=pu;
            ranked[pu]++;
        }
    }
    void unionBySize(int u, int v)
    {
        int pu=findUParent(u);
        int pv=findUParent(v);
        if(pu==pv) return;
        if(ranked[pu]<ranked[pv])
            parent[pu]=pv;
        if(sized[pu]<sized[pv])
        {
            parent[pu]=pv;
            sized[pv]+=sized[pu];
        }
        else
        {
            parent[pv]=pu;
            sized[pu]+=sized[pv];
        }
    }
};

void Solve()
{
    DisjointSet ds(7);
    ds.unionByRank(1,2);
    ds.unionByRank(2,3);
    ds.unionByRank(4,5);
    ds.unionByRank(6,7);
    ds.unionByRank(5,6);
    cout<<ds.findUParent(3)<<" = "<<ds.findUParent(6)<<endl;
    if(ds.findUParent(3)==ds.findUParent(7))
        cout<<"YES"<<endl;
    else cout<<"NO"<<endl;
    ds.unionByRank(3,7);
     if(ds.findUParent(3)==ds.findUParent(7))
        cout<<"YES"<<endl;
    else cout<<"NO"<<endl;
}

int main()
{
    int T=1;
   // cin>>T;
    while(T--)
    {
        Solve();
    }
    return 0;
}
