#include <iostream>

class Quack {
private:
  int x;
public:
  Quack() : x(10){}
  ~Quack(){}
  void doQuack(){
    for (int i=1; i<=this->x; ++i){
      std::cout << i << " quack" << std::endl;
    }
  }
};
