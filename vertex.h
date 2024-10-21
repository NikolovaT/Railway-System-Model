#ifndef VERTEX_H
#define VERTEX_H

template <typename T> struct Vertex{
	T value;
	DoublyLinkedList<Arc<T>> incoming;
	DoublyLinkedList<Arc<T>> outgoing;
};

#endif