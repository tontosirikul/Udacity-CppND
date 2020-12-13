#ifndef ROUTE_MODEL_H
#define ROUTE_MODEL_H

#include <limits>
#include <cmath>
#include <unordered_map>
#include "model.h"
#include <iostream>

// RouteModel inherieted by model class from io2d
class RouteModel : public Model {

  public:
    // subclass called node which inherited from Model::Node (struct)
    class Node : public Model::Node {
      public:
        // Node provides x and y then we add list below 
        Node * parent = nullptr; // pointer to parent node
        float h_value = std::numeric_limits<float>::max(); // h_value of the node
        float g_value = 0.0; // g_value of the node
        bool visited = false; // boolean which tell visited status
        std::vector<Node *> neighbors; // vector of node pointer called neighbors

        void FindNeighbors(); // method to find neighbors of the node
        
        // method which returns distance between others and this node
        float distance(Node other) const {
            return std::sqrt(std::pow((x - other.x), 2) + std::pow((y - other.y), 2));
        }

        
        Node(){}
        Node(int idx, RouteModel * search_model, Model::Node node) : Model::Node(node), parent_model(search_model), index(idx) {}

      private:
        int index;
        Node * FindNeighbor(std::vector<int> node_indices); // use for finding neighbors
        RouteModel * parent_model = nullptr; // pointer to which node belongs
    };

    RouteModel(const std::vector<std::byte> &xml);
    Node &FindClosestNode(float x, float y);
    auto &SNodes() { return m_Nodes; }
    std::vector<Node> path; // store final path
    
  private:
    void CreateNodeToRoadHashmap(); // create map
    std::unordered_map<int, std::vector<const Model::Road *>> node_to_road;
    std::vector<Node> m_Nodes;

};

#endif
