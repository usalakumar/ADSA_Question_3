#include <iostream>
#include <vector>
#include <climits>
using namespace std;
typedef long long ll;
const int MAXN = 1e4+5;

vector<int> adj[MAXN];
bool vis[MAXN], AP[MAXN];
int num_of_vertices, num_of_edges, currTime, disc[MAXN];
int low[MAXN];  // low[i] is the minimum of visited currTime of all vertices which are reachable from i.

void init() {
    currTime = 0;
    for(int i = 1; i <= num_of_vertices; i++) {
        adj[i].clear();
        vis[i] = false;
        AP[i] = false;
        disc[i] = 0;
        low[i] = INT_MAX;
    }
}

void dfs(int u, int parent) {
    vis[u] = true;
    disc[u] = low[u] = currTime + 1;
    int child = 0;
    for(auto v : adj[u]) {
        if(v == parent)
            continue;
        if(!vis[v]) {
            child = child + 1;
            currTime++;
            dfs(v, u);

            low[u] = min(low[u], low[v]);
            if(parent == -1 && child > 1)
                AP[u] = true;          
            if(parent != -1 && low[v] >= disc[u])
                AP[u] = true;
        } else {
            low[u] = min(low[u], disc[v]);
        }
    }
}

int main() {
    cout << "Enter number of vertices : ";
    cin >> num_of_vertices;
    cout << "Enter number of edges : ";
    cin >> num_of_edges;

    init();
    int i = 0;
    for(i = 0; i < num_of_edges; i++) {
        int a, b;
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    dfs(1, -1); //start from any random vertex, make its parent -1.
    cout << "Articulation point : ";
    for (i = 1; i <= num_of_vertices; i++) {
        if(AP[i]) cout << i << "\t";
    }
    cout << "\n";
    return 0;
}
