//
// Created by Robert 5/19/17.
//

#ifndef NAVIGATIONSYSTEM_NODE_HH
#define NAVIGATIONSYSTEM_NODE_HH

#include <ostream>
#include "coordinate.hh"

/**
 * \brief Node class
 * \details
 * Node class used in the constructions of a \ref Graph and \ref Vertice classes
 */
class Node {
private:
    Coordinate coordinate;
    std::string name;


public:
    Node(const Coordinate &coordinate,  const std::string &name = "");
    Node(const float x, const float y,  const std::string &name = "");
    friend std::ostream &operator<<(std::ostream &os, const Node &node);
    bool operator==(const Node &rhs) const;
    bool operator!=(const Node &rhs) const;
    float euclideanDistance(const Node &other) const;
    Coordinate getCoordinate();

/**
 * \brief function to get the name of a node
 */
    std::string getNodeName() const;
};


#endif //NAVIGATIONSYSTEM_NODE_HH
