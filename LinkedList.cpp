#include<iostream>
#include<string>
#define endl '\n';

// Implementation of single node of linkedlist
template <class T>
class Node {
	public:
		Node(const T& e = T(), Node* n = NULL) :
			val(e), next(n) { };

		T val;
		Node* next;


};

// General LinkedList class implementation
template <class T>
class LinkedList {
	private:
		Node<T>* dummyHead;

	public:
    // Constructor 
		LinkedList() : dummyHead(new Node<T>(T(), NULL)) { };
    // Copy Constructor 
		LinkedList(const LinkedList& rhs) {
			dummyHead = new Node<T>(T(), NULL);
      
      // Uses = Operator Overlading 
			*this = rhs;
		}
    
    //Destructor for LinkedList
		~LinkedList() {
			makeEmpty();
			delete dummyHead;
		}
    
    // Node pointer to dummyHead
		Node<T>* zeroth() {
			return dummyHead;
		}
    
    // Node pointer to first element of LinkedList
		Node<T>* first() {
			return dummyHead->next;
		}
    
    // Constant version of first, since some of the functions are implemented using 
    // const to perform better time and memory
		const Node<T>* first() const {
			return dummyHead->next;
		}

    // All of them implemented outside of class with their explanations
		LinkedList& operator=(const LinkedList& rhs);
		bool isEmpty() const { return first() == NULL; }
		void insert(const T& data, Node<T>* p);
		Node<T>* find(const T& data);
		void remove(const T& data);
		void print() const;
		void makeEmpty();
};


// -------------------------------------------------------
// ---------------- LinkedList Functions -----------------
// -------------------------------------------------------

// Overloading the equal(=) operator for LinkedLists
template <class T>
LinkedList<T>& LinkedList<T>::operator=(const LinkedList<T>& rhs) {
	if (this != &rhs) {
		makeEmpty();
		const Node<T>* r = rhs.first();
		Node<T>* p = zeroth();

		while (r) {
			insert(r->val, p);
			r = r->next;
			p = p->next;
		}
	}
	return *this;
}

// Helper of destructor of LinkedList class
template <class T>
void LinkedList<T>::makeEmpty() {
	Node<T>* p = zeroth();
	Node<T>* tmp;

	while (p->next) {
		tmp = p->next->next;
    //delete not to cause memory leak
		delete p->next;
		p->next = tmp;
	}
	
}


// Print function for LinkedList
template <class T>
void LinkedList<T>::print() const {
	const Node<T>* p = first();

	while (p) {
		std::cout << p->val << endl;
		p = p->next;
	}
}


// Removing a Node from LinkedList without finding previous Node.
template <class T>
void LinkedList<T>::remove(const T& data) {
	Node<T>* p = find(data);

	if (p->next) {
		Node<T>* tmp = p->next;
		p->val = p->next->val;
		p->next = p->next->next;

		delete tmp;
	}
	else {
		Node<T>* prev = zeroth();

		while (prev->next->val != data) {
			prev = prev->next;
		}
		delete prev->next;
		prev->next = nullptr;
	}
}

// Find the first occurence pointer of data if there is not value == data, return nullptr
template <class T>
Node<T>* LinkedList<T>::find(const T& data) {
	Node<T>* p = first();

	while (p) {
		if (p->val == data)
			return p;
		p = p->next;
	}
	return NULL;
}


// Insertion inside linkedlist after given pointer
template <class T>
void LinkedList<T>::insert(const T& data, Node<T>* p) {
	Node<T>* insertedNode = new Node<T>(data, p->next);
	p->next = insertedNode;
}

// main starts includes some test cases
int main() {
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);

	LinkedList<int> list;
	list.insert(0, list.zeroth());
	Node<int>* p = list.first();

	for (int i = 1; i <= 10; ++i)
	{
		list.insert(i, p);
		p = p->next;
	}

	for (int i = 0; i <= 10; ++i)
	{
		if (i % 2 == 0)
			list.remove(i);
	}

	std::cout << "printing odd number list" << endl; 
	list.print();

	return 0;
}
