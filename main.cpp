#include <iostream>
#include <vector>
#include <list>

using std::cin;
using std::cout;

struct link {
    static inline int tau, K;
    const int from, to;
    const int cost, capacity;
    int traffic;

    link(int f, int t, int c, int cap, int tr) 
        : from(f), to(t), cost(c), capacity(cap), traffic(tr) {}

    void printLink() {
        cout << "    link (" << from << ", " << to << "):";
        cout << "    cost: " << cost;
        cout << "    traffic: " << traffic << "/" << capacity*tau/100.0;
        if (traffic > capacity*tau/100.0) cout << " (CONGESTION)";
        cout << std::endl;
    }
};

int main() {
    int n, m;
    cin >> n >> m >> link::tau >> link::K;
    cout << "n = " << n << " m = " << m << " t = " << link::tau << " K = " << link::K << std::endl;

    // Graph implementation via adjecency list
    std::vector<std::list<link>> G(n); 
    for (int i = 0; i < m; i++) {
        int u, v, cost, capacity, traffic_uv, traffic_vu;
        cin >> u >> v >> cost >> capacity >> traffic_uv >> traffic_vu;
        u--; v--; // Switch to 0-indexation (need to switch back when printing actual result)

        G[u].push_back(link(u, v, cost, capacity, traffic_uv));
        G[v].push_back(link(v, u, cost, capacity, traffic_vu));

        if (traffic_uv >= capacity*link::tau/100.0) {
            cout << "Congestion at link (" << u << ", " << v << "): " << traffic_uv << "/" << capacity*link::tau/100.0 << std::endl;
        }
        if (traffic_vu >= capacity*link::tau/100.0) {
            cout << "Congestion at link (" << v << ", " << u << "): " << traffic_vu << "/" << capacity*link::tau/100.0 << std::endl;
        }
    }

    // Print graph
    for (int i = 0; i < n; i++) {
        cout << std::endl << "Node " << i << ":" << std::endl;
        for (link& edge : G[i]) {
            edge.printLink( );
        }
        if (!G[i].size()) cout << "NO LINKS" << std::endl;
    }
}

/*
6 7 80 1
1 2 10 100 100 0
1 4 100 100 0 0
2 3 10 100 50 0
2 5 10 100 30 0
3 6 10 100 30 0
4 5 10 100 0 20
5 6 100 100 0 0
*/