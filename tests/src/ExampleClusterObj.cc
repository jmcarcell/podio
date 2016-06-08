#include "ExampleClusterObj.h"
#include "ExampleCluster.h"



ExampleClusterObj::ExampleClusterObj() :
    ObjBase{{podio::ObjectID::untracked,podio::ObjectID::untracked},0}, data(), m_Hits(new std::vector<ExampleHit>()), m_Clusters(new std::vector<ExampleCluster>())
{ }

ExampleClusterObj::ExampleClusterObj(const podio::ObjectID id, ExampleClusterData data) :
    ObjBase{id,0}, data(data)
{ }

ExampleClusterObj::ExampleClusterObj(const ExampleClusterObj& other) :
    ObjBase{{podio::ObjectID::untracked,podio::ObjectID::untracked},0}
    , data(other.data), m_Hits(new std::vector<ExampleHit>(*(other.m_Hits))), m_Clusters(new std::vector<ExampleCluster>(*(other.m_Clusters)))
{ }

ExampleClusterObj::~ExampleClusterObj() {
  if (id.index == podio::ObjectID::untracked) {
    delete m_Hits;
    delete m_Clusters;

  }

}
