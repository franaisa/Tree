#include <iostream>
#include <vector>
#include "Tree.h"
#include "TreeNode.h"

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
   startEraseNode = preIt;
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

   // NO FUNCIONA PORQUE POSTBEGIN CONSTRUYE UN ITERADOR DE POST-ORDEN Y ENTONCES
   // LO QUE SE DEVUELVE ES EL PRIMER NODO QUE HAY QUE IMPRIMIR
   // HAY QUE HACER QUE SE DEVUELVA EL ITERADOR QUE APUNTA AL NODO ORIGINAL PARA
   // QUE AL LLEVAR ACABAO LA ASIGNACION SE PASE AUTOMATICAMENTE AL PRIMER NODO
   // A IMPRIMIR

   Tree<int>::PostOrderIterator post;
   //for(post = tree.postBegin(); post != tree.postEnd(); ++post) {
      //post.printStack();
      //cout << *post << " ";
   //}
   //cout << endl;

   //tree.postPrint();

   //tree.prePrint();
   //tree.chop(startEraseNode);
   //tree.prePrint();
   
   return 0;
}