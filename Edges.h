#ifndef __EDGES_H
#define __EDGES_H

#include <utility>
#include "Graph.h"
#include "Edge.h"


/// @file Edges.h
/// @brief Contains the Edges class, its Request class used for the [] operator 
///        and their member function definitions


/// @brief The Edges of the Graph
/// @tparam NData The data associated with the Graph's nodes
/// @tparam EData The data associated with the Graph's edges
template <typename NData, typename EData>
class Edges {
private:
    /// @brief A pointer to the graph these edges belong to
    Graph<NData, EData>* graph_;

    /// @brief Grows adjacency matrix by one new node, with no new edges
    /// @exception UnavailableMemoryException If there isn't enough memory to grow the matrix
    void grow_adjacency_matrix();

    /// @brief The actual internal storage of the edges themselves
    my_array::Array<Edge<NData, EData>> edges_;

    /// @brief The adjacency matrix of the graph,
    /// [x][y] points to the edge from x to y if it exists, nullptr otherwise
    std::vector<std::vector<Edge<NData, EData>*>> adjacency_matrix_;

    friend Nodes<NData, EData>;
    class Request;

public:
    /// @brief Constructs the Edges for a Graph
    /// @param graph A pointer to the Graph to construct the edges for
    Edges(Graph<NData, EData>* graph);

    /// @brief Prints the edges to the specified output stream
    /// @param os The output stream
    void print(std::ostream& os = std::cout) const;

    /// @brief Prints the adjacency matrix to the specified output stream
    /// @param os The output stream
    void printMatrix(std::ostream& os = std::cout) const;

    /// @brief Add an Edge
    /// @param id The id of the edge to add (should be equal to the size of the edges)
    /// @param source The id of the source node of the edge to add
    /// @param target The id of the target node of the edge to add
    /// @param data The edge data of the edge to add
    /// @return A reference to the Edge that was just created and added to the Edges
    /// @exception InvalidIdentifierException If attempting to add an edge with an invalid id
    ///  (an invalid id is an id higher than the size of the edges)
    /// @exception ConflictingItemException If attempting to add an edge with a conflicting id
    ///  (a conflicting id and is id lower than the size of the edges)
    /// @exception NonexistingItemException If attempting to ad an edge between nodes that do not 
    ///  exist
    /// @exception ConflictingItemException If attempting to ad an edge between node that already
    ///  have an edge between them (this is not a multigraph)
    /// @exception UnavailableMemoryException If the edge cannot be added because the underlying
    ///  edges structure cannot grow due to running out of memory
    Edge<NData, EData>& add(size_t id, size_t source, size_t target, EData data);

    /// @brief Add an Edge
    /// @param source The id of the source node of the edge to add
    /// @param target The id of the target node of the edge to add
    /// @param data The edge data of the edge to add
    /// @return A reference to the Edge that was just created and added to the Edges
    Edge<NData, EData>& add(size_t source, size_t target, EData data);

    /// @brief Returns the number of the contained edges
    /// @return The number of contained edges
    size_t size() const;

    /// @brief Tests the existence of an edge with a given id
    /// @param id the id of the edge
    /// @return True if the edge exists, false if it does not
    bool exists(size_t id) const;

    /// @brief Tests the existence of an edge with a given source and target
    /// @param source The id of the source node
    /// @param target The id of the target node
    /// @return True if the edge exists, false if it does not
    /// @exception NonexistingItemException If testing the existence of an edge between a source 
    ///  and or target node that does not exist
    bool exists(size_t source, size_t target) const;

    /// @brief Gets the edge with a given id
    /// @param id The id of the edge to get
    /// @return A reference to the edge with the given id
    /// @exception NonexistingItemException If an edge with the given id does not exist
    Edge<NData, EData>& get(size_t id) const;

    /// @brief Gets the edge with a given source and target
    /// @param source The id of the source node
    /// @param target The id of the target node
    /// @return A reference to the edge with the given source and target
    /// @exception NonexistingItemException If the source and or target nodes do not exist
    /// @exceptionNonexistingItemException If no edge exists between the given source and target
    Edge<NData, EData>& get(size_t source, size_t target) const;

    /// @brief First part of the two brackets operator accesing of edges [source][target]
    /// @param source Id of the source node of the edge to access
    /// @return Request that remembers the source part of the request
    /// @exception NonexistingItemException If the source node does not exist
    Request operator[](size_t source);

    /// @brief First part of the two brackets operator accesing of edges [source][target]
    /// @param source Id of the source node of the edge to access
    /// @return Request that remembers the source part of the request
    /// @exception NonexistingItemException If the source node does not exist
    const Request operator[](size_t source) const;

    /// @brief Returns an iterator to the first edge
    /// @return The iterator to the first edge
    typename my_array::Array<Edge<NData, EData>>::iterator begin();

    /// @brief Returns an iterator to the space after the last edge
    /// @return The iterator to the space after the last edge
    typename my_array::Array<Edge<NData, EData>>::iterator end();

    /// @brief Copy assignment
    /// @param other The edges that will be copied from
    /// @return The edges that was copied to
    Edges<NData, EData>& operator=(const Edges<NData, EData>& other);

    /// @brief Move assignment
    /// @param other The edges that will be moved
    /// @return The edges that were moved to
    Edges<NData, EData>& operator=(Edges<NData, EData>&& other) noexcept;

    /// @brief Copy constructor with graph
    /// @param other The edges to copy
    /// @param graph The graph the constructed edges will belong to
    Edges(const Edges<NData, EData>& other, Graph<NData, EData>* graph);

    /// @brief Move constructor with graph pointer
    /// @param other The edges to move
    /// @param graph The graph the constructed edges will belong to
    Edges(Edges<NData, EData>&& other, Graph<NData, EData>* graph) noexcept;

    /// @brief Updates the pointers inside edges to point to the current graph
    void update_source_and_target_pointers();

    /// @brief Creates the adjacency matrix for these Edges from scratch
    /// @exception UnavailableMemoryException If there isn't enough memory for the adjacency matrix
    void construct_adjacency_matrix();
};

/// @brief Used exclusively for the second part of the two bracket operator accesing of edges [source][target]
/// @tparam NData The data associated with the Graph's nodes
/// @tparam EData The data associated with the Graph's edges
template <typename NData, typename EData>
class Edges<NData, EData>::Request {
public:
    /// @brief Second part of the two brackets operator accesing of edges [source][target]
    /// @param target Id of the target node of the edge to access
    /// @return A reference too the edge with the given source and target nodes
    /// @exception NonexistingItemException If the target node does not exist
    Edge<NData, EData>& operator[](size_t target);

    /// @brief Second part of the two brackets operator accesing of edges [source][target]
    /// @param target Id of the target node of the edge to access
    /// @return A reference too the edge with the given source and target nodes 
    /// /// @exception NonexistingItemException If the target node does not exist
    const Edge<NData, EData>& operator[](size_t target) const;

private:
    /// @brief Constructs the request used for accesing edges with two brackets [source][target]
    /// @param edges The edges we are making the request upon
    /// @param source Id of the source node of the edge we are trying to access
    Request(const Edges<NData, EData>& edges, size_t source);

    /// @brief Reference to the edges we are making a request upon
    const Edges<NData, EData>& edges_;

    /// @brief Id of the source node of the edge we are trying to access
    size_t source_;

    friend Edges<NData, EData>;
};

/// @brief Prints the given edges to the given output stream and returns the same output stream
/// @tparam NData The data associated with the Graph's nodes
/// @tparam EData The data associated with the Graph's edges
/// @param os The output stream to print to
/// @param edges The edges to print
/// @return The same output stream
template <typename NData, typename EData>
std::ostream& operator<<(std::ostream& os, const Edges<NData, EData>& edges) {
    edges.print(os);
    return os;
}

template<typename NData, typename EData>
inline Edges<NData, EData>::Edges(Graph<NData, EData>* graph) : graph_(graph) {}

template <typename NData, typename EData>
void Edges<NData, EData>::print(std::ostream& os) const {
    for (size_t i = 0; i < edges_.size(); i++) {
        os << edges_[i];
    }
}

template <typename NData, typename EData>
void Edges<NData, EData>::printMatrix(std::ostream& os) const {
    char separator = '|';
    char no_edge_symbol = '-';

    for (size_t i = 0; i < adjacency_matrix_.size(); i++) {
        for (size_t j = 0; j < adjacency_matrix_[i].size(); j++) {
            if (adjacency_matrix_[i][j] == nullptr) {
                os << no_edge_symbol;
            }
            else {
                os << adjacency_matrix_[i][j]->getId();
            }
            if (j < adjacency_matrix_[i].size() - 1) os << separator;
        }
        os << std::endl;
    }
}

template <typename NData, typename EData>
void Edges<NData, EData>::grow_adjacency_matrix() {
    size_t pre_modification_size = adjacency_matrix_.size();
    try {
        for (size_t i = 0; i < pre_modification_size; i++) {
            adjacency_matrix_[i].push_back(nullptr);
        }
        adjacency_matrix_.push_back(
            std::vector<Edge<NData, EData>*>(pre_modification_size + 1, nullptr));
    }
    catch (...) {
        for (size_t i = 0; i < pre_modification_size; i++) {
            adjacency_matrix_[i].resize(pre_modification_size);
        }
        adjacency_matrix_.resize(pre_modification_size);
        throw UnavailableMemoryException::adjacency_matrix_unable_to_insert();
    }
}

template <typename NData, typename EData>
Edge<NData, EData>& Edges<NData, EData>::add(size_t id, size_t source, size_t target, EData data) {
    size_t pre_modification_size = edges_.size();
    if (id > pre_modification_size)
        throw InvalidIdentifierException::adding_edge_invalid_identifier(id, pre_modification_size);
    if (id < pre_modification_size)
        throw ConflictingItemException::adding_edge_conflicting_identifier(id);
    size_t nodes_size = graph_->nodes().size();
    if (source >= nodes_size || target >= nodes_size)
        throw NonexistingItemException::adding_edge_with_nonexistant_nodes
        (source, target, nodes_size);
    if (adjacency_matrix_[source][target] != nullptr)
        throw ConflictingItemException::adding_edge_with_conflicting_nodes(source, target);
    try {
        Node<NData>* source_node = &graph_->nodes().get(source);
        Node<NData>* target_node = &graph_->nodes().get(target);
        Edge<NData, EData> edge = Edge<NData, EData>(id, source_node, target_node, data);
        edges_.push_back(edge);
        adjacency_matrix_[source][target] = &edges_[edges_.size() - 1];
        if (graph_->is_undirected()) adjacency_matrix_[target][source] = &edges_[edges_.size() - 1];
    }
    catch (...) {
        if (edges_.size() > pre_modification_size) edges_.pop_back();
        adjacency_matrix_[source][target] = nullptr;
        if (graph_->is_undirected()) adjacency_matrix_[target][source] = nullptr;
        throw UnavailableMemoryException::edge_container_unable_to_insert();
    }
    return edges_[edges_.size() - 1];
}

template <typename NData, typename EData>
Edge<NData, EData>& Edges<NData, EData>::add(size_t source, size_t target, EData data) {
    return add(edges_.size(), source, target, data);
}

template <typename NData, typename EData>
size_t Edges<NData, EData>::size() const {
    return edges_.size();
}

template <typename NData, typename EData>
bool Edges<NData, EData>::exists(size_t id) const {
    return id < size(); // assuming the property that ids should be 0...n-1
}

template <typename NData, typename EData>
bool Edges<NData, EData>::exists(size_t source, size_t target) const {
    size_t adjacency_matrix_size = adjacency_matrix_.size(); // same size for rows and columns
    if (source >= adjacency_matrix_size ||
        target >= adjacency_matrix_size)
        throw NonexistingItemException::testing_existence_of_edge_with_nonexistant_nodes(source,
            target, adjacency_matrix_size);
    return adjacency_matrix_[source][target] != nullptr;
}

template <typename NData, typename EData>
Edge<NData, EData>& Edges<NData, EData>::get(size_t id) const {
    if (!exists(id))
        throw NonexistingItemException::accessing_nonexistant_edge_with_identifier(id, size());
    return const_cast<Edge<NData, EData>&>(edges_[id]);
}

template <typename NData, typename EData>
Edge<NData, EData>& Edges<NData, EData>::get(size_t source, size_t target) const {
    size_t adjacency_matrix_size = adjacency_matrix_.size(); // same size for rows and columns
    if (source >= adjacency_matrix_size || target >= adjacency_matrix_size)
        throw NonexistingItemException::accessing_edge_with_nonexistant_nodes
        (source, target, adjacency_matrix_size);
    if (adjacency_matrix_[source][target] == nullptr)
        throw NonexistingItemException::accessing_nonexistant_edge_with_source_target
        (source, target);
    return *adjacency_matrix_[source][target];
}

template <typename NData, typename EData>
Edges<NData, EData>::Request::Request(const Edges<NData, EData>& edges, size_t source)
    : edges_(edges), source_(source) {}

template <typename NData, typename EData>
typename Edges<NData, EData>::Request Edges<NData, EData>::operator[](size_t source) {
    size_t size = adjacency_matrix_.size();
    if (source >= size)
        throw NonexistingItemException::accessing_edge_nonexistant_source(source, size);
    return Edges<NData, EData>::Request(*this, source);
}

template <typename NData, typename EData>
const typename Edges<NData, EData>::Request Edges<NData, EData>::operator[](size_t source) const {
    size_t size = edges_.adjacency_matrix_.size();
    if (source >= size)
        throw NonexistingItemException::accessing_edge_nonexistant_source(source, size);
    return Edges<NData, EData>::Request(*this, source);
}

template <typename NData, typename EData>
Edge<NData, EData>& Edges<NData, EData>::Request::operator[](size_t target) {
    size_t size = edges_.adjacency_matrix_.size();
    if (target >= size)
        throw NonexistingItemException::accessing_edge_nonexistant_target(target, size);
    return edges_.get(source_, target);
}

template <typename NData, typename EData>
const Edge<NData, EData>& Edges<NData, EData>::Request::operator[](size_t target) const {
    size_t size = adjacency_matrix_.size();
    if (target >= size)
        throw NonexistingItemException::accessing_edge_nonexistant_target(target, size);
    return edges_.get(source_, target);
}

template <typename NData, typename EData>
typename my_array::Array<Edge<NData, EData>>::iterator Edges<NData, EData>::begin() {
    return edges_.begin();
}

template <typename NData, typename EData>
typename my_array::Array<Edge<NData, EData>>::iterator Edges<NData, EData>::end() {
    return edges_.end();
}

template <typename NData, typename EData>
void Edges<NData, EData>::construct_adjacency_matrix() {
    adjacency_matrix_ = std::vector<std::vector<Edge<NData, EData>*>>();
    size_t nodes_size = graph_->nodes().size();
    try {
        for (size_t i = 0; i < nodes_size; i++) {
            adjacency_matrix_.emplace_back(nodes_size, nullptr);
        }
    }
    catch (...) {
        throw UnavailableMemoryException::adjacency_matrix_unable_to_insert();
    }

    for (size_t i = 0; i < edges_.size(); i++) {
        size_t s = edges_[i].getSource().getId();
        size_t t = edges_[i].getTarget().getId();
        adjacency_matrix_[s][t] = &edges_[i];
        if (graph_->is_undirected()) adjacency_matrix_[t][s] = &edges_[i];
    }
}

template <typename NData, typename EData>
void Edges<NData, EData>::update_source_and_target_pointers() {
    for (size_t i = 0; i < edges_.size(); i++) {
        Node<NData>* updated_source = &graph_->nodes()[edges_[i].getSource().getId()];
        Node<NData>* updated_target = &graph_->nodes()[edges_[i].getTarget().getId()];
        edges_[i].update_node_pointers(updated_source, updated_target);
    }
}

template <typename NData, typename EData>
Edges<NData, EData>& Edges<NData, EData>::operator=(const Edges<NData, EData>& other) {
    edges_ = other.edges_;
    // upon just copying, the source/target pointers inside individual edges point to other
    update_source_and_target_pointers();
    // we can't just copy the adjacency matrix, because the pointers would still point to other
    construct_adjacency_matrix();
    return *this;
}

template <typename NData, typename EData>
Edges<NData, EData>& Edges<NData, EData>::operator=(Edges<NData, EData>&& other) noexcept {
    if (this != &other) {
        std::swap(edges_, other.edges_);
        std::swap(adjacency_matrix_, other.adjacency_matrix_);
    }
    return *this;
}

template <typename NData, typename EData>
Edges<NData, EData>::Edges(const Edges<NData, EData>& other, Graph<NData, EData>* graph) 
        : graph_(graph), edges_(other.edges_) {
    // upon just copying, the source/target pointers inside individual edges point to other
    update_source_and_target_pointers();
    // the adjacency matrix must be constructed inside the child constructors   
}

template <typename NData, typename EData>
Edges<NData, EData>::Edges(Edges<NData, EData>&& other, Graph<NData, EData>* graph) noexcept
        : graph_(graph) {
    std::swap(edges_, other.edges_);
    std::swap(adjacency_matrix_, other.adjacency_matrix_);
}


#endif