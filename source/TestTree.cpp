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
#include "Tree.h"

using namespace std;

int main(int argc, char** argv) {
   Tree<int>::PreOrderIterator it;
   Tree<int>::PreOrderIterator graftIt;
   Tree<int> tree2(10);

   it = tree2.preBegin();
   tree2.pushBackChild(it, 20);
   tree2.pushBackChild(it, 30);
   tree2.pushBackChild(it, 40);
   tree2.pushBackChild(it, 50);

   it = it.children(1);
   tree2.pushBackChild(it, 60);
   tree2.pushBackChild(it, 70);

   it = it.children(1);
   tree2.pushBackChild(it, 80);
   tree2.pushBackChild(it, 90);
   tree2.pushBackChild(it, 100);

   it = it.children(2);
   tree2.pushBackChild(it, 110);

   it = tree2.preBegin();
   it = it.children(3);
   graftIt = it;
   tree2.pushBackChild(it, 120);

   //tree2.prePrint();
   //tree2.postPrint();

   Tree<int> tree(28);
   Tree<int>::PreOrderIterator preIt;
   Tree<int>::PreOrderIterator startEraseNode;

   preIt = tree.preBegin();
   tree.pushBackChild(preIt, 7);
   tree.pushBackChild(preIt, 5);

   preIt = preIt.children(0);
   startEraseNode = preIt; // Node 7
   tree.pushBackChild(preIt, 2);
   tree.pushBackChild(preIt, 6);

   preIt = preIt.children(1);
   tree.pushBackChild(preIt, 5);
   tree.pushBackChild(preIt, 11);

   preIt = tree.preBegin();
   preIt = preIt.children(1);
   tree.pushBackChild(preIt, 9);

   preIt = preIt.children(0);
   tree.pushBackChild(preIt, 4);

   startEraseNode = tree.preBegin();

   //tree.prePrint();
   //tree.postPrint();

   /*tree.prePrint();
   tree.chop(startEraseNode);
   tree.prePrint();*/

   /*tree.prePrint();
   tree.erase(startEraseNode);
   tree.prePrint();*/

   /*tree.prePrint();
   tree.insertChild(startEraseNode, 1, 200);
   tree.prePrint();*/

   //tree2.graftBack(graftIt, tree);
   //tree2.prePrint();

   return 0;
}