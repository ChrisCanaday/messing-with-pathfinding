#include "pqs.h"

void PQ::Insert(state *s, std::pair<double, double> k)
{
  s->k = k;
  storage.insert(s);
}

void PQ::Update(state *s, std::pair<double, double> k)
{
  if (storage.find(s) == storage.end()) return;

  storage.erase(s);
  s->k = k;
  storage.insert(s);
}

priority PQ::TopKey()
{
  return (*storage.begin())->k;
}

void PQ::Remove(state *s)
{
  storage.erase(s);
}

bool PQ::Empty()
{
  return storage.empty();
}

state *PQ::Top()
{
  return (*storage.begin());
}

state *PQ::Pop()
{
  state *ans = Top();

  storage.erase(*storage.begin());
  return ans;
}

bool PQ::Present(state *s)
{
  return (storage.find(s) != storage.end());
}

void PQ::Print()
{
  for (it = storage.begin(); it != storage.end(); it++){
    std::cout << "i -- " << (*it)->i << " j -- " << (*it)->j << std::endl;
    std::cout << "g -- " << (*it)->g << " rhs -- " << (*it)->rhs << std::endl;
    std::cout << "k1 -- " << (*it)->k.first << " k2 -- " << (*it)->k.second << std::endl << std::endl;
  }
}

int PQ::GetSize()
{
  return storage.size();
}

void PQ::GetAllNodes(std::vector<state*> &v){
  v.clear();

  for(it = storage.begin(); it != storage.end(); it++){
    v.push_back(*it);
  }
}

void PQ::Clear(){
  storage.clear();
}