#include<bits/stdc++.h>
using namespace std;

//NlogN
int N=2e5+9,LOG=19;
vector<vector<int>>par,gh;
vector<int>level;

void BinaryLifting(int node, int p=0){
    par[node][0]=p;   // set 1st parent
    level[node]=level[p]+1;   // compute hight

    for(int i=1; i<LOG; i++) par[node][i]=par[ par[node][i-1] ][i-1];

    for(auto child : gh[node])
        if(child!=p)
            BinaryLifting(child,node);

    return;
}

int Kth(int node, int k){
    if(level[node]<=k) return -1;

    for(int i=0; i<LOG; i++)
        if(k & (1<<i)) node=par[node][i];

    //if(node==0) return -1;
    return node;
}

int LCA(int u, int v){
    if(level[u]<level[v]) swap(u,v);

    int d=level[u]-level[v];
//    while(d>0){
//        int i=log2(d);
//        u=par[u][i];
//        d=d-(1<<i);  // d=d-(2^i)
//    }
//or
    u=Kth(u,d);

    if(u==v) return u;

    for(int k = LOG-1; k>=0; k--){
        if(par[u][k] != par[v][k]){
            u=par[u][k];  // find first not match ancesstor
            v=par[v][k];
        }
    }
    return par[u][0];  // LCA
}


int dist(int u, int v){
    int lca=LCA(u,v);
    return level[u]+level[v]-2*level[lca];
}

int32_t main() {
  int n,q;
  cin >> n >>q;

  N=n+1;
  LOG=log2(n)+1;
  gh.assign(N,{});
  par.assign(N, vector<int>(LOG,0));
  level.assign(N,0);

  for (int i = 1; i < n; i++) 
  {
    int u,v; cin >> u>>v ;
    gh[u].push_back(v);
    gh[v].push_back(u);
  }

  BinaryLifting(1);

  while (q--)
    {
    int u,v;
    cin>>u>>v;
    cout << dist(u,v) << '\n';
  }
  return 0;
}

