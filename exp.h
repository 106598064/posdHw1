#ifndef EXP_H
#define EXP_H

#include "atom.h"
#include <vector>
#include <iostream>

using namespace std;

class Exp {
public:
  virtual bool evaluate() = 0;
  virtual string getResult() = 0;
};


class MatchExp : public Exp {
public:
  MatchExp(Term* left, Term* right): _left(left), _right(right){

  }

  bool evaluate(){
    return _left->match(*_right);
  }


  string getResult() {
    if(evaluate())
    {
      if( _left->symbol() == _right->symbol())
      {
        return "true";
      }
      return _left->symbol() + " = " + _right->value();
    }else{
        return "false";
    }
  }

private:
  Term* _left;
  Term* _right;
};

class ConjExp : public Exp {
public:
  ConjExp(Exp *left, Exp *right) : _left(left), _right(right) {

  }

  bool evaluate() {
    return (_left->evaluate() && _right->evaluate());
  }

  string getResult() {
    evaluate();
    if (_left->getResult() == "false" || _right->getResult() == "false"){
      return "false";
    }else if (_right->getResult() == "true" || _left->getResult().find(_right->getResult()) != string::npos){
      return _left->getResult();
      //cout<<YYY<<endl;
    }else if (_left->getResult() == "true" && _right->getResult() == "true"){
      return "true";
    }else if (_left->getResult() == "true"){
      return _right->getResult();
    }else{
      return _left->getResult() + ", " + _right->getResult();
    }
  }

private:
  Exp * _left;
  Exp * _right;
};

class DisjExp : public Exp {
public:
  DisjExp(Exp *left, Exp *right) : _left(left), _right(right) {

  }

  bool evaluate() {
    return (_left->evaluate() || _right->evaluate());
  }

  string getResult() {
    evaluate();
    if (_right->getResult() == "false")
    {
      return _left->getResult();
      //cout<<"FFFF"<<endl;
    }else if (_left->getResult() == "false")
    {
      //cout<<"SSSS"<<endl;
      return _right->getResult();
    }else{
      return _left->getResult() + "; " + _right->getResult();
    }
  }

private:
  Exp * _left;
  Exp * _right;
};


#endif
