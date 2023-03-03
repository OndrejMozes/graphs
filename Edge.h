#ifndef __EDGE_H
#define __EDGE_H

#include <utility>
#include <iostream>
#include "Node.h"


/// @file Edge.h
/// @brief Contains the Edge class and its member function definitions


/// @brief An individual edge of the graph
/// @tparam NData The data associated with the Graph's nodes
/// @tparam EData The data associated with the Graph's edges
template <typename NData, typename EData>
class Edge {
public:
    /// @brief The default constructor
    Edge() = default;

    /// @brief Construct an edge with the given id, source and target and edge data
    /// @param id The id of the edge to construct
    /// @param source A pointer to the source node of the edge
    /// @param target A pointer to the target node of the edge
    /// @param data The edge data of the edge
    Edge(size_t id, Node<NData>* source, Node<NData>* target, EData data);

    /// @brief Get the id of the edge
    /// @return The id of the edge
    size_t getId() const;

    /// @brief Get the edge data of the edge
    /// @return The edge data of the edge
    EData& getData();

    /// @brief Get the source node of the edge
    /// @return A reference to the source node of the edge
    Node<NData>& getSource() const;

    /// @brief Get the target node of the edge
    /// @return A reference to the target node of the edge
    Node<NData>& getTarget() const;

    /// @brief Copy assignment
    /// @param other The edge that will be copied
    /// @return The edge that was copied to
    Edge<NData, EData>& operator=(const Edge<NData, EData>& other);

    /// @brief Move assignment
    /// @param other The edge that will be moved
    /// @return The edge that was moved to
    Edge<NData, EData>& operator=(Edge<NData, EData>&& other) noexcept;

    /// @brief Copy constructor
    /// @param other The edge to copy
    Edge(const Edge<NData, EData>& other);

    /// @brief Move constructor
    /// @param other The edge to move
    Edge(Edge<NData, EData>&& other) noexcept;

    /// @brief Destructor
    ~Edge();

    /// @brief Updates the source and target node pointers to the given values
    /// @param source A pointer to the source node 
    /// @param target A pointer to the target node
    void update_node_pointers(Node<NData>* source, Node<NData>* target);

private:
    /// @brief The id of the edge; values 0...n-1 where n is the number of edges in the given graph
    size_t id_;

    /// @brief A pointer to the source node of this edge
    Node<NData> *source_;

    /// @brief A pointer to the target node of this edge
    Node<NData> *target_;

    /// @brief The edge data associated with the edge
    EData data_;
};

/// @brief Prints the given edge to the given output stream and returns the same output stream
/// @tparam NData The data associated with the Graph's nodes
/// @tparam EData The data associated with the Graph's edges
/// @param os The output stream to print to 
/// @param edge The edge to print
/// @return The same output stream
template <typename NData, typename EData>
std::ostream& operator<<(std::ostream& os, const Edge<NData, EData>& edge) {
    os << "edge (" << edge.getSource().getId() << ")-[" << edge.getId() << " {"
        << const_cast<Edge<NData, EData>&>(edge).getData() << "}]->("
        << edge.getTarget().getId() << ")" << std::endl;
    return os;
}

template <typename NData, typename EData>
Edge<NData, EData>::Edge(size_t id, Node<NData>* source, Node<NData>* target, EData data) :
    id_(id), source_(source), target_(target), data_(data) {}

template <typename NData, typename EData>
size_t Edge<NData, EData>::getId() const {
    return id_;
}

template <typename NData, typename EData>
EData& Edge<NData, EData>::getData() {
    return data_;
}

template <typename NData, typename EData>
Node<NData>& Edge<NData, EData>::getSource() const {
    return *source_;
}

template <typename NData, typename EData>
Node<NData>& Edge<NData, EData>::getTarget() const {
    return *target_;
}


// when copying edges we need to do so alongside nodes
// otherwise source/target will point to nonsense
template <typename NData, typename EData>
Edge<NData, EData>& Edge<NData, EData>::operator=(const Edge<NData, EData>& other) {
    id_ = other.id_;
    source_ = other.source_;
    target_ = other.target_;
    data_ = other.data_;
    return *this;
}

// when moving edges we need to do so alongside nodes
// otherwise source/target will point to nonsense
template <typename NData, typename EData>
Edge<NData, EData>& Edge<NData, EData>::operator=(Edge<NData, EData>&& other) noexcept {
    if (this != &other) {
        std::swap(id_, other.id_);
        std::swap(source_, other.source_);
        std::swap(target_, other.target_);
        std::swap(data_, other.data_);
    }
    return *this;
}

// when copying edges we need to do so alongside nodes
// otherwise source/target will point to nonsense
template <typename NData, typename EData>
Edge<NData, EData>::Edge(const Edge<NData, EData>& other) 
    : id_(other.id_), source_(other.source_), target_(other.target_), data_(other.data_) {}

// when moving edges we need to do so alongside nodes
// otherwise source/target will point to nonsense
template <typename NData, typename EData>
Edge<NData, EData>::Edge(Edge<NData, EData>&& other) noexcept
        : id_(SIZE_MAX), source_(nullptr), target_(nullptr) {
    std::swap(id_, other.id_);
    std::swap(source_, other.source_);
    std::swap(target_, other.target_);
    std::swap(data_, other.data_);
}

template <typename NData, typename EData>
Edge<NData, EData>::~Edge() {
    id_ = SIZE_MAX;
    source_ = nullptr;
    target_ = nullptr;
}

template <typename NData, typename EData>
void Edge<NData, EData>::update_node_pointers(Node<NData>* source, Node<NData>* target) {
    source_ = source;
    target_ = target;
}


#endif