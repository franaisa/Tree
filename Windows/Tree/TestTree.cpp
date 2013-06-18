/*
 * This program is free software; you can redistribute it and/or modify it under
 * the terms of the GNU General Public License as published by the Free Software
 * Foundation; either version 2 of the License, or (at your option) any later
 * version. This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General
 * Public License for more details. You should have received a copy of the GNU
 * General Public License along with this program; if not, write to the Free
 * Software Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301
 * USA.
 *
 * Copyright © 2011-2012 Francisco Aisa Garcia
 */

#include <iostream>
#include <list>
#include "Tree.hpp"

using namespace std;
using namespace aisa;

// *****************************************************************************
//                             FUNCTION DEFINITIONS
// *****************************************************************************


// Print a tree in pre-order
template <class T>
void prePrint(const Tree<T>& tree) {
   for(typename Tree<T>::PreOrderIterator it(tree.preBegin()); it != tree.preEnd(); ++it) {
      cout << *it << " ";
   }
   cout << endl;
}

// _____________________________________________________________________________

// Print a tree in post-order
template <class T>
void postPrint(const Tree<T>& tree) {
   for(typename Tree<T>::PostOrderIterator it(tree.postBegin()); it != tree.postEnd(); ++it) {
      cout << *it << " ";
   }
   cout << endl;
}

// _____________________________________________________________________________

Tree<int> wikipediaTree() {
   // The root node for the new tree is 2
   Tree<int> tree(2);
   Tree<int>::PreOrderIterator preIt;
   Tree<int>::PreOrderIterator startEraseNode;

   // Retrieving pre-order iterator to root node
   preIt = tree.preBegin();
   tree.pushBackChild(preIt, 7);
   tree.pushBackChild(preIt, 5);

   // Get the first child
   preIt = preIt.firstChild();

   startEraseNode = preIt; // Node 7
   // Attach to the first child
   tree.pushBackChild(preIt, 2);
   tree.pushBackChild(preIt, 6);

   // Get the second child
   preIt = preIt.firstChild();
   preIt = preIt.nextChild();

   // Attach to the second child
   tree.pushBackChild(preIt, 5);
   tree.pushBackChild(preIt, 11);

   // Retrieving pre-order iterator to root node
   preIt = tree.preBegin();

   // Get the second child
   preIt = preIt.firstChild();
   preIt = preIt.nextChild();

   // Attach to the second child
   tree.pushBackChild(preIt, 9);

   // Get the first child
   preIt = preIt.firstChild();

   // Attach to the first child
   tree.pushBackChild(preIt, 4);

   return tree;
}

// _____________________________________________________________________________

void chopTest(Tree<int>& tree, Tree<int>::PreOrderIterator& it) {
   cout << "CHOP TEST" << endl;
   cout << "The subtree that hangs from node " << *it << " is going to be chopped" << endl;
   cout << "Tree before chopping: ";
   prePrint(tree);

   tree.chop(it);

   cout << "Tree after chopping: ";
   prePrint(tree);
}

// _____________________________________________________________________________

void eraseTest(Tree<int>& tree, Tree<int>::PreOrderIterator& it) {
   cout << "ERASE TEST" << endl;
   cout << "We are going to delete node " << *it << endl;
   cout << "Tree before erasing: ";
   prePrint(tree);

   tree.erase(it);

   cout << "Tree after erasing: ";
   prePrint(tree);
}

// _____________________________________________________________________________

void graftBackTest(Tree<int>& tree, Tree<int>& adoptTree, const Tree<int>::PreOrderIterator& it) {
   cout << "GRAFT-BACK TEST" << endl;
   cout << "Tree : ";
   prePrint(tree);
   cout << "We are going to graft as the last child of node: " << *it << endl;
   cout << "The following tree: ";
   prePrint(adoptTree);

   tree.graftBack(it, adoptTree);

   cout << "After grafting the resulting tree is: ";
   prePrint(tree);
}


// *****************************************************************************
//                                    MAIN
// *****************************************************************************

// Some examples of how to use a Tree structure
int main(int argc, char** argv) {
   // Build the tree example found in wikipedia -> http://en.wikipedia.org/wiki/Binary_tree
   Tree<int> tree = wikipediaTree();
   Tree<int> tree2 = tree;

   Tree<int>::PreOrderIterator eraseIt, graftIt;

   eraseIt = tree.preBegin();		// Root Node 2
   eraseIt = eraseIt.firstChild();	// Node 7
   graftIt = eraseIt.firstChild();	// Node 2
   eraseIt = eraseIt.nextChild();	// Node 6

   postPrint(tree);
   prePrint(tree);

   //chopTest(tree, eraseIt);
   //eraseTest(tree, eraseIt);
   //graftBackTest(tree, tree2, graftIt);

   return 0;
}