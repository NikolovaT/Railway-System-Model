#ifndef stack_H
#define stack_H

template <typename T> struct Node {
	T value;
	Node* next;
};

template <typename T> struct Stack {
	Node<T>* top_node=NULL;

	void push(T value) {
		Node<T>* new_node = new Node<T>();
		new_node -> value = value;
		new_node -> next = this->top_node;
		this->top_node = new_node;
	}

	T pop() {
		Node<T>* temp;
		if(top_node) {
			temp = this->top_node;
			int old_val = temp->value;
			this->top_node = this->top_node->next;
			delete(temp);
			return old_val;
		} else {
			printf("\nNo more elements to pop");
			return 0;
		}
	}

	T peek() {
		if (this->top_node) return this->top_node->value;
		else {
			printf("\nNo elements to peek");
			return 0;
		}
	}

	void print_stack() {
		do {
			printf("\n%d", this->peek());
		} while(this->pop()!=0);
	}
};


#endif