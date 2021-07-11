#include "maxsubarray.h"

int kadane(std::vector<int> input){
  int _inf = -1*std::numeric_limits<int>::max();
  int best_sum=_inf, current_sum=0;
  for(auto x : input){
    current_sum = std::max(x,current_sum+x);
    best_sum = std::max(best_sum,current_sum);
  }
  return best_sum;
}

int main (int argc, char* argv[]){
  std::array<std::vector<int>,4> inputs {{{-2,1,-3,4,-1,2,1,-5,4},{1},{5,4,-1,7,8},{-5,-9,-1,-3,-6}}};
  std::array<int, 4> outputs{6,1,23,-1};
  for(int i=0; i<4; ++i){
    int result = kadane(inputs[i]); 
    std::cout<<"Iteration " << i << " expected: " << outputs[i] << " result was: "  << result << '\n';
    assert(outputs[i]==result);
  }
}
