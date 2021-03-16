#ifndef HEAP_H
#define HEAP_H

template<typename Key, typename Value> struct Node{
    Key key;
    Value value;
    Node(){}
    Node(Key _key, Value _value):key(_key), value(_value){}
    ~Node(){}
    Node operator=(Node<Key, Value> &rhs);
};

template<typename Key, typename Value>
Node<Key, Value> Node<Key, Value>::operator=(Node<Key, Value> &rhs){
    this->key = rhs.key;
    this->value = rhs.value;
    return *this;
}

template<typename Key, typename Value> class Heap{
public:
    Heap();
    ~Heap();
    void push(Key key, Value value);
    Node<Key, Value> pop();
    bool isEmpty();
private:
    Node<Key, Value> *head;
    void Down();
    void Up();
    void DoubleHeap();
    long length, max_length;
};

template<typename Key, typename Value>
Heap<Key,Value>::Heap(){
    head = new Node<Key, Value> [2];
    length = 0;
    max_length = 2;
}
template<typename Key, typename Value>
Heap<Key,Value>::~Heap(){
    delete [] head;
}

template<typename Key, typename Value>
void Heap<Key,Value>::Down(){
    long i=1;
    Node<Key, Value> temp;
    while(2*i+1<=length){
        if(head[2*i].value>head[2*i+1].value){
            temp = head[2*i];
            head[2*i]=head[i];
            head[i] = temp;
            i*=2;
        }
        else{
            temp = head[2*i+1];
            head[2*i+1]=head[i];
            head[i] = temp;
            i=i*2+1;
        }
    }
    temp = head[i];
    head[i] = head[length];
    head[length] = temp;
}

template<typename Key, typename Value>
void Heap<Key,Value>::Up(){
    long i=length;
    Node<Key, Value> temp;
    while(i>1){
        if(head[i].value>head[i/2].value){
            temp = head[i];
            head[i] = head[i/2];
            head[i/2] = temp;
            i/=2;
        }
        else break;
    }
}

template<typename Key, typename Value>
void Heap<Key,Value>::DoubleHeap(){
    Node<Key, Value> *temp = new Node<Key, Value> [2*max_length];
    for(long i=0; i<max_length; ++i){
        temp[i]=head[i];
    }
    delete [] head;
    head = temp;
    max_length = 2*max_length;
}

template<typename Key, typename Value>
void Heap<Key,Value>::push(Key key, Value value){
    length=length+1;
    if(length>=max_length){
        DoubleHeap();
    }
    head[length].key = key;
    head[length].value = value;
    Up();
}


template<typename Key, typename Value>
Node<Key, Value> Heap<Key,Value>::pop(){
    Down();
    length--;
    return head[length+1];
}

template<typename Key, typename Value>
bool Heap<Key,Value>::isEmpty(){
    return (length==0);
}

#endif // HEAP_H
