# include <iostream>
# include <stack>

using namespace std;

template <class T>
class StackExt {
    stack<T> pilha;
    stack<T> min;
public:
	StackExt() {};
	bool empty() const; 
	T &top();
	void pop();
	void push(const T & val);
	T &findMin();
};

// a alterar
template <class T> 
bool StackExt<T>::empty() const
{
    return pilha.empty();
}

//a alterar
template <class T> 
T& StackExt<T>::top()
{
    return pilha.top();
}

//a alterar
template <class T> 
void StackExt<T>::pop()
{
    if(pilha.top()==min.top())
        min.pop();
    pilha.pop();
}

//a alterar
template <class T> 
void StackExt<T>::push(const T & val)
{
    pilha.push(val);
    if(!min.empty()){
        if(val<=min.top()) {
            min.push(val);
        }
    }else{min.push(val);}

}

//a alterar
template <class T> 
T& StackExt<T>::findMin()
{
    return min.top();
}

