#ifndef NUMBER_H
#define NUMBER_H
#include "atom.h"
#include "variable.h"
#include <string>

using namespace std;

class Variable;
class Atom;
class Number{
public:
  Number(int v);
  string symbol();
  string value();

  bool match(Atom atom);

  bool match( Variable& X );

  bool match( Number num );

private:
  int _value;
  string _symbol;
  bool _assignable = true;

};



#endif