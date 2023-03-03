#ifndef __EXCEPTIONS_H  
#define __EXCEPTIONS_H


#include <string>


/// @file Exceptions.h
/// @brief Contains the exceptions that are thrown by the graph and its nodes and edges


/// @brief Abstract parent of all the other exceptions
class Exception {
public:
    /// @brief Construct an exception with the given text
    /// @param text The message of the exception
    Exception(const std::string& text);

    /// @brief Construct an exception with the given text
    /// @param text The message of the exception
    Exception(std::string&& text);

    /// @brief Get the message of the exception
    /// @return The message of the exception
    std::string& what();

private:
    /// @brief The message of the exception
    std::string text_;
};

/// @brief Exceptions relating to dealing with non-existing items
class NonexistingItemException : public Exception {
public:
    using Exception::Exception;

    /// @brief Return an exception for attempting to access a node with an id that does not exist
    /// @param id The id of the node that was being attempted to access
    /// @param size The size of the nodes structure
    /// @return The Nonexisting item exception with the appropriate message
    static NonexistingItemException accessing_nonexistant_node
    (size_t id, size_t size);

    /// @brief Return an exception for attempting to access an edge with an id that does not exist
    /// @param id The id of the edge that was being attempted to access
    /// @param size The size of the edges structure
    /// @return The Nonexisting item exception with the appropriate message
    static NonexistingItemException accessing_nonexistant_edge_with_identifier
    (size_t id, size_t size);

    /// @brief Return an exception for attempting to access an edge with source and or target nodes
    ///  that do not exist
    /// @param source The id of the source node
    /// @param target Th id of the target node
    /// @param size The size of the nodes structure
    /// @return The Nonexisting item exception with the appropriate message
    static NonexistingItemException accessing_edge_with_nonexistant_nodes
    (size_t source, size_t target, size_t size);

    /// @brief Return an exception for attempting to access an edge that does not exist between
    ///  the given source and target nodes
    /// @param source The id of the source node
    /// @param target The id of the target node
    /// @return The Nonexisting item exception with the appropriate message
    static NonexistingItemException accessing_nonexistant_edge_with_source_target
    (size_t source, size_t target);

    /// @brief Returns and exception for attempting to test the existance of an edge with 
    ///  a non-existent source and or target node
    /// @param source The id of the source node
    /// @param target The id of the target node
    /// @param size The size of the nodes structure
    /// @return The Nonexisting item exception with the appropriate message
    static NonexistingItemException testing_existence_of_edge_with_nonexistant_nodes
    (size_t source, size_t target, size_t size);

    /// @brief Returns an exception for attempting to access an edge outgoing from 
    ///  a nonexisting source node
    /// @param source The id of the source node
    /// @param size The size of the nodes structure
    /// @return The Nonexisting item exception with the appropriate message
    static NonexistingItemException accessing_edge_nonexistant_source
    (size_t source, size_t size);

    /// @brief Returns an exception for attempting to access an edge incoming to
    ///  a nonexisting target node
    /// @param target The if of the target node
    /// @param size The size of the nodes structure
    /// @return The Nonexisting item exception with the appropriate message
    static NonexistingItemException accessing_edge_nonexistant_target
    (size_t target, size_t size);

    /// @brief Returns an exception for attempting to add an edge with source and or target nodes
    ///  that do not exist
    /// @param source The id of the source node
    /// @param target Th id of the target node
    /// @param size The size of the nodes structure
    /// @return The Nonexisting item exception with the appropriate message
    static NonexistingItemException adding_edge_with_nonexistant_nodes
    (size_t source, size_t target, size_t size);

};

/// @brief Exceptions relating to conflicting items
class ConflictingItemException : public Exception {
public:
    using Exception::Exception;

    /// @brief Returns an exception for attempting to add a node with an id that is already in use
    /// @param id The id of the node that was being attempted to be added
    /// @return The conflicting item exception with the appropriate message
    static ConflictingItemException adding_node_conflicting_identifier(size_t id);

    /// @brief Returns an exception for attempting to add an edge with an id that is already in use
    /// @param id The id of the edge that was being attempted to be added
    /// @return The conflicting item exception with the appropriate message
    static ConflictingItemException adding_edge_conflicting_identifier(size_t id);

    /// @brief Returns an exception for attempting to add an edge between already connected nodes
    /// @param source The id of the source node
    /// @param target Th id of the target node
    /// @return The conflicting item exception with the appropriate message
    static ConflictingItemException adding_edge_with_conflicting_nodes
    (size_t source, size_t target);
};

/// @brief Exceptions related to invalid identifiers
class InvalidIdentifierException : public Exception {
public:
    using Exception::Exception;

    /// @brief Returns an exception for attempting to add a node with an invalid id
    /// @param id The id of the node
    /// @param size The size of the nodes structure and also the expected id value
    /// @return The invalid identifier exception with the appropriate message
    static InvalidIdentifierException adding_node_invalid_identifier(size_t id, size_t size);

    /// @brief Returns an exception for attempting to add an edge with an invalid id
    /// @param id The id of the edge
    /// @param size The size of the edges structure and also the expected id value
    /// @return The invalid identifier exception with the appropriate message
    static InvalidIdentifierException adding_edge_invalid_identifier(size_t id, size_t size);
};

/// @brief Exceptions relating to running out of memory
class UnavailableMemoryException : public Exception {
public:
    using Exception::Exception;

    /// @brief Returns an exception for being unable to grow the nodes container
    /// @return The unavailable memory exception with the appropriate message
    static UnavailableMemoryException node_container_unable_to_insert();

    /// @brief Returns an exception for being unable to grow the adjacency matrix container
    /// @return The unavailable memory exception with the appropriate message
    static UnavailableMemoryException adjacency_matrix_unable_to_insert();

    /// @brief Returns an exception for being unable to grow the edges container
    /// @return The unavailable memory exception with the appropriate message
    static UnavailableMemoryException edge_container_unable_to_insert();

    /// @brief Returns an exception for being unable to grow the array
    /// @return The unavailable memory exception with the appropriate message
    static UnavailableMemoryException array_unable_to_insert();
};

/// @brief Exceptions relating problems with files
class FileProcessingException : public Exception {
public:
    using Exception::Exception;

    /// @brief Returns an exception for being unable to open the output file
    /// @param filename The name of the file
    /// @return The file processing exception with the appropriate message
    static FileProcessingException unable_to_open_output_file(std::string filename);

    /// @brief Returns an exception for being unable to open the input file
    /// @param filename The name of the file
    /// @return The file processing exception with the appropriate message
    static FileProcessingException unable_to_open_input_file(std::string filename);
};

/// @brief Exceptions relation to problems with streams
class InvalidStreamException : public Exception {
public:
    using Exception::Exception;

    /// @brief Returns an exception for being unable to print to output stream
    static InvalidStreamException invalid_output_stream();

    /// @brief Returns an exception for being unable to import from the input stream
    static InvalidStreamException invalid_input_stream();
};

class ParsingException : public Exception {
public:
    using Exception::Exception;

    /// @brief Returns an exception for failing to parse a number
    static ParsingException failed_parsing_number();
};

/// @brief Exception relating to accesing array indexes out of range
class OutOfRangeException : public Exception {
public:
    using Exception::Exception;
    
    /// @brief Returns an exception for trying to access an invalid array index
    /// @param index The index trying to access
    /// @return The out of range exception with the appropriate message
    static OutOfRangeException array_accessing_invalid_index(size_t index);
};

/// @brief Exception relating to trying to shrink an empty array
class EmptyArrayException : public Exception {
public:
    using Exception::Exception;

    /// @brief Returns an exception for trying to pop an empty array
    /// @return The empty array exception with the appropriate message
    static EmptyArrayException array_popping_empty_array();
};




// Parent exception

Exception::Exception(const std::string& text) : text_(text) {}

Exception::Exception(std::string&& text) : text_(text) {}

std::string& Exception::what() {
    return text_;
}




// Array exceptions

UnavailableMemoryException UnavailableMemoryException::array_unable_to_insert() {
    return UnavailableMemoryException("Memory allocation failed!");
}

OutOfRangeException OutOfRangeException::array_accessing_invalid_index(size_t index) {
    return OutOfRangeException("Invalid array index " + std::to_string(index) + " requested");
}

EmptyArrayException EmptyArrayException::array_popping_empty_array() {
    return EmptyArrayException("Tried to remove an element from an empty array!");
}




// Graph exceptions

NonexistingItemException NonexistingItemException::accessing_nonexistant_node
(size_t id, size_t size) {
    return NonexistingItemException(std::string("Attempting to access a nonexisting node with")
        + " identifier " + std::to_string(id) + ", only " + std::to_string(size) + " nodes are"
        + " available");
}

NonexistingItemException NonexistingItemException::accessing_nonexistant_edge_with_identifier
(size_t id, size_t size) {
    return NonexistingItemException(std::string("Attempting to access a nonexisting edge with")
        + " identifier " + std::to_string(id) + ", only " + std::to_string(size)
        + " edges are available");
}

NonexistingItemException NonexistingItemException::accessing_edge_with_nonexistant_nodes
(size_t source, size_t target, size_t size) {
    return NonexistingItemException
    ("Attempting to access an edge between a nonexisting pair of nodes with identifiers "
        + std::to_string(source) + " and " + std::to_string(target) + ", only "
        + std::to_string(size) + " nodes are available");
}

NonexistingItemException NonexistingItemException::accessing_nonexistant_edge_with_source_target
(size_t source, size_t target) {
    return NonexistingItemException
    ("Attempting to access a nonexisting edge between a pair of nodes with identifiers " +
        std::to_string(source) + " and " + std::to_string(target));
}

NonexistingItemException NonexistingItemException::testing_existence_of_edge_with_nonexistant_nodes
(size_t source, size_t target, size_t size) {
    return NonexistingItemException(std::string("Attempting to test the existence of an edge")
        + " between a nonexisting pair of nodes with identifiers " + std::to_string(source)
        + " and " + std::to_string(target) + ", only " + std::to_string(size)
        + " nodes are available");
}

NonexistingItemException NonexistingItemException::accessing_edge_nonexistant_source
(size_t source, size_t size) {
    return NonexistingItemException
    ("Attempting to access an edge outgoing from a nonexisting source node with identifier " +
        std::to_string(source) + ", only " + std::to_string(size) + " nodes are available");
}

NonexistingItemException NonexistingItemException::accessing_edge_nonexistant_target
(size_t target, size_t size) {
    return NonexistingItemException
    ("Attempting to access an edge incoming to a nonexisting target node with identifier " +
        std::to_string(target) + ", only " + std::to_string(size) + " nodes are available");
}

NonexistingItemException NonexistingItemException::adding_edge_with_nonexistant_nodes
(size_t source, size_t target, size_t size) {
    return NonexistingItemException
    ("Attempting to add a new edge between a nonexisting pair of nodes with identifiers " +
        std::to_string(source) + " and " + std::to_string(target) + ", only "
        + std::to_string(size) + " nodes are available");
}

ConflictingItemException ConflictingItemException::adding_node_conflicting_identifier(size_t id) {
    return ConflictingItemException("Attempting to add a new node with identifier "
        + std::to_string(id) + " which already is associated with another existing node");
}

ConflictingItemException ConflictingItemException::adding_edge_conflicting_identifier(size_t id) {
    return ConflictingItemException("Attempting to add a new edge with identifier "
        + std::to_string(id) + " which already is associated with another existing edge");
}

ConflictingItemException ConflictingItemException::adding_edge_with_conflicting_nodes
(size_t source, size_t target) {
    return ConflictingItemException
    ("Attempting to add a new edge between a pair of nodes with identifiers "
        + std::to_string(source) + " and " + std::to_string(target)
        + " which already are connected with another existing edge");
}

InvalidIdentifierException InvalidIdentifierException::adding_node_invalid_identifier(size_t id,
    size_t size) {
    return InvalidIdentifierException("Attempting to add a new node with invalid identifier "
        + std::to_string(id) + ", expected " + std::to_string(size) + " instead");
}

InvalidIdentifierException InvalidIdentifierException::adding_edge_invalid_identifier(size_t id,
    size_t size) {
    return InvalidIdentifierException("Attempting to add a new edge with invalid identifier "
        + std::to_string(id) + ", expected " + std::to_string(size) + " instead");
}

UnavailableMemoryException UnavailableMemoryException::node_container_unable_to_insert() {
    return UnavailableMemoryException
    ("Unable to insert a new node record into the underlying container of nodes");
}

UnavailableMemoryException UnavailableMemoryException::adjacency_matrix_unable_to_insert() {
    return UnavailableMemoryException
    ("Unable to extend the underlying adjacency matrix container for edges");
}

UnavailableMemoryException UnavailableMemoryException::edge_container_unable_to_insert() {
    return UnavailableMemoryException
    ("Unable to insert a new edge record into the underlying container of edges");
}

FileProcessingException FileProcessingException::unable_to_open_output_file(std::string filename) {
    return FileProcessingException("Unable to open an output file " + filename);
}

FileProcessingException FileProcessingException::unable_to_open_input_file(std::string filename) {
    return FileProcessingException("Unable to open an input file " + filename);
}


InvalidStreamException InvalidStreamException::invalid_output_stream() {
    return InvalidStreamException("Unable to print to the specified output stream");
}

InvalidStreamException InvalidStreamException::invalid_input_stream() {
    return InvalidStreamException("Unable to import from the specified input stream");
}

ParsingException ParsingException::failed_parsing_number() {
    return ParsingException("Failed while parsing a number from the input");
}



#endif