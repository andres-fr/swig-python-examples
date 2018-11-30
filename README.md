Basic examples to illustrate the extension of Python2/3 with C/C++ code using SWIG and gcc/g++, tested in Ubuntu.


The syntax for SWIG interface files is well explained [here](The syntax for SWIG interface files is well explained [here]/https://www.ibm.com/developerworks/aix/library/au-swig/index.html).



# 1. FUNCTION-C-EXAMPLE:


### `example.c`

For our basic example, write a simple C function:

```c
int fact(int n) {
  if (n <= 1) return 1;
  else return n*fact(n-1);
}
```

### `example.i`

The SWIG interface file tells to expose the implemented C function.

```
%module example
%{
  extern int fact(int n);
%}
extern int fact(int n);
```

### Build+Run it for Python2:

In bash, `cd` into the folder and run the following:

```bash
swig -python example.i
gcc -fPIC -c example.c example_wrap.c -I /usr/include/python2.7
gcc -shared example.o example_wrap.o -o _example.so
python2.7 -c "import example; print example.fact(5)"
```

### Build+Run it for Python3:

```bash
swig -python example.i
gcc -fPIC -c example.c example_wrap.c -I /usr/include/python3.6
gcc -shared example.o example_wrap.o -o _example.so
python3.6 -c "import example; print(example.fact(5))"
```







# 2. CLASS-CPP-EXAMPLE:

This time using a basic C++ class. The commands also vary slightly. Note how private field `x` is not accessible. [http://www.swig.org/Doc1.3/SWIGDocumentation.html#SWIGPlus_nn15](Docs): "SWIG wraps class members that are public following the C++ conventions, i.e., by explicit public declaration or by the use of the using directive. In general, anything specified in a private or protected section will be ignored".


### `example.cpp`

```cpp
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
```


### `example.i`

```
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
```


### Build+Run it for Python2:

In bash, `cd` into the folder and run the following:

```bash
swig -c++ -python example.i
g++ -fPIC -c example.cpp example_wrap.cxx -I /usr/include/python2.7
g++ -shared example.o example_wrap.o -o _example.so
python2.7 -c "import example; q=example.Quack(); q.doQuack()"
```

### Build+Run it for Python3:

```bash
swig -c++ -python example.i
g++ -fPIC -c example.cpp example_wrap.cxx -I /usr/include/python3.6
g++ -shared example.o example_wrap.o -o _example.so
python3.6 -c "import example; q=example.Quack(); q.doQuack()"
```












# 3. HEADER-STRUCT-C-EXAMPLE:

### `example.h`

```c
#ifndef EXAMPLE_H_
#define EXAMPLE_H_

#include <stdlib.h>

typedef struct pair {
  float x;
  float y;
} pair;

pair* CreatePair(float x, float y);

pair* AddPairs(const pair* p1, const pair* p2);

#endif // EXAMPLE_H_
```

### `example.c`

```c
#include "example.h"

pair* CreatePair(float x, float y){
  pair* result = (pair*)malloc(sizeof(pair));
  result->x = x;
  result->y = y;
  return result;
};

pair* AddPairs(const pair* p1, const pair* p2){
  pair* result = (pair*)malloc(sizeof(pair));
  result->x = p1->x + p2->x;
  result->y = p1->y + p2->y;
  return result;
}
```

### `example.i`

```
%module example

%{
#include "example.h"
%}

%include "example.h"
```

### Build+Run it for Python2:

In bash, `cd` into the folder and run the following:

```bash
swig -python example.i
gcc -fPIC -c example.c example_wrap.c -I /usr/include/python2.7
gcc -shared example.o example_wrap.o -o _example.so
python2.7 -c "from example import *; p = AddPairs(CreatePair(1.2,3.4), CreatePair(10,100)); print p.x, p.y"
```

### Build+Run it for Python3:

```bash
swig -python example.i
gcc -fPIC -c example.c example_wrap.c -I /usr/include/python3.6
gcc -shared example.o example_wrap.o -o _example.so
python3.6 -c "from example import *; p = AddPairs(CreatePair(1.2,3.4), CreatePair(10,100)); print(p.x, p.y)"
```

