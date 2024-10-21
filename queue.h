#ifndef Queue_H
#define Queue_H

template <typename T> struct Node {
	T value;
	Node* next;
};

template <typename T> struct Queue {
	Node<T>* front=NULL;
	Node<T>* back=NULL;

	void push(T value) {
		Node<T>* new_node = new Node<T>();
		new_node->value = value;
		new_node->next = NULL;
		if(!this->back) {
			this->front = this->back = new_node;
			return;
		}
		this->back->next = new_node;
		this->back = new_node;
	}

	T pop() {
		Node<T>* temp;
		if(this->front) {
			temp = this->front;
			int old_val = temp->value;
			this->front = temp->next;
			delete(temp);
			return old_val;

		} else {
			printf("\nNo nodes to pop");
			return 0;
		}
	}

	T peek_front() {
		if(this->front) return this->front->value;
		else {
			printf("\nNo front element");
			return 0;
		}
	}

	T peek_back() {
		if(this->back) return this->back->value;
		else {
			printf("\nNo back element");
			return 0;
		}
	}

	void display() {
		do {
			printf("\n%d", this->peek_front());
		} while(this->pop()!=0);
	}

};

#endif