%module example
%{
  #include "example.cpp"
%}

class Quack {
private:
  int x;
public:
  Quack();
  ~Quack();
  void doQuack();
};
