#ifndef __GRAPH_H
#define __GRAPH_H

#include <utility>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include "Array.h"
#include "Exceptions.h"
#include "Nodes.h"
#include "Edges.h"


/// @file Graph.h
/// @brief Contains the Graph and Directed Graph and Undirected Graph 
///  and their member function definition


/// @brief The class representing the graph
/// @tparam NData The data associated with the Graph's nodes
/// @tparam EData The data associated with the Graph's edges
template <typename NData, typename EData>
class Graph {
public:
    /// @brief The empty graph constructor
    Graph();

    /// @brief The virtual destructor
    virtual ~Graph() = 0;

    /// @brief Get a reference to the nodes of the graph
    /// @return A reference to the graph's nodes
    Nodes<NData, EData>& nodes();

    /// @brief Get a reference to the edges of the graph
    /// @return A reference to the graph's edges
    Edges<NData, EData>& edges();

    /// @brief Prints the graph to the specified output stream
    /// @param os The output stream
    /// @exception InvalidStreamException If the output stream is not good
    void print(std::ostream& os = std::cout) const;

    /// @brief Prints the graph to a file with the specified filename
    /// @param filename The name of the file to print to
    /// @exception FileProcessingException If the output file is not good
    void print(const std::string& filename) const;

    /// @brief Imports the graph from the given input stream
    /// @param is The input stream   
    /// @exception InvalidStreamException If the input stream is not good
    void import(std::istream& is = std::cin);

    /// @brief Impots the graph from a file with the given filename
    /// @param filename The name of the file to import from
    /// @exception FileProcessingException If the input file is not good
    void import(const std::string& filename);

    /// @brief Copy constructor
    /// @param other The graph to copy from
    Graph(const Graph& other);

    /// @brief Move constructor
    /// @param other The graph to move
    Graph(Graph&& other) noexcept;

    /// @brief Copy assignment
    /// @param other The graph to copy
    /// @return The graph copied to
    Graph& operator=(const Graph& other);

    /// @brief Move assignment
    /// @param other The graph to move
    /// @return The graph moved to
    Graph& operator=(Graph&& other) noexcept;

    /// @brief Returns if the graph is or is not undirected
    /// @return True if the graph is undirected, false if it is directed
    virtual bool is_undirected() const = 0;

private:
    /// @brief The nodes of the graph
    Nodes<NData, EData> nodes_;

    /// @brief The edged og the grapg
    Edges<NData, EData> edges_;

    /// @brief Import a line from the specified input string stream
    /// @param iss The input string stream
    void import_line(std::istringstream& iss);

    /// @brief Import a node from the specified input string stream
    /// @param iss The input string stream
    void import_node(std::istringstream& iss);

    /// @brief Import an edge from the specified input string stream
    /// @param iss The input string stream
    void import_edge(std::istringstream& iss);

    /// @brief Parse an id from the specified input string stream with a given delimiter
    /// @param iss The input string stream
    /// @param delim The delimiter
    /// @return The id
    /// @exception ParsingException If the parsing of the id failed
    size_t parse_id(std::istringstream& iss, char delim);
};

/// @brief A directed graph
/// @tparam NData The data associated with the Graph's nodes
/// @tparam EData The data associated with the Graph's edges
template <typename NData, typename EData>
class DirectedGraph : public Graph<NData, EData> {
public:
    /// @brief The default constructor
    DirectedGraph() = default;
   
    /// @brief Copy constructor
    /// @param other The other directed graph to copy
    DirectedGraph(const DirectedGraph& other);

    /// @brief Returns if the graph is or is not undirected
    /// @return False
    bool is_undirected() const override;
};

/// @brief An undirected graph
/// @tparam NData The data associated with the Graph's nodes
/// @tparam EData The data associated with the Graph's edges
template <typename NData, typename EData>
class UndirectedGraph : public Graph<NData, EData> {
public:
    /// @brief The default constructor
    UndirectedGraph() = default;

    /// @brief Copy constructor
    /// @param other The other undirected graph to copy
    UndirectedGraph(const UndirectedGraph& other);

    /// @brief Returns if the graph is or is not undirected
    /// @return True
    bool is_undirected() const override;
};

/// @brief Print the given graph to the given output stream and return the same output stream
/// @tparam NData The data associated with the Graph's nodes
/// @tparam EData The data associated with the Graph's edges
/// @param os The output stream
/// @param graph The graph to print
/// @return The same output stream
template <typename NData, typename EData>
std::ostream& operator<<(std::ostream& os, const Graph<NData, EData>& graph) {
    graph.print(os);
    return os;
}

template <typename NData, typename EData>
Graph<NData, EData>::Graph() : nodes_(this), edges_(this) {}

template <typename NData, typename EData> 
Graph<NData, EData>::~Graph() {}

template <typename NData, typename EData>
inline bool DirectedGraph<NData, EData>::is_undirected() const {
    return false;
}

template <typename NData, typename EData>
inline bool UndirectedGraph<NData, EData>::is_undirected() const {
    return true;
}

template <typename NData, typename EData>
Nodes<NData, EData>& Graph<NData, EData>::nodes() {
    return nodes_;
}

template <typename NData, typename EData>
Edges<NData, EData>& Graph<NData, EData>::edges() {
    return edges_;
}

template <typename NData, typename EData>
void Graph<NData, EData>::print(std::ostream& os) const {
    if (!os.good()) throw InvalidStreamException::invalid_output_stream();
    nodes_.print(os);
    edges_.print(os);
}

template <typename NData, typename EData>
void Graph<NData, EData>::print(const std::string& filename) const {
    std::ofstream ofs(filename);
    if (!ofs.good()) throw FileProcessingException::unable_to_open_output_file(filename);
    print(ofs);
    ofs.close();
}

template <typename NData, typename EData>
size_t  Graph<NData, EData>::parse_id(std::istringstream& iss, char delim) {
    std::string id_string;
    std::getline(iss, id_string, delim);
    size_t p;
    size_t id;
    try {
        id = stoi(id_string, &p);
        if (p != id_string.size()) {
            throw ParsingException::failed_parsing_number();
        }
    }
    catch (...) {
        throw ParsingException::failed_parsing_number();
    }
    return id;
}

// assumes node prefix was already consumed
// also assumes correct format ($ID {$DATA})
template <typename NData, typename EData>
void Graph<NData, EData>::import_node(std::istringstream& iss) {
    if (!iss.good()) return;
    iss.get(); // skip (
    size_t id = parse_id(iss, ' ');
    iss.get(); // skip {
    std::string data_string;
    std::getline(iss, data_string, '}');
    NData data;
    std::istringstream(data_string) >> data;
    nodes_.add(id, data);
}

// assumes edge prefix was already consumed
// also assumes correct format ($SOURCE_ID)-[$EDGE_ID {$DATA}]->($TARGET_ID)
template <typename NData, typename EData>
void Graph<NData, EData>::import_edge(std::istringstream& iss) {
    if (!iss.good()) return;
    iss.get(); // skip (
    size_t source_id = parse_id(iss, ')');
    iss.get(); // skip -
    iss.get(); // skip [
    size_t edge_id = parse_id(iss, ' ');
    iss.get(); // skip {
    std::string data_string;
    std::getline(iss, data_string, '}');
    EData data;
    std::istringstream(data_string) >> data;
    iss.get(); // skip ]
    iss.get(); // skip -
    iss.get(); // skip >
    iss.get(); // skip (
    size_t target_id = parse_id(iss, ')');
    edges_.add(edge_id, source_id, target_id, data);
}

template <typename NData, typename EData>
void Graph<NData, EData>::import_line(std::istringstream& iss) {
    if (!iss.good()) return;
    const std::string node_prefix = "node";
    const std::string edge_prefix = "edge";
    const char prefix_delim = ' ';
    std::string prefix;
    std::getline(iss, prefix, prefix_delim);
    if (prefix == node_prefix) {
        import_node(iss);
    } else if (prefix == edge_prefix) {
        import_edge(iss);
    }
    // else do nothing
}

template <typename NData, typename EData>
void Graph<NData, EData>::import(std::istream& is) {
    if (!is.good()) throw InvalidStreamException::invalid_input_stream();
    std::string line;
    while (std::getline(is, line)) {
        std::istringstream iss(line);
        import_line(iss);
    }
}

template <typename NData, typename EData>
void Graph<NData, EData>::import(const std::string& filename) {
    std::ifstream ifs(filename);
    if (!ifs.good()) throw FileProcessingException::unable_to_open_input_file(filename);
    import(ifs);
    ifs.close();
}

template <typename NData, typename EData>
Graph<NData, EData>::Graph(const Graph<NData, EData>& other)
     : nodes_(other.nodes_, this), edges_(other.edges_, this) {} 


template <typename NData, typename EData>
UndirectedGraph<NData, EData>::UndirectedGraph(const UndirectedGraph<NData, EData>& other)
     : Graph<NData, EData>(other) {
    // we can't just copy the adjacency matrix, because the pointers would still point to other
    // we also can't construct it inside Graph's constructor, because we can't yet call
    // is_undirected() inside the parent constructor
    Graph<NData, EData>::edges().construct_adjacency_matrix();
}

template <typename NData, typename EData>
DirectedGraph<NData, EData>::DirectedGraph(const DirectedGraph<NData, EData>& other)
    : Graph<NData, EData>(other) {
    // we can't just copy the adjacency matrix, because the pointers would still point to other
    // we also can't construct it inside Graph's constructor, because we can't yet call
    // is_undirected() inside the parent constructor
    Graph<NData, EData>::edges().construct_adjacency_matrix();
}


template <typename NData, typename EData>
Graph<NData, EData>::Graph(Graph<NData, EData>&& other) noexcept : nodes_(this), edges_(this) {
    std::swap(nodes_, other.nodes_);
    std::swap(edges_, other.edges_);
}

template <typename NData, typename EData>
Graph<NData, EData>& Graph<NData, EData>::operator=(const Graph<NData, EData>& other) {
    nodes_ = other.nodes_;
    edges_ = other.edges_;
    return *this;
}

template <typename NData, typename EData>
Graph<NData, EData>& Graph<NData, EData>::operator=(Graph<NData, EData>&& other) noexcept {
    if (this != &other) {
        std::swap(nodes_, other.nodes_);
        std::swap(edges_, other.edges_);
    }
    return *this;
}


#endif