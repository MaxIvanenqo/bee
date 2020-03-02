#include "beehive.h"

Beehive::Beehive(){      
  for (int i = 0; i < MATRIX_COL; ++i){
    std::vector<Node> tmp;
    for (int j = 0; j < MATRIX_ROW; ++j){
      Queen qInstance;
      int x1 = rand()%MAX_ALLEY; 
      int x2;
      do x2 = rand()%MAX_ALLEY;
      while (x1 == x2);
      int queen_init_condition_int = rand() % 20000;
      queen_init_condition_int <= (10) 
        ?
        tmp.push_back(Node(Queen(x1, x2, i, j)))
        :
        tmp.push_back(Node(Queen(false, i, j)));
    }
    matrix.push_back(tmp);
  }
}

void Beehive::run_reproducing(int i, int j){
      if (!this->matrix[i][j].getData().isExist()) return;
      int currX = this->matrix[i][j].getData().getCoords().getX();
      int currY = this->matrix[i][j].getData().getCoords().getY();
      if (currX == -1 || currY == -1) return;
      else {
          std::vector<Queen> _vq;
          for (int x = currX - 1; x <= currX + 1; ++x){    // O(1)
            for (int y = currY - 1; y <= currY + 1; ++y){
              if (x < 0 || y < 0 || x == MATRIX_COL || y == MATRIX_ROW) continue;
              _vq.push_back(this->matrix[x][y].getData()); // group of cells where DRONS alley could be found
            }
          }
          Queen reproduce_response = *(this->matrix[i][j].getData().reproduce(_vq));
          int alpha = reproduce_response.getAlleys().getAlpha();
          int beta = reproduce_response.getAlleys().getBeta();

          if (alpha != -1 && beta != -1) {  // new Queen was born
              int old_alpha = reproduce_response.getAlleys().getAlpha();
              int old_beta = reproduce_response.getAlleys().getBeta();
              int x = reproduce_response.getCoords().getX();
              int y = reproduce_response.getCoords().getY();
              this->matrix[x][y].getData() = Queen(reproduce_response.getAlleyToReproduce(), reproduce_response.getSelfAlley(), x, y);
              int random_index_in_vq = rand() % (_vq.size() - 1);
              if (!(_vq[random_index_in_vq].isExist())){
                int new_x = _vq[random_index_in_vq].getCoords().getX();
                int new_y = _vq[random_index_in_vq].getCoords().getY();
                this->matrix[new_x][new_y] = Node(Queen(old_alpha, old_beta, new_x, new_y));
              }
          }
      }
  this->matrix[i][j].getData().check_hp();
}


std::string Beehive::convert_int_data_to_string(int data){
  std::string data_str = std::to_string(data);
  if (data < 10 && data > 0)
    data_str = "0" + std::to_string(data);
  return data_str;
}