#ifndef TREE_LIBRARY_FUNCTIONS
#define TREE_LIBRARY_FUNCTIONS

#include "tnode.h"


// Create one of the binary trees from page 513
tnode<char> *buildTree(int n);



tnode<char> *buildTree(int n) {
	tnode<char> *root, *b, *c, *d, *e, *f, *g, *h, *i;

	switch(n) {
		case 0:
			d = new tnode<char> ('D');
			e = new tnode<char> ('E');
			b = new tnode<char> ('B', (tnode<char> *)NULL, d);
			c = new tnode<char> ('C', e, (tnode<char> *)NULL);
			root = new tnode<char> ('A', b, c);
			break;
		
		case 1:
			g = new tnode<char> ('G');
			h = new tnode<char> ('H');
			i = new tnode<char> ('I');
			d = new tnode<char> ('E');
			e = new tnode<char> ('E', g, (tnode<char> *)NULL);
			f = new tnode<char> ('F', h, i);
			b = new tnode<char> ('B', d, e);
			c = new tnode<char> ('C', (tnode<char> *)NULL, f);
			root = new tnode<char> ('A', b, c);
			break;

		case 2:
			g = new tnode<char> ('G');
			h = new tnode<char> ('H');
			i = new tnode<char> ('I');
			d = new tnode<char> ('D', (tnode<char> *)NULL, g);
			e = new tnode<char> ('E', h, i);
			f = new tnode<char> ('F');
			b = new tnode<char> ('B', d, (tnode<char> *)NULL);
			c = new tnode<char> ('C', e, f);
			root = new tnode<char> ('A', b, c);
	}
	return root;
}


#endif
