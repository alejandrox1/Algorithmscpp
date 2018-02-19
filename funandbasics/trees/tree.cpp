#include<iostream>
#include "tnode.h"

int main() {
	tnode<char>* root;

	root = buildTree(1);

	std::cout<< "Inorder scan of nodes: ";
	inorderOutput(root);
	std::cout<<'\n';
}
