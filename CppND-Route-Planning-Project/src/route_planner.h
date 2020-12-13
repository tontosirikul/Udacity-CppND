#ifndef ROUTE_PLANNER_H
#define ROUTE_PLANNER_H

#include <iostream>
#include <vector>
#include <string>
#include "route_model.h"

// RoutePlanner class definitions
class RoutePlanner {
  public:
    // constructure takes a "RouteModel" and the coordinates.
    RoutePlanner(RouteModel &model, float start_x, float start_y, float end_x, float end_y);
    
    // Add public variables or methods declarations here.
    
    // GetDistance() which return distance which store below
    float GetDistance() const {return distance;}
    // AStarSearch() 
    void AStarSearch();

    // The following methods have been made public so we can test them individually.
    void AddNeighbors(RouteModel::Node *current_node);
    float CalculateHValue(RouteModel::Node const *node);
    std::vector<RouteModel::Node> ConstructFinalPath(RouteModel::Node *);
    RouteModel::Node *NextNode();

  private:
    // Add private variables or methods declarations here.
    
    // private variable for the open_list
    std::vector<RouteModel::Node*> open_list; // pointer to the open_list 
    RouteModel::Node *start_node; // pointer to the start node
    RouteModel::Node *end_node; // pointer to the end_node

    float distance = 0.0f; // distance for GetDistance()
    RouteModel &m_Model; // routemodel that we are using.
};

#endif