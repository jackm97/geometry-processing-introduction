#include "euler_characteristic.h"
#include "edges.h"
#include <igl/euler_characteristic.h>
#include <vector>
#include <algorithm>

int euler_characteristic(const Eigen::MatrixXi &F)
{
  int Chi = 0;
  
  Eigen::MatrixXi E = edges(F);
  
  std::vector<int> verts(F.data(), F.data() + F.size());
  std::sort(verts.begin(), verts.end());
  std::vector<int>::iterator it;
  it = std::unique(verts.begin(),verts.end());
  int Vabs = std::distance(verts.begin(),it);

  Chi = Vabs - E.rows() + F.rows();
  
  return Chi;
}
