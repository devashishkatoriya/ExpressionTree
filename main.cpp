//Expression Tree

/*
 * Created By Devashish Katoriya on 07-02-2017
 */

#include<iostream>

using namespace std;

#define LIMIT 200

//Function Prototypes
bool isOperand(char);
bool isOperator(char);

//Class definitions
class node															//Node Class
{
public :
    char data;
    node *LChild,*RChild;
};

template<typename T>
class stack															//Stack Class
{
    T arr[LIMIT];
    int top;
public :
    stack()
    {
        top = 0;
    }
    void push(T s)
    {
        if(!isFull())
        {
            arr[top] = s;
            top++;
        }
        else
        {
            cout<<"\nStack Overflow!";
        }
    }
    T pop()
    {
        if(!isEmpty())
        {
            return arr[--top];
        }
        else
        {
            cout<<"\nStack Underflow!";
        }
    }
    bool isEmpty()
    {
        return top == 0;
    }
    bool isFull()
    {
        return top == LIMIT;
    }
};

class expression_tree													//Tree Class
{
    node *root;
    node *create();
    
public :
    expression_tree()
    {
        root = NULL;
    }
    node *retRoot()
    {
        return root;
    }
    void clr()
    {
        root = NULL;
    }
    bool isEmpty()
    {
        return root == NULL;
    }
    void construct();
    void inOrder(node *);
    void in_itr(node *);
    void post_itr(node *);
    void swap(node *);
};

node *expression_tree::create()											//create()
{
    node *s;
    s = new node;
    if(s==NULL)
    {
        cout<<"\nMemory Not Allocated!";
        return NULL;
    }
    cout<<"Enter next char : ";
    cin>>s->data;
    s->LChild = NULL;
    s->RChild = NULL;

    return s;
}

void expression_tree::construct()                                        //construct()
{
    node *curr,*t1,*t2;
    stack<node *> s;

    cout<<"\nEnter Post Order sequence :- \n\n";

    while(1)
    {
        curr = create();
        if(isOperand(curr->data))
        {
            s.push(curr);
        }
        else if(isOperator(curr->data))
        {
            t2 = s.pop();
            t1 = s.pop();

            curr->LChild = t1;
            curr->RChild = t2;

            s.push(curr);
        }
        else
        {
            root = s.pop();
            break;
        }
    }

    cout<<"\nTree created Successfully!";
}

void expression_tree::in_itr(node *s1)								//In order Iterative
{
    node *temp;
    temp = s1;
    stack <node *>s;
    while(1)
    {
        while(temp!=NULL)
        {
            s.push(temp);
            temp = temp->LChild;
        }
        if(s.isEmpty())
            return;
        temp = s.pop();
        cout<<temp->data;
        temp = temp->RChild;
    }
}

void expression_tree::inOrder(node *s1)								//in order()
{
    if(s1!=NULL)
    {
        inOrder(s1->LChild);
        cout<<s1->data;
        inOrder(s1->RChild);
    }

}

void expression_tree::post_itr(node *r)								//Post order Iterative
{
    node *temp;
    temp = r;
    stack <node *>s;
    stack <char>s2;
    char flag;

    while(1)
    {
        while(temp!=NULL)
        {
            s.push(temp);
            s2.push('L');
            temp = temp->LChild;
        }
        if(s.isEmpty())
            return;
        temp = s.pop();
        flag = s2.pop();
        if(flag=='R')
        {
            cout<<temp->data;
            temp = NULL;
        }
        else
        {
            s.push(temp);
            s2.push('R');
            temp = temp->RChild;
        }
    }
}

void expression_tree::swap(node *r)
{
    node *temp;
    if(r!=NULL)
    {
        swap(r->LChild);
        swap(r->RChild);
        
        temp = r->LChild;
        r->LChild = r->RChild;
        r->RChild = temp;
    }
}

//main()
int main()
{
    expression_tree obj;
    int ch;
    char choice;
    cout<<"\nProgram to create Expression Tree.";
    do
    {
        ch = 0;
        choice = 'n';
        cout<<"\n\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~";
        cout<<"\n 1 for Construction and Insertion";
        cout<<"\n 2 for In order Recursive";
        cout<<"\n 3 for In order Iterative";
        cout<<"\n 4 for Post order Iterative";
        cout<<"\n 5 for Swapping";
        cout<<"\n 6 for Root Node";
        cout<<"\n -1 to Clear whole Tree";
        cout<<"\n 0 to  Quit";
        cout<<"\nEnter your choice : ";
        cin>>ch;
        cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
        switch(ch)
        {
            case 1 : obj.construct();
                break;
            case 2 : cout<<"\nIn order Traversal is ";
                obj.inOrder(obj.retRoot());
                break;
            case 6 : if(!obj.isEmpty())
                    cout<<"\nRoot Node is "<<obj.retRoot()->data;
                else
                    cout<<"\nEmpty Tree!";
                break;
            case 3 : cout<<"\nIn order Iterative is ";
                obj.in_itr(obj.retRoot());
                break;
            case 4 : cout<<"\nPost order Iterative is ";
                obj.post_itr(obj.retRoot());
                break;
            case 5 : obj.swap(obj.retRoot());
                cout<<"\nNodes Swapped Successfully!";
                break;
            case -1 : cout<<"\nAre you sure you want to clear tree (y/n) ? ";
                cin>>choice;
                if(choice=='y'||choice=='Y')
                {
                    obj.clr();
                    cout<<"\nTree Cleared Successfully!";
                }
                else
                    cout<<"\nCancelled!";
            case 0 : break;
            default : cout<<"\nInvalid Option!";
        }

        /*
        if(ch!=0)
        {
            cout<<"\n\n\n\n\n\n\nPress any key to continue...";
            cin.ignore();
            cin.get();
        }
        */
    }while(ch!=0);

    cout<<"\nThank you for using this program :) \n\n";
    return 0;
}

//Various Functions
bool isOperand(char c)
{
    if((c>='a' && c<='z') || (c>='A' && c<='Z') || (c>='0' && c<='9'))
        return true;
    else
        return false;
}

bool isOperator(char c)
{
    if(c=='+' || c=='-' || c=='*' || c=='/')
        return true;
    else
        return false;
}

/* OUTPUT



*/
