#include "WagonStack.h"

const int WagonStack::DEFAULT_CAPACITY;

WagonStack::WagonStack()
    : data(nullptr), capacity(0), top(-1)
{   
    this->data = new int[DEFAULT_CAPACITY];
    this->capacity = DEFAULT_CAPACITY;
    // TODO: Allocate an array of DEFAULT_CAPACITY wagons. The stack is empty.
}

WagonStack::~WagonStack()
{
    // TODO: Free the array.
    delete[] this->data;
}

WagonStack::WagonStack(const WagonStack &other)
    : data(nullptr), capacity(0), top(-1)
{
    // TODO: Deep copy: an array of its own with other.capacity elements and the same wagons.
    int* newAr = new int[other.capacity];
    for(int i = 0; i <= other.top; i++)
    {
        newAr[i] = other.data[i];
    }
    this->capacity = other.capacity;
    this->top = other.top;
    this->data = newAr;
}

WagonStack &WagonStack::operator=(const WagonStack &other)
{
    // TODO: Deep copy. The old array must not leak, and s = s must change nothing.
    if(&other == this)
    {
        return *this;
    }
    
    int* newAr = new int[other.capacity];
    for(int i = 0; i <= other.top; i++)
    {
        newAr[i] = other.data[i];
    }
    this->capacity = other.capacity;
    this->top = other.top;
    delete[] this->data;
    this->data = newAr;
    
    return *this;
}

bool WagonStack::isEmpty() const
{
    // TODO
    if(this->top != -1)
    {
        return false;
    }
    return true;
}

int WagonStack::size() const
{
    // TODO
    return this->top+1;
    
}

void WagonStack::resize(int newCapacity)
{
    // TODO: A new array of newCapacity elements with the same wagons at the same indices.
    //  Delete the old array.
    int* newAr = new int[newCapacity];
    for(int i = 0; i < size(); i++)
    {
        newAr[i] = this->data[i]; 
    }
    delete[] this->data;
    this->capacity = newCapacity;
    this->data = newAr;
}

void WagonStack::push(int wagon)
{
    // TODO: If the array is full, resize(2 * capacity) first. Then put the wagon on top.
    if(size() == this->capacity)
    {
        resize(2*this->capacity);
    }

    this->top += 1;
    this->data[this->top] = wagon;
}

bool WagonStack::pop(int &out)
{
    // TODO: Return false if empty. Otherwise write the top wagon into out and remove it.
    if(isEmpty())
    {
        return false;
    }
    out = this->data[this->top];
    this->top -= 1;
    return true;
}

bool WagonStack::peek(int &out) const
{
    // TODO: Return false if empty. Otherwise write the top wagon into out.
    if(isEmpty())
    {
        return false;
    }
    out = this->data[this->top];
    return true;
}

int WagonStack::get(int i) const
{
    return this->data[i];
}

int WagonStack::indexOf(int wagon) const
{
    // TODO: The position of the wagon from the BOTTOM, or -1 if it is not in the stack.
    for(int i = 0; i <= top; i++)
    {
        if(this->data[i] == wagon)
        {
            return i;
        }
    }
    return -1;
}

void WagonStack::clear()
{
    // TODO: Remove all wagons. The capacity does not change.
    int i = 0;
    while(!isEmpty())
    {
        pop(i);
    }

}
