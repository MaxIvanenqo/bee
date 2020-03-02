#include "queen.h"

Queen * Queen::new_queen_born(){
  return this;
}

void Queen::check_hp(){
  this->HP -= rand()%5;
  if (this->HP <= 0) {
    this->death();
  };
}

void Queen::death(){
  this->alleys.setAlleys(-1, -1);
}

bool Queen::isExist(){
  return (this->alleys.getAlpha() > 0 && this->alleys.getBeta() > 0) ? true : false;
}

bool Queen::spermatecae_is_empty(){
  return (this->spermatecae.size() > 0) ? false : true;
}

void Queen::choose_and_remove_alley(int & drawn_alley_for_reproducing, std::vector<int> & spermatecae){
  if (spermatecae.empty()) return;
  int index_of_alley_in_spermatecae = (spermatecae.size() == 1)? 0 : rand() % (spermatecae.size() - 1);
  drawn_alley_for_reproducing = spermatecae[index_of_alley_in_spermatecae];
  spermatecae.erase(spermatecae.begin() + index_of_alley_in_spermatecae);
}

int Queen::find_an_alley(std::vector<Queen> & _vq){
  int drawn_alley_for_reproducing = -1;
  if (!this->spermatecae_is_empty()){
    choose_and_remove_alley(drawn_alley_for_reproducing, this->spermatecae);
  } else{
    for(auto each : _vq){
      if (!each.isExist() || each.spermatecae_is_empty()) continue;
        choose_and_remove_alley(drawn_alley_for_reproducing, each.spermatecae);
      }
    }
  return drawn_alley_for_reproducing;
}
