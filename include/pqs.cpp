#include "pqs.h"

PQ::PQ(){

}

void PQ::Insert(state *s, std::pair<double, double> k)
{
  s->k = k;
  storage.insert(s);
  present.insert(s);
}

void PQ::Update(state *s, std::pair<double, double> k)
{
  it = storage.find(s);
  if (it == storage.end()){
    std::cout << "AAAAAAAAAAAAAAAAAAAAAAAAAAAAA" << std::endl;
    return;
  }

  storage.erase(s);
  s->k = k;
  storage.insert(s);
}

priority PQ::TopKey()
{
  it = storage.begin();
  return (*it)->k;
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
  it = storage.begin();
  return (*it);
}

state *PQ::Pop()
{
  state *ans;
  it = storage.begin();
  ans = Top();
  storage.erase(*it);
  return ans;
}

bool PQ::Present(state *s)
{
  it = storage.find(s);
  return (it != storage.end());
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

void PQ::ReturnAllEntries(std::vector<state*> &v){
  v.clear();
  for(it = storage.begin(); it != storage.end(); it++){
    v.push_back(*it);
  }
}