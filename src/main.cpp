#include <iostream>
#include <chrono>
#include <SFML/Graphics.hpp>
#include "node.h"
#include "beehive.cpp"
#include "queen.cpp"

int main() {
    Beehive BH = Beehive();
    // std::cout<<BH;
    const int SCALE = 4;
    const int WIDTH = MATRIX_COL * SCALE;
    const int HEIGHT = MATRIX_ROW * SCALE;
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Bees");
    sf::Clock clock;
    sf::Time elapsed;
      while (window.isOpen()){
        sf::Event event;
        while (window.pollEvent(event)){
            if (event.type == sf::Event::Closed)
                window.close();
        }
        std::vector<std::vector<Node>> b_matrix = BH.getMatrix();
        elapsed = clock.getElapsedTime();
        if (elapsed.asMilliseconds() > 10){
          window.clear();
          for (int i = 0; i < MATRIX_COL; ++i){
              for (int j = 0; j < MATRIX_ROW; ++j){
                  BH.run_reproducing(i,j);
                  Queen tmp = b_matrix[i][j].getData();
                  int ALPHA = tmp.getAlleys().getAlpha();
                  int BETA = tmp.getAlleys().getBeta();
                  sf::RectangleShape bee(sf::Vector2f(SCALE, SCALE));
                  bee.setPosition(i*SCALE, j*SCALE);
                  sf::Color *color;
                  int red = BETA + ALPHA, 
                  green = BETA + ALPHA, 
                  blue = 0;
                  if (tmp.isExist()) {
                    color = new sf::Color(red, green, blue);
                  }
                  else {
                    color = new sf::Color(sf::Color::White);
                  }
                  bee.setFillColor(*color);
                  window.draw(bee);
                  delete color;
                  clock.restart();
              }            
          }
          
          window.display();
        }
        
    }

    return 0;


}


