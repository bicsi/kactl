/**
 * Author: 
 * Source: Topcoder
 * Description: Computes Gomory-Hu tree of a graph
 * Time: O(V) calls of flow algorithm
 * Status: works
 */
#pragma once
void GomoryHu() {
    int parent[n]; //initialized to 0
    int answer[n][n]; //initialize this one to infinity
    for(int i=1;i<n;++i){
        //Compute the minimum cut between i and parent[i].
        //Let the i-side of the min cut be S, and the value of the min-cut be F
        for (int j=i+1;j<n;++j)
            if ((j is in S) && parent[j]==parent[i])
                parent[j]=i;
        answer[i][parent[i]]=answer[parent[i]][i]=F;
        for (int j=0;j<i;++j)
            answer[i][j]=answer[j][i]=min(F,answer[parent[i]][j]);
    }
}
