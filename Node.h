#ifndef __NODE_H  
#define __NODE_H

#include <iostream>
#include <utility>

/// @file Node.h
/// @brief Contains the Node class and its member function definitions


/// @brief An individual node of the graph
/// @tparam NData The data associated with the Graph's nodes
template <typename NData>
class Node {
public:
    /// @brief The default constructor
    Node() = default;

    /// @brief Construct a node with the given id and node data
    /// @param id The id of the node to construct
    /// @param data The node data of the node
    Node(size_t id, NData data);

    /// @brief Get the id of the node
    /// @return The id of the node
    size_t getId() const;

    /// @brief Get the node data of the node
    /// @return The node data of the node
    NData& getData();

    /// @brief Copy assignment
    /// @param other The node that will be copied
    /// @return The node that was copied to
    Node<NData>& operator=(const Node<NData>& other);

    /// @brief Move assignment
    /// @param other The node that will be moved
    /// @return The node that was moved to
    Node<NData>& operator=(Node<NData>&& other) noexcept;

    /// @brief Copy constructor
    /// @param other The node to copy
    Node(const Node<NData>& other);

    /// @brief Move constructor
    /// @param other The node to move
    Node(Node<NData>&& other) noexcept;

    /// @brief Destructor
    ~Node();
private:
    /// @brief The id of the node; values 0...n-1 where n is the number of nodes in the given graph
    size_t id_;

    /// @brief The node data associated with the node
    NData data_;
};

/// @brief Prints the given node to the given output stream and returns the same output stream
/// @tparam NData The data associated with the Graph's nodes
/// @param os The output stream
/// @param node The node to print
/// @return The same output stream
template <typename NData>
std::ostream& operator<<(std::ostream& os, const Node<NData>& node) {
    os << "node (" << node.getId() << " {" << const_cast<Node<NData>&>(node).getData()
        << "})" << std::endl;
    return os;
}

template <typename NData>
Node<NData>::Node(size_t id, NData data) : id_(id), data_(data) {}

template <typename NData>
size_t Node<NData>::getId() const {
    return id_;
}

template <typename NData>
NData& Node<NData>::getData() {
    return data_;
}

template <typename NData>
Node<NData>& Node<NData>::operator=(const Node<NData>& other) {
    id_ = other.id_;
    data_ = other.data_;
    return *this;
}


template <typename NData>
Node<NData>& Node<NData>::operator=(Node<NData>&& other) noexcept {
    if (this != &other) {
        std::swap(id_, other.id_);
        std::swap(data_, other.data_);
    }
    return *this;
}

template <typename NData>
Node<NData>::Node(const Node<NData>& other) : id_(other.id_), data_(other.data_) {}

template <typename NData>
Node<NData>::Node(Node<NData>&& other) noexcept : id_(0){
    std::swap(id_, other.id_);
    std::swap(data_, other.data_);
}

template <typename NData>
Node<NData>::~Node() {
    id_ = SIZE_MAX;
}


#endif