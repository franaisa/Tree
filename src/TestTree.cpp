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
#include "Tree.h"

using namespace std;

int main(int argc, char** argv) {
   Tree<int>::PreOrderIterator it;
   Tree<int>::PreOrderIterator graftIt;
   Tree<int> tree2(10);

   // Retrieving pre-order iterator to root node
   it = tree2.preBegin();
   tree2.pushBackChild(it, 20);
   tree2.pushBackChild(it, 30);
   tree2.pushBackChild(it, 40);
   tree2.pushBackChild(it, 50);

   // Get the second child
   it = it.firstChild();
   it = it.nextChild();

   // Attach to the second child
   tree2.pushBackChild(it, 60);
   tree2.pushBackChild(it, 70);

   // Get the second child
   it = it.firstChild();
   it = it.nextChild();

   // Attach to the second child
   tree2.pushBackChild(it, 80);
   tree2.pushBackChild(it, 90);
   tree2.pushBackChild(it, 100);

   // Get the third child
   it = it.firstChild();
   it = it.nextChild();
   it = it.nextChild();

   // Attach to the third child
   tree2.pushBackChild(it, 110);

   // Retrieving pre-order iterator to root node
   it = tree2.preBegin();

   // Get the fourth child
   it = it.firstChild();
   it = it.nextChild();
   it = it.nextChild();
   it = it.nextChild();

   // The fourth child is going to be the grafting node
   graftIt = it;
   tree2.pushBackChild(it, 120);

   // The root node for the new tree is 28
   Tree<int> tree(28);
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

   //tree.prePrint();
   //tree2.prePrint();

   /*tree.prePrint();
   tree.chop(startEraseNode);
   tree.prePrint();*/

   /*tree.prePrint();
   tree.erase(startEraseNode);
   tree.prePrint();*/

   /*tree.prePrint();

   preIt = startEraseNode.firstChild();
   preIt = startEraseNode.nextChild();

   tree.insertChild(startEraseNode, preIt, 200);

   tree.prePrint();*/

   cout << "tree : ";
   tree.prePrint();
   cout << "tree2 : ";
   tree2.prePrint();
   cout << "After grafting tree to tree2 on node " << *graftIt << " :" << endl;

   preIt = graftIt.firstChild();
   cout << "In the position of its first child" << endl;
   tree2.graftAt(graftIt, preIt, tree);
   tree2.prePrint();

   return 0;
}