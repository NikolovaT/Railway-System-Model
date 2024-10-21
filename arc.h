#ifndef ARC_H
#define ARC_H

template <typename T> struct Arc{
	int weight=0;
	Vertex<T> start;
	Vertex<T> end;
};

#endif