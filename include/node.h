#pragma once
#include <iostream>
#include "queen.h"

class Node{
	private:
	  Queen data;
	public:
		Node(const Queen & data = Queen()){
			this->data = data;
		};
		Queen & getData(){
			return this->data;
		}

		~Node(){}
};