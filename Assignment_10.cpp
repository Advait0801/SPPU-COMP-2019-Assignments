#include <iostream>
#include <string>
#include <locale>

using namespace std;

// infix to postfix
// avaluation
// precedence func2

template<class T>
class stack
{
    int size;
    int top;
    T *arr;

public:
    stack()
    {
        size = 10000;
        arr = new T(size);
        top = -1;
    }

    void push(T x)
    {
        if (isFull())
        {
            cout << "Stack Overflow.!" << endl;
        }
        else
        {
            top++;
            arr[top] = x;
        }
    }

    T pop()
    {
        if (isEmpty())
        {
            cout << "Stack underflow!" << endl;
        }
        else
        {
            T poppedItem = arr[top];
            arr[top] = '-';
            top--;

            return poppedItem;
        }
    }
    bool isEmpty()
    {
        if (top == -1)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    char peek()
    {
        return arr[top];
    }
    void display()
    {
        int i = top;
        while (i >= 0)
        {
            cout << arr[i] << endl;
            i--;
        }
        cout << endl;
    }

    bool isFull()
    {
        if (top == size)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
};

class toPostfix
{
    string result = "";
    stack<char> p;
    string infixStr;

public:
    toPostfix()
    {
        cout << "Enter expression:";
        cin >> infixStr;
    }

    int checkPreced(char ch)
    {
        if (ch == '+' || ch == '-')
        {
            return 1;
        }
        else if (ch == '*' || ch == '/')
        {
            return 2;
        }
        else
            return 0;
    }

    string infixTopost()
    {
        p.push('$');

        for (int i = 0; i < infixStr.length(); i++)
        {
            if (isalnum(infixStr[i]))
            {
                result += infixStr[i];
            }

            else if (infixStr[i] == '(')
            {
                p.push(infixStr[i]);
            }
            else if (infixStr[i] == ')')
            {
                while (p.peek() != '$' && p.peek() != '(')
                {
                    result += p.pop();
                }
                p.pop();
            }

            else
            {
                if (checkPreced(infixStr[i]) > checkPreced((char)p.peek()))
                {
                    p.push(infixStr[i]);
                }
                else
                {
                    while (p.peek() != '$' && checkPreced((char)p.peek()) >= checkPreced(infixStr[i]))
                    {
                        result += p.peek();
                        p.pop();
                    }

                    p.push(infixStr[i]);
                }
            }
        }

        while(p.peek()!='$')
        {
            result+=p.peek();
            p.pop();
        }

        return result;
    }

   void evalExp()
{
    string exp;
    cout<<"Enter postfix expression with values: ";
    cin>>exp;

    stack<float> result;
    for(int i=0;i<exp.length();i++)
    {
        if(isdigit(exp[i]))
        {
            result.push((float)(exp[i]-'0'));
        }
        else{
            float num1 = result.pop();
            float num2 = result.pop();
            float value=0;
            switch (exp[i])
            {
                case '+':
                value = num1+num2;
                break;

                case '-':
                value = num2-num1;
                break;

                case '*':
                value = num2*num1;
                break;

                case '/':
                value = num2/num1;
                break;

                default:
                break;
            }

            result.push(value);
        }
    }
    cout<<"Answer : "<<(float)result.peek()<<endl;
}

};


int main()
{
    int flag =1;
    while(flag)
    {
        toPostfix obj;
        cout<<obj.infixTopost()<<endl;
        obj.evalExp();
        cout<<"-------------------------"<<endl;


        cout<<"1 Continue\n0 Exit"<<endl;
        cin>>flag;
    }
    
    return 0;
}