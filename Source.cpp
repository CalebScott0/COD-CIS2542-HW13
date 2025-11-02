#include "Operands.h"
#include <queue>
#include <iostream>

double calculate(std::queue<Operand *>&);

int main()
{
    /* calculation:
     *  (6 + 8)^2 / (102 - 53) + (428 - 379) / 7 = 11
     *  - in RPN:
     *      -> 6
     *      -> 8 +
     *      -> Square (2 pow)
     *      -> 102
     *      -> 53 - Divide
     *      -> 429
     *      -> 379 -
     *      -> 7 Divide +
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
    q.push(new Number(429));
    q.push(new Number(379));
    q.push(new Subtract);
    q.push(new Number(7));
    q.push(new Divide);
    q.push(new Add);

    // Int Numbers convert to double result due to floating point division / multiplication
    // double result is ~11.143 if containers were set up for int this would be 11
    std::cout << static_cast<int>(calculate(q)) << std::endl;




    return 0;
}


double calculate(std::queue<Operand *>& q)
{
    // TODO: If you don't correctly set up the calculation code,
    //   the stack might become empty too soon. Throw an exception of some kind if this happens.

    
    // stack to hold numeric values used with RPN operations
    std::stack<double> numbers;

    while(!q.empty())
    {
        // Base class pointer
        Operand* o = q.front(); 
        q.pop();

        // check if current Operand object is Number or Operator (Add, Subtract, Divide, Multiply, Square)
        if(dynamic_cast<Number *>(o) != nullptr)
        {
            // Downcast to derived Number class to access number value member
            Number* n = dynamic_cast<Number *>(o);
            numbers.push(n->number);
        }
        else if(dynamic_cast<Add *>(o) != nullptr)
        {
           double n1 = numbers.top();
           numbers.pop(); 
           double n2 = numbers.top();
           numbers.pop(); 

           numbers.push(n2 + n1);
        }
        else if(dynamic_cast<Subtract *>(o) != nullptr)
        {
           double n1 = numbers.top();
           numbers.pop(); 
           double n2 = numbers.top();
           numbers.pop(); 

           numbers.push(n2 - n1);
        }
        else if(dynamic_cast<Multiply *>(o) != nullptr)
        {
           double n1 = numbers.top();
           numbers.pop(); 
           double n2 = numbers.top();
           numbers.pop(); 

           numbers.push(n2 * n1);
        }
        else if(dynamic_cast<Divide *>(o) != nullptr)
        {
           double n1 = numbers.top();
           numbers.pop(); 
           double n2 = numbers.top();
           numbers.pop(); 

           numbers.push(n2 / n1);
        }
        else if(dynamic_cast<Multiply *>(o) != nullptr)
        {
           double n1 = numbers.top();
           numbers.pop(); 
           double n2 = numbers.top();
           numbers.pop(); 

           numbers.push(n2 * n1);
        }
        else if(dynamic_cast<Square *>(o) != nullptr)
        {
           double n = numbers.top();
           numbers.pop();

           numbers.push(n * n);
        }

    }

    return numbers.top();

}
