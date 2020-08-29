#include "edges.h"
#include <vector>
#include <algorithm>

Eigen::MatrixXi edges(const Eigen::MatrixXi &F)
{
  Eigen::MatrixXi E(F.rows() * 3, 2);
  Eigen::MatrixXi ETmp(F.rows() * 3, 2);

  ETmp << F.block(0,0,F.rows(),2), F.block(0,1,F.rows(),2), F.col(2), F.col(0);
  E.block(0,0,E.rows(),1) = (ETmp.col(0).array() < ETmp.col(1).array()).select(ETmp.block(0,0,ETmp.rows(),1),ETmp.block(0,1,ETmp.rows(),1));
  E.block(0,1,E.rows(),1) = (ETmp.col(0).array() > ETmp.col(1).array()).select(ETmp.block(0,0,ETmp.rows(),1),ETmp.block(0,1,ETmp.rows(),1));
  ETmp = E;

  std::vector<int> edge(2,-1);
  std::vector<std::vector<int>> edgeVec(ETmp.rows(),edge);
  for (int i = 0; i < ETmp.rows(); i++)
  {
    edge[0] = ETmp(i,0);
    edge[1] = ETmp(i,1);
    edgeVec[i] = edge;
  }

  std::sort(edgeVec.begin(), edgeVec.end());

  std::vector<std::vector<int>>::iterator it;
  it = std::unique(edgeVec.begin(),edgeVec.end());
  edgeVec.resize(std::distance(edgeVec.begin(),it));

  E.resize(edgeVec.size(),2);

  for (int i=0; i<edgeVec.size(); i++)
  {
    E(i,0) = edgeVec[i][0];
    E(i,1) = edgeVec[i][1];
  }
  
  return E;
}
