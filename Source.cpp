#include "Operands.h"
#include <stdexcept>
#include <queue>
#include <stack>
#include <iostream>

double calculate(std::queue<Operand *>&);

int main()
{
    /* calculation:
     *  (6 + 8)^2 / (102 - 53) + (428 - 379) / 7 = 11
     *  - in RPN:
     *      -> 6
     *      -> 8 Add
     *      -> Square (2 pow)
     *      -> 102
     *      -> 53 Subtract Divide
     *      -> 428
     *      -> 379 Subtract
     *      -> 7 Divide Add
     *      -> 11
     */
    std::queue<Operand *> q;
    q.push(new Number(6));
    q.push(new Number(8));
    q.push(new Add);
    q.push(new Square);
    q.push(new Number(102));
    q.push(new Number(53));
    q.push(new Subtract);
    q.push(new Divide);
    q.push(new Number(428));
    q.push(new Number(379));
    q.push(new Subtract);
    q.push(new Number(7));
    q.push(new Divide);
    q.push(new Add);

    // Int Numbers convert to double result due to floating point division / multiplication
    try
    {
        std::cout << "Result: " << calculate(q) << std::endl;
    }
    catch(const std::exception& e)
    {
        std::cout << "EXCEPTION: " << e.what() << std::endl;
    }

    return 0;
}


double calculate(std::queue<Operand *>& q)
{
    // stack to hold numeric values used with RPN operations
    std::stack<double> numberStack;

    while(!q.empty())
    {
        // Base class pointer
        Operand* operandPtr = q.front(); 
        q.pop();

        // check if current Operand object is Number or Operator (Add, Subtract, Divide, Multiply, Square)
        Number* numberPtr = dynamic_cast<Number *>(operandPtr);
        if(numberPtr != nullptr)
        {
            // Downcasted before if to derived Number class to access number value member
            numberStack.push(numberPtr->value);
        }
        else if(dynamic_cast<Add *>(operandPtr) != nullptr)
        {
           double n1 = numberStack.top();
           numberStack.pop(); 
           double n2 = numberStack.top();
           numberStack.pop(); 

           numberStack.push(n2 + n1);
        }
        else if(dynamic_cast<Subtract *>(operandPtr) != nullptr)
        {
           double n1 = numberStack.top();
           numberStack.pop(); 
           double n2 = numberStack.top();
           numberStack.pop(); 

           numberStack.push(n2 - n1);
        }
        else if(dynamic_cast<Multiply *>(operandPtr) != nullptr)
        {
           double n1 = numberStack.top();
           numberStack.pop(); 
           double n2 = numberStack.top();
           numberStack.pop(); 

           numberStack.push(n2 * n1);
        }
        else if(dynamic_cast<Divide *>(operandPtr) != nullptr)
        {
           double n1 = numberStack.top();
           numberStack.pop(); 
           double n2 = numberStack.top();
           numberStack.pop(); 

           numberStack.push(n2 / n1);
        }
        else if(dynamic_cast<Square *>(operandPtr) != nullptr)
        {
           double n = numberStack.top();
           numberStack.pop();

           numberStack.push(n * n);
        }
        
        // points to popped element, delete allocated memory
        delete operandPtr;
    }
    
    if(numberStack.size() != 1)
    {
        // exception arises processing data during runtime
        throw std::runtime_error("Stack size not equal 1 after calculation.");
    }
    
    return numberStack.top();
}
