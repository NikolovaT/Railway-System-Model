#ifndef DoublyLinkedList_H
#define DoublyLinkedList_H

#include "node.h"

template <typename T> struct DoublyLinkedList {
	Node<T>* front=NULL;
	Node<T>* back=NULL;

	void add(T value) {
		Node<T>* new_node = new Node<T>();
		new_node->value = value;
		new_node->next = NULL;
		if(!this->back) {
			this->front = this->back = new_node;
			return;
		}

		new_node->prev = this->back;
		this->back->next = new_node;
		this->back = new_node;
	}

	void add_front(T value) {
		Node<T>* new_node = new Node<T>();
		new_node->value = value;
		new_node->prev = NULL;

		if(!this->front) {
			this->front = this->back = new_node;
			return;
		}

		new_node->next = this->front;
		this->front->prev = new_node;
		this->front = new_node;
	}

	void insert(int index, T value) {
		if(index<0) {
			printf("\nInvalid index");
			return;
		}

		Node<T>* temp_front = this->front;
		Node<T>* temp_back;
		Node<T>* new_node = new Node<T>();
		new_node->value = value;

		if(index==0) {
			this->add_front(value);
			return;
		} else {
			for(int i=0; i<index-1; i++) {
				temp_front = temp_front->next;
				if(!temp_front) {
					printf("\nIndex too big");
					return;
				}
			}
			temp_back = temp_front->next;
			if(!temp_back) {
				this->add(value);
				return;
			}

		}

		new_node->prev = temp_front;
		new_node->next = temp_back;

		temp_front->next = new_node;
		temp_back->prev = new_node;
	}

	void remove_at(int index) {
		if(index<0) {
			printf("\nInvalid index");
			return;
		}

		Node<T>* temp = this->front;
		int is_last = 0;

		for(int i=0; i<index; i++) {
			temp = temp->next;
			if(!temp) {
				printf("\nIndex too big");
			}
			if(!temp->next) is_last=1;
		}

		Node<T>* temp_next = temp->next;
		Node<T>* temp_prev = temp->prev;

		if(temp_prev) temp_prev->next = temp_next;
		if(temp_next) temp_next->prev = temp_prev;

		if(index==0) this->front = temp_next;
		if(is_last) this->back = temp_prev;

		delete temp;
	}

	template <typename X> bool get(int index, X& result) {

		if(index<0) {
			printf("\nInvalid index");
			return false;
		}

		if(!this->front) return false;
		
		Node<T>* temp = this->front;

		for(int i=0; i<index; i++) {
			temp = temp->next;
			if(!temp) {
				return false;
			}
		}

		result = temp->value;
		return true;
	}
};

#endif