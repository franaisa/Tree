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
   /*Tree<int>::PreOrderIterator it;
   Tree<int> tree(10);

   it = tree.preBegin();
   tree.pushBackChild(it, 20);
   tree.pushBackChild(it, 30);
   tree.pushBackChild(it, 40);
   tree.pushBackChild(it, 50);

   it.children(1, it);
   tree.pushBackChild(it, 60);
   tree.pushBackChild(it, 70);

   it.children(1, it);
   tree.pushBackChild(it, 80);
   tree.pushBackChild(it, 90);
   tree.pushBackChild(it, 100);

   it.children(2, it);
   tree.pushBackChild(it, 110);

   it = tree.preBegin();
   it.children(3, it);
   tree.pushBackChild(it, 120);

   tree.prePrint();
   tree.postPrint();*/

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

   //tree.prePrint();
   //tree.postPrint();

   /*tree.prePrint();
   tree.chop(startEraseNode);
   tree.prePrint();*/

   tree.prePrint();
   tree.erase(startEraseNode);
   tree.prePrint();

   return 0;
}