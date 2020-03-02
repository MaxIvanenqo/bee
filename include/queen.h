#pragma once
#include "defines.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>

class Coords{   
    public:
        Coords(const int & _x = -1, const int & _y = -1):x(_x), y(_y) {};
        int &getX(){ return this->x; }
        int &getY(){ return this->y; }
        void setXY(const int & x, const int & y){
            this->x = x;
            this->y = y;
        }
    private: int x, y;
};

class Alleys{
    public:
        Alleys(const int & _x = -1, const int & _y = -1):alpha(_x), beta(_y){};
        int &getAlpha(){ return this->alpha; }
        int &getBeta(){  return this->beta;  }
        void setAlleys(const int & alpha, const int & beta){  
            this->alpha = alpha;
            this->beta = beta;
        }
    private: int alpha, beta;
};

class Queen
{
public:

    Queen(const int & a = -1, const int & b = -1, const int & x = -1, const int & y = -1){
        this->alleys = Alleys(a, b); 
        this->coords = Coords(x, y);
        while(spermatecae_size--){
            int alley_for_spermatecae = 1 + rand() % MAX_ALLEY;
            int operation_condition_value = 1 + rand() % 2;
            if(!(std::find(this->spermatecae.begin(), this->spermatecae.end(), alley_for_spermatecae) != this->spermatecae.end()) && operation_condition_value < 2){
                this->spermatecae.push_back(alley_for_spermatecae);
            }
        }
    };
    Queen(bool, int x, int y){
        this->spermatecae_size = 0;
        this->alleys = Alleys(); // (false, x, y) -> empty place
        this->coords = Coords(x, y);
    };

    Queen * reproduce(std::vector<Queen> & _vq){
        this->alley_to_reproduce = this->find_an_alley(_vq);
        if (this->alley_to_reproduce != -1){
            int self_alley_choosing = rand()%2;
            if (self_alley_choosing == 1) this->self_alley = this->alleys.getAlpha();
            else this->self_alley = this->alleys.getBeta();
            if  (this->self_alley != this->alley_to_reproduce && 
                (rand() % (QTY_OF_BORN_OPTIONS*10) <= PROBABILITY_OF_QUEEN_BORNING)) {
                    return this;
                    // return Alleys(self_alley, alley_to_reproduce);
            }
        }
        return new Queen();
    }

    Coords getCoords() { return this->coords; }
    
    Alleys getAlleys() { return this->alleys; }

    Queen * new_queen_born();

    bool isExist();

    std::vector<int> getSpermatecae(){return this->spermatecae;}

    int getHP(){return this->HP;}

    void setAlleys(const int alpha, const int beta){this->alleys.setAlleys(alpha, beta);}

    void setCoords(const int x, const int y){this->coords.setXY(x, y);}

    int getAlleyToReproduce(){
        return this->alley_to_reproduce;
    }

    int getSelfAlley(){
        return this->self_alley;
    }
    void check_hp();

    ~Queen(){};
private:
    int HP = MAX_LIFE;
    int QTY_OF_BORN_OPTIONS = 2; // bee + queen
    int PROBABILITY_OF_QUEEN_BORNING = 5; // out of 20
    int alley_to_reproduce, self_alley;

    Coords coords;
    Alleys alleys;

    std::vector<int> spermatecae;   //alleys of drones for Queen use to bees reproduction
    int spermatecae_size = 11;      // top border for drones alleys quantity. Will be reduced in the constructor according to drawn value

    void death();
    bool spermatecae_is_empty();
    void choose_and_remove_alley(int & drawn_alley_for_reproducing, std::vector<int> & spermatecae);
    int find_an_alley(std::vector<Queen> & _vq);
};