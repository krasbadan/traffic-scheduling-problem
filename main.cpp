#include <iostream>
#include <fstream>//ƒл€ тестов

#include <vector>
#include <list>

class Graph
{
private:
	struct node {
		Graph* parentGraph;
		const int from, to;

		int cost, capacity;
		int traffic;

		//ƒобавил ссылку на родител€, чтобы можно было к его пол€м обращатьс€
		node(Graph* parent, int f, int t, int c, int cap, int tr) 
			: parentGraph(parent), from(f), to(t), cost(c), capacity(cap), traffic(tr) {}

		void printNode() {
			std::cout << "\tlink (" << from << ", " << to << "):";
			std::cout << "\tcost: " << cost;
			std::cout << "\ttraffic: " << traffic << "/" << capacity * parentGraph->tau / 100.0;

			double congestion_limit = capacity * parentGraph->tau / 100.0;
			if (traffic > congestion_limit)
				std::cout << "\nCONGESTION!!!\n";
		}
	};

public:
	// Graph implementation via adjecency list
	std::vector<std::list<node>> G; 

	int tau, K;
	int n, m;

	Graph() : tau(0), K(0), n(0), m(0){}

	void CreateGraph()
	{
		std::cin >> n >> m >> tau >> K;
		std::cout << "n = " << n << " m = " << m << " t = " << tau << " K = " << K << '\n';

		G = std::vector<std::list<node>>(n);

		for (int i = 0; i < m; i++) {
			int u, v, cost, capacity, traffic_uv, traffic_vu;

			std::cin >> u >> v >> cost >> capacity >> traffic_uv >> traffic_vu;
			u--; v--; // Switch to 0-indexation (need to switch back when printing actual result)

			G[u].push_back(node(this, u, v, cost, capacity, traffic_uv));
			G[v].push_back(node(this, v, u, cost, capacity, traffic_vu));

			if (traffic_uv >= capacity * tau/100.0) {
				std::cout << "Congestion at link (" << u << ", " << v << "): " 
					<< traffic_uv << "/" << capacity * tau/100.0 << '\n';
			}
			if (traffic_vu >= capacity * tau/100.0) {
				std::cout << "Congestion at link (" << v << ", " << u << "): " 
					<< traffic_vu << "/" << capacity * tau/100.0 << '\n';
			}
		}
	}
	void CreateGraph(std::fstream& file)
	{
		file >> n >> m >> tau >> K;
		std::cout << "n = " << n << " m = " << m << " t = " << tau << " K = " << K << '\n';

		G = std::vector<std::list<node>>(n);

		for (int i = 0; i < m; i++) {
			int u, v, cost, capacity, traffic_uv, traffic_vu;

			file >> u >> v >> cost >> capacity >> traffic_uv >> traffic_vu;
			u--; v--; // Switch to 0-indexation (need to switch back when printing actual result)

			G[u].push_back(node(this, u, v, cost, capacity, traffic_uv));
			G[v].push_back(node(this, v, u, cost, capacity, traffic_vu));

			if (traffic_uv >= capacity * tau/100.0) {
				std::cout << "Congestion at link (" << u << ", " << v << "): " 
					<< traffic_uv << "/" << capacity * tau/100.0 << '\n';
			}
			if (traffic_vu >= capacity * tau/100.0) {
				std::cout << "Congestion at link (" << v << ", " << u << "): " 
					<< traffic_vu << "/" << capacity * tau/100.0 << '\n';
			}
		}
	}

	void printGraph()
	{
		// Print graph
		for (int i = 0; i < n; i++) {
			std::cout << std::endl << "Node " << i << ":" << std::endl;
			for (Graph::node& edge : G[i]) {
				edge.printNode();
			}
			if (!G[i].size()) std::cout << "NO LINKS" << std::endl;
		}
	}
};


int main() {
	std::fstream f("C:/Users/User/source/repos/traffic-scheduling-project/traffic-scheduling-project/file.txt");

	Graph graph;
	graph.CreateGraph(f);
	graph.printGraph();

	return 0;
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