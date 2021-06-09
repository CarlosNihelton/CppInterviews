#include "exclude_intersects.h"

using namespace std;

bool noIntersect(const pair<int,int>& p1, const pair<int,int>& p2){
  return (p1.second<p2.first || p1.first>p2.second);
}
bool isContained(const pair<int,int>& p1, const pair<int,int>& p2){
  return (p1.first>p2.first && p1.second<p2.second);
}
bool intersectsRight(const pair<int,int>& p1, const pair<int,int>& p2){
  return (p1.first>p2.first && p1.second>p2.second);
}
bool intersectsLeft(const pair<int,int>& p1, const pair<int,int>& p2){
  return (p1.first<p2.first && p1.second<p2.second);
}

vector<pair<int,int>> removeInterval(vector<pair<int,int>> intervals, pair<int,int> toBeRemoved){
  vector<pair<int,int>> unified;

  for(auto p : intervals){
    if(isContained(p,toBeRemoved)){
      continue;
    }
    else if(noIntersect(toBeRemoved,p))
    unified.push_back(p);
    else if(isContained(toBeRemoved,p)){
      unified.push_back(make_pair(p.first,toBeRemoved.first));
      unified.push_back(make_pair(toBeRemoved.second,p.second));
    }
    else if(intersectsLeft(toBeRemoved,p)){
      unified.push_back(make_pair(toBeRemoved.second,p.second));
    }
    else if(intersectsRight(toBeRemoved,p)){
      unified.push_back(make_pair(p.first,toBeRemoved.first));
    }
  }
  return unified;
}

void print_comparison(vector<pair<int,int>>expected, vector<pair<int,int>>actual){
  std::cout << "== Expected:\n[";
  for(auto p : expected){
    std::cout << '['<<p.first<<','<<p.second<<']';
  }
  std::cout << "]\n== Found:\n[";
  for(auto p : actual){
    std::cout << '['<<p.first<<','<<p.second<<']';
  }
  std::cout << "]\n\n";
}

int main(){
  vector<pair<int,int>> intervals{{0,2},{3,4},{5,7}};
  pair<int,int> toBeRemoved{1,6};
  vector<pair<int,int>> result{{0,1},{6,7}};

  auto real = removeInterval(intervals,toBeRemoved);
  print_comparison(result,real);

  intervals={{0,5}};
  toBeRemoved={2,3};
  result={{0,2},{3,5}};

  real = removeInterval(intervals,toBeRemoved);
  print_comparison(result,real);

  intervals={{-5,-4},{-3,-2},{1,2},{3,5},{8,9}};
  toBeRemoved={-1,4};
  result={{-5,-4},{-3,-2},{4,5},{8,9}};

  real = removeInterval(intervals,toBeRemoved);
  print_comparison(result,real);

  return 0;
}
