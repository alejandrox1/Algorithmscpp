#ifndef TNODE
#define TNODE

template <typename T>
class tnode {
	public:
		T nodeValue;
		tnode<T> *left, *right;

		// Default constructor
		tnode(){}

		// Initialize data members
		tnode(const T& item, tnode<T> *lptr=NULL, tnode<T> *rptr=NULL) 
			: nodeValue(item), left(lptr), right(rptr) {}
};

#endif
