#ifndef OPERANDS_H
#define OPERANDS_H

// base class operand
class Operand
{
public:
    virtual ~Operand();
};

class Number : public Operand
{
public:
    Number(double val);
    double value;
};

class Operator : public Operand
{
    // Empty
};

class Add : public Operator
{
    // Empty
};

class Subtract : public Operator
{
    // Empty
};

class Multiply : public Operator
{
    // Empty
};

class Divide : public Operator
{
    // Empty
};

class Square : public Operator
{
    // Empty
};
#endif
