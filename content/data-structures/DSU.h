#pragma once 

struct DSU {
    vector<int> link;
    DSU(int n) : link(n, -1) {}
    int Find(int x) { return link[x] == -1 ? x : link[x] = Find(link[x]); }
};