#ifndef NODE_H
#define NODE_H

template <typename T> struct Node {
	Node* prev;
	Node* next;
	T value;
};

#endif 