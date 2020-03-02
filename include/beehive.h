#pragma once
#include "defines.h"
#include "queen.h"
#include "node.h"
#include <iostream>
#include <iomanip>
#include <vector>

class Beehive
{
private:
    std::vector<std::vector<Node>> matrix;
    std::string convert_int_data_to_string(int data);
public:
	Beehive();
    void run_reproducing(int i, int j);
    std::vector<std::vector<Node>> & getMatrix() {
        return this->matrix;
    }
    
    friend std::ostream& operator<< (std::ostream & a, Beehive & hive){
        a<<"Beehive: "<<std::endl;
        a<<"\33[1;31m** \33[m" << "- " << "free space" << std::endl;
        a<<"15 - "<<"alleys of queen"<<std::endl<<std::endl;
        for (int i = 0; i <= MATRIX_COL; ++i){
            for (int j = 0; j <= MATRIX_ROW; ++j)
            {
                int alley_alpha = hive.matrix[i][j].getData().getAlleys().getAlpha();
                int alley_beta = hive.matrix[i][j].getData().getAlleys().getBeta();
                std::string data_1 = hive.convert_int_data_to_string(alley_alpha); //adding zero before one sign number
                std::string data_2 = hive.convert_int_data_to_string(alley_beta);  //for better view
             
                (alley_alpha == -1 || alley_beta == -1)?
                    a << "\33[1;34m|\33[m" << std::setw(3) << "" <<"\33[1;31m**  \33[m"  << " "
                    :
                    a << "\33[1;34m| \33[m" <<  data_1 << ", " << data_2 << " ";
            }
            a << std::setw(9) << "\33[1;34m| \33[m" << std::endl;
            a << std::endl;
        }
        a<<std::endl;
        return a;
    };

    ~Beehive(){};
};