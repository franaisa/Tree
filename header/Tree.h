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

#ifndef __TREE_H__
#define __TREE_H__

#include "TreeNode.h"
#include "TreeIterator.h"
#include <iterator>
#include <map>
#include <new>
#include <stack>


// Forward declarations
template <class T>
class TreeIterator;


// *****************************************************************************
//                                  TREE HEADER
// *****************************************************************************


template <class DataType>
class Tree {
   public:
      class PreOrderIterator;
      class PostOrderIterator;

      Tree();
      Tree(const DataType& data);
      Tree(const Tree<DataType>& source);

      virtual ~Tree();

      Tree<DataType>& operator=(const Tree<DataType>& rhs);

      // Return iterator to root
      void setRoot(const DataType& data);

      // Return iterator to child inserted
      void pushFrontChild(const TreeIterator<DataType>& parent, const DataType& data);
      void pushBackChild(const TreeIterator<DataType>& parent, const DataType& data);
      //void insertChild(const TreeIterator<DataType>& parent, const DataType& data);

      // Member functions to obtain iterators
      inline PreOrderIterator preBegin() const;
      inline PreOrderIterator preEnd() const;
      inline PostOrderIterator postBegin() const;
      inline PostOrderIterator postEnd() const;

      inline unsigned int size() const;

      // Member functions to erase nodes
      // erase un nodo
      // tree poda(iterator) prune
      // void corte(iterator) chop
      void chop(TreeIterator<DataType>& rootNode);
      // graft un tree

      void prePrint() {
         if(_root != NULL) {
            for(PreOrderIterator it(preBegin()); it != preEnd(); ++it) {
               std::cout << *it << " ";
            }
            std::cout << std::endl;
         }
      }

      void postPrint() {
         if(_root != NULL) {
            for(PostOrderIterator it(postBegin()); it != postEnd(); ++it) {
               std::cout << *it << " ";
            }
            std::cout << std::endl;
         }
      }

   protected:
      // Nothing yet
   private:
      TreeNode<DataType>* _root;
      unsigned int _nNodes;

      void clone(const Tree<DataType>& source);
      inline void clean();
};


// *****************************************************************************
//                              TREE IMPLEMENTATION
// *****************************************************************************


template <class DataType>
Tree<DataType>::Tree() : _root(NULL), _nNodes(0) {
   // Nothing to do
}

//______________________________________________________________________________

// DEPRECATED <- THROW EXCEPTION IF MEMORY CAN'T BE ALLOCATED
template <class DataType>
Tree<DataType>::Tree(const DataType& data) : _nNodes(1) {
   _root = new(std::nothrow) TreeNode<DataType>(data);

   if(_root == NULL) {
      std::cerr << "Error: Failure to allocate memory" << std::endl;
   }
}

//______________________________________________________________________________

// DEPRECATED <- To be implemented as a copy-on-write
template <class DataType>
Tree<DataType>::Tree(const Tree<DataType>& source) : _root(NULL), _nNodes(source._nNodes) {
   clone(source);
}

//______________________________________________________________________________

template <class DataType>
Tree<DataType>::~Tree() {
   clean();
}

//______________________________________________________________________________

// DEPRECATED <- To be implemented as a copy-on-write
template <class DataType>
Tree<DataType>& Tree<DataType>::operator=(const Tree<DataType>& rhs) {
   if(this != &rhs) {
      _nNodes = rhs._nNodes;
      clone(rhs);
   }

   return *this;
}

//______________________________________________________________________________

// DEPRECATED <- THROW EXCEPTION IF MEMORY CAN'T BE ALLOCATED
template <class DataType>
void Tree<DataType>::setRoot(const DataType& data) {
   if(_root == NULL) {
      _root = new(std::nothrow) TreeNode<DataType>(data);

      if(_root == NULL) {
         std::cerr << "Error: Failure to allocate memory for the root node" << std::endl;
      }

      ++_nNodes;
   }
   else {
      *_root = data;
   }
}

//______________________________________________________________________________

// DEPRECATED <- THROW EXCEPTION IF MEMORY CAN'T BE ALLOCATED
template <class DataType>
void Tree<DataType>::pushFrontChild(const TreeIterator<DataType>& parent, const DataType& data) {
   TreeNode<DataType>* child = new(std::nothrow) TreeNode<DataType>(data, parent._pointer);
   if(child == NULL) {
      std::cerr << "Error: Failure to allocate memory" << std::endl;
   }

   ++_nNodes;
   parent._pointer->_children.push_front(child);
}

//______________________________________________________________________________

// DEPRECATED <- THROW EXCEPTION IF MEMORY CAN'T BE ALLOCATED
template <class DataType>
void Tree<DataType>::pushBackChild(const TreeIterator<DataType>& parent, const DataType& data) {
   TreeNode<DataType>* child = new(std::nothrow) TreeNode<DataType>(data, parent._pointer);
   if(child == NULL) {
      std::cerr << "Error: Failure to allocate memory" << std::endl;
   }

   ++_nNodes;
   parent._pointer->_children.push_back(child);
}

//______________________________________________________________________________

template <class DataType>
typename Tree<DataType>::PreOrderIterator Tree<DataType>::preBegin() const {
   return PreOrderIterator(_root);
}

//______________________________________________________________________________

template <class DataType>
typename Tree<DataType>::PreOrderIterator Tree<DataType>::preEnd() const {
   return PreOrderIterator(NULL);
}

//______________________________________________________________________________

template <class DataType>
typename Tree<DataType>::PostOrderIterator Tree<DataType>::postBegin() const {
   return PostOrderIterator(_root);
}

//______________________________________________________________________________

template <class DataType>
typename Tree<DataType>::PostOrderIterator Tree<DataType>::postEnd() const {
   return PostOrderIterator(NULL);
}

//______________________________________________________________________________

template <class DataType>
unsigned int Tree<DataType>::size() const {
   return _nNodes;
}

//______________________________________________________________________________

// DEPRECATED IF THE ITERATOR PASSED IS A NULL POINTER NOTHING HAPPENS
template <class DataType>
void Tree<DataType>::chop(TreeIterator<DataType>& rootNode) {
   TreeNode<DataType>* rootPtr(rootNode.getPointer());
   TreeNode<DataType>* parentPtr(rootPtr->parent());

   if(parentPtr != NULL) {
      // Kill the given children (rootPtr)

   }

   for(PostOrderIterator postIt(rootPtr); postIt != postEnd(); ++postIt) {
      std::cout << *postIt << " ";
      //delete postIt.getPointer();
   }
   std::cout << std::endl;
}

//______________________________________________________________________________

// DEPRECATED <- THROW EXCEPTION IF MEMORY CAN'T BE ALLOCATED
// To be implemented as a copy-on-write
template <class DataType>
void Tree<DataType>::clone(const Tree<DataType>& source) {
   // If the tree already had data stored, delete it
   if(_root != NULL) {
      clean();
      _root = NULL;
   }

   // This map is going to tell us which node is the parent of who
   std::map< TreeNode<DataType>*, TreeNode<DataType>* > parentMap;
   parentMap[NULL] = NULL;

   // Allocate memory for the new root
   _root = new(std::nothrow) TreeNode<DataType>(*source.preBegin());
   parentMap[source._root] = _root;

   for(PreOrderIterator srcIt = source.preBegin(), myIt = preBegin(); srcIt != source.preEnd(); ++srcIt, ++myIt) {
      // Temp variables
      TreeNode<DataType>* myPt = myIt.getPointer();
      TreeNode<DataType>* srcPt = srcIt.getPointer();
      int nChildren = srcPt->nChildren();
      PreOrderIterator tmpParent;
      tmpParent = srcIt.parent();

      // Link the current node to the corresponding parent
      myPt->_parent = parentMap[tmpParent.getPointer()];

      // Copy node data
      *myIt = *srcIt;

      // Allocate memory for descendants if any and put them in the dictionary
      for(int i = 0; i < nChildren; ++i) {
         myPt->_children.push_back(new(std::nothrow) TreeNode<DataType>);
         parentMap[srcPt->children(i)] = myPt->children(i);
      }
   }
}

//______________________________________________________________________________

template <class DataType>
void Tree<DataType>::clean() {
   // Use post-order iterator to erase each node
   if(_root != NULL)
      for(PostOrderIterator postIt = postBegin(); postIt != postEnd(); ++postIt)
         delete postIt.getPointer();
}















// *****************************************************************************
//                            TREE-ITERATOR HEADER
// *****************************************************************************

template <class DataType>
class TreeIterator {
   public:
      TreeIterator();
      TreeIterator(const TreeIterator<DataType>& source);

      virtual ~TreeIterator();

      TreeIterator<DataType>& operator=(const TreeIterator<DataType>& rhs);
      TreeIterator<DataType>& operator=(TreeNode<DataType>* rhs);

      // Abstract
      virtual TreeIterator<DataType>& operator++() = 0;
      TreeIterator<DataType> operator++(int notUsed);

      inline bool operator==(const TreeIterator<DataType>& rhs) const;
      inline bool operator!=(const TreeIterator<DataType>& rhs) const;

      inline DataType* operator->() const;
      inline DataType& operator*() const;
      // Careful when using it, the pointer returned MUST NOT be modified
      inline TreeNode<DataType>* getPointer();
      inline void setPointer(TreeNode<DataType>* newPointer);

      // We return a reference to a TreeIterator to be able to return a derived
      // class.
      // THIS TWO METHODS MUST NEVER BE USED TO MODIFY THE RETURNED VALUE
      // BECAUSE A STATIC LOCAL VALUE IS RETURNED.
      virtual TreeIterator<DataType>& parent() = 0;
      virtual TreeIterator<DataType>& children(int child) = 0;
   //protected:
      TreeIterator(TreeNode<DataType>* data);
   private:
      friend class Tree<DataType>;

      TreeNode<DataType>* _pointer;

      inline void clone(const TreeIterator<DataType>& rhs);
};


// *****************************************************************************
//                       TREE-ITERATOR IMPLEMENTATION
// *****************************************************************************


template <class DataType>
TreeIterator<DataType>::TreeIterator() : _pointer(NULL) {
   // Nothing to do
}

//______________________________________________________________________________

template <class DataType>
TreeIterator<DataType>::TreeIterator(TreeNode<DataType>* data) : _pointer(data) {
   // Nothing to do
}

//______________________________________________________________________________

template <class DataType>
TreeIterator<DataType>::TreeIterator(const TreeIterator<DataType>& source) : _pointer(source._pointer) {
   // Nothing to do
}

//______________________________________________________________________________

template <class DataType>
TreeIterator<DataType>::~TreeIterator() {
   // Nothing to do
}

//______________________________________________________________________________

template <class DataType>
TreeIterator<DataType>& TreeIterator<DataType>::operator=(const TreeIterator<DataType>& rhs) {
   if(this != &rhs)
      clone(rhs);

   return *this;
}

//______________________________________________________________________________

template <class DataType>
TreeIterator<DataType>& TreeIterator<DataType>::operator=(TreeNode<DataType>* rhs) {
   if(_pointer != rhs) {
      _pointer = rhs;
   }

   return *this;;
}

//______________________________________________________________________________

template <class DataType>
TreeIterator<DataType> TreeIterator<DataType>::operator++(int notUsed) {
   TreeIterator<DataType> tmp(*this);
   operator++();
   return tmp;
}

//______________________________________________________________________________

template <class DataType>
bool TreeIterator<DataType>::operator==(const TreeIterator<DataType>& rhs) const {
   return _pointer == rhs._pointer;
}

//______________________________________________________________________________

template <class DataType>
bool TreeIterator<DataType>::operator!=(const TreeIterator<DataType>& rhs) const {
   return _pointer != rhs._pointer;
}

//______________________________________________________________________________

template <class DataType>
DataType* TreeIterator<DataType>::operator->() const {
   return &(_pointer->_data);
}

//______________________________________________________________________________

template <class DataType>
DataType& TreeIterator<DataType>::operator*() const {
   return *(operator->());
}

//______________________________________________________________________________

template <class DataType>
void TreeIterator<DataType>::setPointer(TreeNode<DataType>* newPointer) {
   _pointer = newPointer;
}

//______________________________________________________________________________

template <class DataType>
TreeNode<DataType>* TreeIterator<DataType>::getPointer() {
   return _pointer;
}

//______________________________________________________________________________

template <class DataType>
void TreeIterator<DataType>::clone(const TreeIterator<DataType>& rhs) {
   _pointer = rhs._pointer;
}














// *****************************************************************************
//                            PRE-ORDER ITERATOR HEADER
// *****************************************************************************


template <class DataType>
class Tree<DataType>::PreOrderIterator : public TreeIterator<DataType> {
   public:
      PreOrderIterator();
      PreOrderIterator(const PreOrderIterator& source);

      virtual ~PreOrderIterator();

      PreOrderIterator& operator=(const TreeIterator<DataType>& rhs);

      virtual PreOrderIterator& operator++();

      virtual TreeIterator<DataType>& parent();
      virtual TreeIterator<DataType>& children(int child);
   //private:
      friend PreOrderIterator Tree<DataType>::preBegin() const;
      friend PreOrderIterator Tree<DataType>::preEnd() const;

      PreOrderIterator(TreeNode<DataType>* data);

      std::stack< std::pair<TreeNode<DataType>*, int> > _pathStack;
};


// *****************************************************************************
//                       PRE-ORDER ITERATOR IMPLEMENTATION
// *****************************************************************************

// Parent sets _pointer to NULL
template <class DataType>
Tree<DataType>::PreOrderIterator::PreOrderIterator() {
   // Nothing to do
}

//______________________________________________________________________________

template <class DataType>
Tree<DataType>::PreOrderIterator::PreOrderIterator(TreeNode<DataType>* data) : TreeIterator<DataType>(data) {
   // Nothing to do
}

//______________________________________________________________________________

template <class DataType>
Tree<DataType>::PreOrderIterator::PreOrderIterator(const PreOrderIterator& source) : TreeIterator<DataType>(source), _pathStack(source._pathStack) {
   // Nothing to do
}

//______________________________________________________________________________

template <class DataType>
Tree<DataType>::PreOrderIterator::~PreOrderIterator() {
   // Nothing to do
}

//______________________________________________________________________________

template <class DataType>
typename Tree<DataType>::PreOrderIterator& Tree<DataType>::PreOrderIterator::operator=(const TreeIterator<DataType>& rhs) {
   if(this != &rhs) {
      TreeIterator<DataType>::operator=(rhs);

      // Clear the stack
      while(!_pathStack.empty()) {
         _pathStack.pop();
      }
   }

   return *this;
}

//______________________________________________________________________________

// THE CURRENT NODE CAN'T BE NULL
template <class DataType>
typename Tree<DataType>::PreOrderIterator& Tree<DataType>::PreOrderIterator::operator++() {
   std::pair<TreeNode<DataType>*, int> topNode;
   // nodePt is the pointer to the TreeNode stored inside the TreeIterator
   TreeNode<DataType>* nodePt = TreeIterator<DataType>::getPointer();

   int nChildren = nodePt->nChildren();
   // If the current node has children, we must visit them and keep the current
   // node in the stack in case there are more children
   if(nChildren > 0) {
      // If the current node is the one on the top of the stack, get the next
      // child to visit
      int nextChild;
      if(_pathStack.empty() || nodePt != _pathStack.top().first) {
         nextChild = 0;
         _pathStack.push(std::pair<TreeNode<DataType>*, int>(nodePt, 1));
      }
      else {
         topNode = _pathStack.top();
         nextChild = topNode.second;
         _pathStack.top() = std::pair<TreeNode<DataType>*, int>(topNode.first, topNode.second + 1);
      }

      TreeIterator<DataType>::setPointer(nodePt->children(nextChild));
   }
   else {
      while(!_pathStack.empty()) {
         topNode = _pathStack.top();
         // If there are children that haven't been visited
         if(topNode.second < topNode.first->nChildren()) {
            // Current node is the next child to visit
            TreeIterator<DataType>::setPointer(topNode.first->children(topNode.second));
            // Update next child to be visited
            _pathStack.top() = std::pair<TreeNode<DataType>*, int>(topNode.first, topNode.second + 1);

            return *this;
         }
         // If we have already visited every children of the top node, extract it
         // from the stack and try with the next one if any. If the stack goes empty
         // return the NULL iterator (or end iterator)
         else {
            _pathStack.pop();
         }
      }

      // The stack is empty, meaning that we have no nodes left to visit, hence
      // the pointer should be NULL indicating that we have reached the end
      TreeIterator<DataType>::setPointer(NULL);
   }

   return *this;
}

//______________________________________________________________________________

template <class DataType>
TreeIterator<DataType>& Tree<DataType>::PreOrderIterator::parent() {
   static Tree<DataType>::PreOrderIterator tmp;
   tmp.setPointer(TreeIterator<DataType>::getPointer()->_parent);
   return tmp;
}

//______________________________________________________________________________

// DEPRECATED Child can't be out of bounds
template <class DataType>
TreeIterator<DataType>& Tree<DataType>::PreOrderIterator::children(int child) {
   static Tree<DataType>::PreOrderIterator tmp;
   tmp.setPointer(TreeIterator<DataType>::getPointer()->children(child));
   return tmp;
}














// *****************************************************************************
//                           POST-ORDER ITERATOR HEADER
// *****************************************************************************


template <class DataType>
class Tree<DataType>::PostOrderIterator : public TreeIterator<DataType> {
   public:
      PostOrderIterator();
      // If we have to return an iterator from a function
      // DO NOT ever construct it using this constructor, use the one that's private
      PostOrderIterator(const PostOrderIterator& source);

      virtual ~PostOrderIterator();

      PostOrderIterator& operator=(const PostOrderIterator& rhs);

      virtual PostOrderIterator& operator++();

      void printStack() {
         std::stack< std::pair<TreeNode<DataType>*, int> > auxStack(_pathStack);

         std::cout << "\nStack state: " << std::endl;
         while(!auxStack.empty()) {
            std::cout << "(" << *auxStack.top().first << ", " << auxStack.top().second << ")" << std::endl;
            auxStack.pop();
         }
         std::cout << std::endl;
      }

      virtual TreeIterator<DataType>& parent();
      virtual TreeIterator<DataType>& children(int child);
   //private:
      friend PostOrderIterator Tree<DataType>::postBegin() const;
      friend PostOrderIterator Tree<DataType>::postEnd() const;

      PostOrderIterator(TreeNode<DataType>* data);

      std::stack< std::pair<TreeNode<DataType>*, int> > _pathStack;
      bool _justCreated;
};

// *****************************************************************************
//                       POST-ORDER ITERATOR IMPLEMENTATION
// *****************************************************************************

// Parent sets _pointer to NULL
template <class DataType>
Tree<DataType>::PostOrderIterator::PostOrderIterator() : _justCreated(false) {
   // Nothing to do
}

//______________________________________________________________________________

template <class DataType>
Tree<DataType>::PostOrderIterator::PostOrderIterator(TreeNode<DataType>* data) : TreeIterator<DataType>(data) {
   TreeNode<DataType>* ptr = TreeIterator<DataType>::getPointer();
   if(ptr != NULL) {
      _pathStack.push(std::pair<TreeNode<DataType>*, int>(ptr, 0));
      operator++();
      _justCreated = true;
   }
}

//______________________________________________________________________________

template <class DataType>
Tree<DataType>::PostOrderIterator::PostOrderIterator(const PostOrderIterator& source) : TreeIterator<DataType>(source) {
   TreeNode<DataType>* ptr = TreeIterator<DataType>::getPointer();
   if(ptr != NULL) {
      _pathStack.push(std::pair<TreeNode<DataType>*, int>(ptr, 0));
      operator++();
      _justCreated = true;
   }
}

//______________________________________________________________________________

template <class DataType>
Tree<DataType>::PostOrderIterator::~PostOrderIterator() {
   // Nothing to do
}

//______________________________________________________________________________

template <class DataType>
typename Tree<DataType>::PostOrderIterator& Tree<DataType>::PostOrderIterator::operator=(const PostOrderIterator& rhs) {
   if(this != &rhs) {
      TreeIterator<DataType>::operator=(rhs);

      // If the right hand side element has already been used, we copy it normally
      // if not. We just copy the stack state because the constructor has just been
      // executed, which means that the state of the iterator has already been set
      if(!rhs._justCreated) {
         // Clear the stack
         while(!_pathStack.empty()) {
            _pathStack.pop();
         }

         // Put the first element to be printed at the top of the stack
         TreeNode<DataType>* rhsPtr(TreeIterator<DataType>::getPointer());
         if(rhsPtr != NULL) {
            _pathStack.push(std::pair<TreeNode<DataType>*, int>(rhsPtr, 0));
            operator++();
         }
      }
      else {
         _pathStack = rhs._pathStack;
      }
   }

   return *this;
}

//______________________________________________________________________________

template <class DataType>
typename Tree<DataType>::PostOrderIterator& Tree<DataType>::PostOrderIterator::operator++() {
   // Raise a flag indicating that this iterator is no longer on the initialization state
   _justCreated = false;
   while(!_pathStack.empty()) {
      std::pair<TreeNode<DataType>*, int> topNode = _pathStack.top();

      // If there are children nodes non explored, find the last one
      while(topNode.second < topNode.first->nChildren()) {
         _pathStack.top() = std::pair<TreeNode<DataType>*, int>(topNode.first, topNode.second + 1);
         _pathStack.push(std::pair<TreeNode<DataType>*, int>(topNode.first->children(topNode.second), 0));
         topNode = _pathStack.top();
      }

      _pathStack.pop();
      TreeIterator<DataType>::setPointer(topNode.first);

      return *this;
   }

   TreeIterator<DataType>::setPointer(NULL);
   return *this;
}

//______________________________________________________________________________

template <class DataType>
TreeIterator<DataType>& Tree<DataType>::PostOrderIterator::parent() {
   static Tree<DataType>::PostOrderIterator tmp;
   tmp.setPointer(TreeIterator<DataType>::getPointer()->_parent);
   return tmp;
}

//______________________________________________________________________________

// DEPRECATED Child can't be out of bounds
template <class DataType>
TreeIterator<DataType>& Tree<DataType>::PostOrderIterator::children(int child) {
   static Tree<DataType>::PostOrderIterator tmp;
   tmp.setPointer(TreeIterator<DataType>::getPointer()->children(child));
   return tmp;
}

#endif