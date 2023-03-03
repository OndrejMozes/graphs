#ifndef __NODES_H  
#define __NODES_H

#include <utility>
#include "Graph.h"
#include "Node.h"


/// @file Edges.h
/// @brief Contains the Nodes class and its member function definitions


// forward declaration
template <typename NData, typename EData>
class Graph;

/// @brief The Nodes of the Graph
/// @tparam NData The data associated with the Graph's nodes
/// @tparam EData The data associated with the Graph's edges 
template <typename NData, typename EData>
class Nodes {
public:
    /// @brief Constructs the Nodes for a Graph
    /// @param graph A pointer to the Graph to construct the nodes for
    Nodes(Graph<NData, EData>* graph);

    /// @brief Prints the nodes to the specified output stream
    /// @param os The output stream
    void print(std::ostream& os = std::cout) const;

    /// @brief Add a Node
    /// @param id Id of the node to add (should be equal to the size of the nodes)
    /// @param data The node data of the node to add
    /// @return A reference to the node that was just created and added to the nodes
    /// @exception InvalidIdentifierException If id was invalid (higher than size of edges)
    /// @exception ConflictingItemException If id is already taken (lower than size of edges)
    /// @exception UnavailableMemoryException If the underlying nodes contained cannot grow due to
    ///  running out of memory
    Node<NData>& add(size_t id, NData data);

    /// @brief Add a Node
    /// @param data The node data of the node to add
    /// @return A reference to the node that was just created and added to the nodes 
    Node<NData>& add(NData data);

    /// @brief Returns the number of the contained nodes
    /// @return The number of contained nodes
    size_t size() const;

    /// @brief Tests the existence of a node with a given id
    /// @param id The id of the node
    /// @return True if the node exists, false if it does not 
    bool exists(size_t id) const;

    /// @brief Gets the node with the given id
    /// @param id The id of the node to get
    /// @return A reference to the node with the given id
    /// @exception NonexistingItemException If no node with the given id exists
    Node<NData>& get(size_t id) const;

    /// @brief Gets the node with the given id
    /// @param id The id of the node to get
    /// @return A reference to the node with the given id 
    Node<NData>& operator[](size_t id) const;

    /// @brief Returns an iterator to the first node
    /// @return The iterator to the first node
    typename my_array::Array<Node<NData>>::iterator begin();

    /// @brief Returns an iterator to the space after the last node
    /// @return The iterator to the space after the last node
    typename my_array::Array<Node<NData>>::iterator end();

    /// @brief Copy assignment
    /// @param other The nodes that will be copied from
    /// @return The nodes that were copied to
    Nodes<NData, EData>& operator=(const Nodes<NData, EData>& other);

    /// @brief Move assignment
    /// @param other The nodes that will be moved from
    /// @return The nodes that were moved to
    Nodes<NData, EData>& operator=(Nodes<NData, EData>&& other) noexcept;

    /// @brief Copy constructor with graph
    /// @param other Nodes to copy from
    /// @param graph Pointer to the graph these nodes should belong to
    Nodes(const Nodes<NData, EData>& other, Graph<NData, EData> *graph);

    /// @brief Move constructor with graph
    /// @param other Nodes to move
    /// @param graph Pointer to the graph these nodes should belong to
    Nodes(Nodes<NData, EData>&& other, Graph<NData, EData>* graph) noexcept;

private:
    /// @brief A pointer to the graph these are the nodes of
    Graph<NData, EData>* graph_;

    /// @brief The actual internal storage of the nodes themselves
    my_array::Array<Node<NData>> nodes_;
};

/// @brief Prints the given nodes to the given output stream and return the same stream
/// @tparam NData The data associated with the Graph's nodes
/// @tparam EData The data associated with the Graph's edges 
/// @param os The output stream to print to
/// @param nodes The nodes to print 
/// @return The same output stream
template <typename NData, typename EData>
std::ostream& operator<<(std::ostream& os, const Nodes<NData, EData>& nodes) {
    nodes.print(os);
    return os;
}

template<typename NData, typename EData>
inline Nodes<NData, EData>::Nodes(Graph<NData, EData>* graph) : graph_(graph) {}

template <typename NData, typename EData>
void Nodes<NData, EData>::print(std::ostream& os) const {
    for (size_t i = 0; i < nodes_.size(); i++) {
        os << nodes_[i];
    }
}

template <typename NData, typename EData>
Node<NData>& Nodes<NData, EData>::add(size_t id, NData data) {
    size_t pre_modification_size = nodes_.size();
    if (id > pre_modification_size)
        throw InvalidIdentifierException::adding_node_invalid_identifier(id, pre_modification_size);
    // assuming that the current nodes have valid ids 0...n-1
    if (id < pre_modification_size)
        throw ConflictingItemException::adding_node_conflicting_identifier(id);
    try {
        nodes_.push_back(Node<NData>(id, data));
        graph_->edges().grow_adjacency_matrix();
    }
    catch (...) {
        if (nodes_.size() > pre_modification_size) nodes_.pop_back();
        throw UnavailableMemoryException::node_container_unable_to_insert();
    }

    return nodes_[nodes_.size() - 1];
}

template <typename NData, typename EData>
Node<NData>& Nodes<NData, EData>::add(NData data) {
    return add(nodes_.size(), data);
}

template <typename NData, typename EData>
size_t Nodes<NData, EData>::size() const {
    return nodes_.size();
}

template <typename NData, typename EData>
bool Nodes<NData, EData>::exists(size_t id) const {
    return id < size(); // assuming the property that ids should be 0...n-1
}

template <typename NData, typename EData>
Node<NData>& Nodes<NData, EData>::get(size_t id) const {
    if (!exists(id))
        throw NonexistingItemException::accessing_nonexistant_node(id, size());
    return const_cast<Node<NData>&>(nodes_[id]);
}

template <typename NData, typename EData>
Node<NData>& Nodes<NData, EData>::operator[](size_t id) const {
    return get(id);
}

template <typename NData, typename EData>
typename my_array::Array<Node<NData>>::iterator Nodes<NData, EData>::begin() {
    return nodes_.begin();
}

template <typename NData, typename EData>
typename my_array::Array<Node<NData>>::iterator Nodes<NData, EData>::end() {
    return nodes_.end();
}

template <typename NData, typename EData>
Nodes<NData, EData>& Nodes<NData, EData>::operator=(const Nodes<NData, EData>& other) {
    nodes_ = other.nodes_;
    return *this;
}

template <typename NData, typename EData>
Nodes<NData, EData>& Nodes<NData, EData>::operator=(Nodes<NData, EData>&& other) noexcept{
    if (this != &other) {
        std::swap(nodes_, other.nodes_);
    }
    return *this;
}

template <typename NData, typename EData>
Nodes<NData, EData>::Nodes(const Nodes<NData, EData>& other, Graph<NData, EData>* graph)
        : graph_(graph), nodes_(other.nodes_) {}

template <typename NData, typename EData>
Nodes<NData, EData>::Nodes(Nodes<NData, EData>&& other, Graph<NData, EData>* graph) noexcept 
        : graph_(graph) {
    std::swap(nodes_, other.nodes_);
}


#endif