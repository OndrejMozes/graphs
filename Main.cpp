#include "Graph.h"

int main() {
	DirectedGraph<std::string, std::string> sneed;
	sneed.import("input.txt");
	DirectedGraph<std::string, std::string> bar;
	bar = std::move(sneed);
	//std::cout << sneed << std::endl;
	//sneed.edges().printMatrix();
	std::cout << std::endl << std::endl;
	std::cout << bar << std::endl;
	bar.edges().printMatrix();
	return 0;
}