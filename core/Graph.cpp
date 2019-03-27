//
// Created by Thoh Testarossa on 2019-03-08.
//

#include "../core/Graph.h"

Vertex::Vertex(int vertexID, bool activeness, std::map<int, double> value)
{
    this->vertexID = vertexID;
    this->isActive = activeness;
    this->value = value;
}

Edge::Edge(int src, int dst, double weight)
{
    this->src = src;
    this->dst = dst;
    this->weight = weight;
}

Graph::Graph(int vCount)
{
    this->vList = std::vector<Vertex>();
    this->eList = std::vector<Edge>();

    this->vCount = vCount;
    for(int i = 0; i < vCount; i++) this->vList.emplace_back(Vertex(i, false, std::map<int, double>()));
    this->eCount = 0;
}

Graph::Graph(int vCount, std::map<int, std::map<int, double>>& vertex, std::vector<Edge>& edge, std::set<int>& activeID, std::set<int>& markID) {

    this->vList = std::vector<Vertex>();
    this->eList = std::vector<Edge>();

    this->vCount = vCount;
    for(int i = 0; i < vCount; i++) {
        bool ifactive = activeID.count(i)>0;
        this->vList.emplace_back(Vertex(i, ifactive, std::map<int, double>()));
    }
    this->eCount = 0;

    for(auto itE : edge){
        insertEdge(itE.src, itE.dst, itE.weight);
    }
    for(auto &itV : vList){
        if(vertex.count(itV.vertexID) > 0){
            //copy construct
            std::map<int, double> attr = std::map<int, double>(vertex[itV.vertexID]);
            itV.value = attr;
        }
        else{
            for(auto blank : markID){
                itV.value.insert(std::pair<int, double>(blank, INT32_MAX >> 1));
            }
        }
    }
}

void Graph::insertEdge(int src, int dst, double weight)
{
    this->eList.emplace_back(Edge(src, dst, weight));
    this->eCount++;
}