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

#include "RootNotErasableException.h"
#include "TreeNode.h"
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
      Tree(const DataType& data) throw (std::bad_alloc);
      Tree(const Tree<DataType>& source) throw(std::bad_alloc);

      virtual ~Tree();

      Tree<DataType>& operator=(const Tree<DataType>& rhs) throw(std::bad_alloc);

      // If the root node doesn't exists, it creates a new one, otherwise it just
      // changes the value of the root node
      void setRoot(const DataType& data) throw(std::bad_alloc);

      // Return iterator to child inserted
      void pushFrontChild(const TreeIterator<DataType>& parent, const DataType& data) throw(std::bad_alloc);
      void pushBackChild(const TreeIterator<DataType>& parent, const DataType& data) throw(std::bad_alloc);
      // Use with care, iterator must be valid
      void insertChild(const TreeIterator<DataType>& parent, const TreeIterator<DataType>& childNode, const DataType& data) throw(std::bad_alloc);

      // Member functions to obtain iterators
      // Note that they could have been implemented returning just one kind of
      // iterator and then using a conversion constructor if the iterator to match
      // is different. That approach would mean the creation of one more temporary
      // variable, that's why we haven't used it.
      inline PreOrderIterator preBegin() const;
      inline PreOrderIterator preEnd() const;
      inline PostOrderIterator postBegin() const;
      inline PostOrderIterator postEnd() const;

      inline bool empty() const;

      // Member functions to erase nodes
      void erase(TreeIterator<DataType>& node) throw(RootNotErasableException);
      Tree<DataType> prune(TreeIterator<DataType>& rootNode);
      void chop(TreeIterator<DataType>& rootNode);

      void graftFront(const TreeIterator<DataType>& parent, Tree<DataType>& tree);
      void graftBack(const TreeIterator<DataType>& parent, Tree<DataType>& tree);
      // Use with care, iterator must be valid
      void graftAt(const TreeIterator<DataType>& parent, const TreeIterator<DataType>& childNode, Tree<DataType>& adoptTree);

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

      inline Tree(TreeNode<DataType>* root);

      void clone(const Tree<DataType>& source) throw(std::bad_alloc);
      inline void clean();
};


// *****************************************************************************
//                              TREE IMPLEMENTATION
// *****************************************************************************


template <class DataType>
Tree<DataType>::Tree() : _root(NULL) {
   // Nothing to do
}

//______________________________________________________________________________

template <class DataType>
Tree<DataType>::Tree(const DataType& data) throw (std::bad_alloc) {
   try {
      _root = new TreeNode<DataType>(data);
   }
   catch(std::bad_alloc& ex) {
      std::cerr << ex.what() << " : Failure to allocate memory for the root node when building the tree" << std::endl;

      // No resources need to be deallocated here
      // Because we are dealing with a run-time exception, rethrow it
      throw;
   }
}

//______________________________________________________________________________

// DEPRECATED <- To be implemented as a copy-on-write
template <class DataType>
Tree<DataType>::Tree(const Tree<DataType>& source) throw(std::bad_alloc) : _root(NULL) {
   try {
      clone(source);
   }
   catch(std::bad_alloc& ex) {
      std::cerr << ex.what() << " : Failure to allocate memory when copy constructing the object" << std::endl;

      // Because the object hasn't been constructed the destructor won't be executed, hence, we need
      // to deallocate any memory that had been allocated.
      clean();

      // Rethrow
      throw;
   }
}

//______________________________________________________________________________

// DEPRECATED <- To be implemented with chop
template <class DataType>
Tree<DataType>::~Tree() {
   clean();
}

//______________________________________________________________________________

// DEPRECATED <- To be implemented as a copy-on-write
template <class DataType>
Tree<DataType>& Tree<DataType>::operator=(const Tree<DataType>& rhs) throw(std::bad_alloc) {
   if(this != &rhs) {
      // No need to check for exceptions. If something fails, memory deallocation
      // will automatically happen because of the execution of the destructor
      clone(rhs);
   }

   return *this;
}

//______________________________________________________________________________

template <class DataType>
void Tree<DataType>::setRoot(const DataType& data) throw(std::bad_alloc) {
   if(_root == NULL) {
      try {
         _root = new TreeNode<DataType>(data);
      }
      catch(std::bad_alloc& ex) {
         std::cerr << ex.what() << " : Failure to allocate memory for the root node" << std::endl;

         // No resources need to be deallocated here, because the tree was empty
         // Because we are dealing with a run-time exception, rethrow it
         throw;
      }
   }
   else {
      // Just assign a new value to the root
      *_root = data;
   }
}

//______________________________________________________________________________

template <class DataType>
void Tree<DataType>::pushFrontChild(const TreeIterator<DataType>& parent, const DataType& data) throw(std::bad_alloc) {
   TreeNode<DataType>* child;
   try {
      child = new TreeNode<DataType>(data, parent._pointer);
   }
   catch(std::bad_alloc& ex) {
      std::cerr << ex.what() << " : Failure to allocate memory for the new child" << std::endl;

      // Since we are not inside the constructor, the destructor for this object
      // will get called, hence, there won't be any memory leak
      throw;
   }

   parent._pointer->_children.push_front(child);
   child->_childIt = parent._pointer->_children.begin();
}

//______________________________________________________________________________

template <class DataType>
void Tree<DataType>::pushBackChild(const TreeIterator<DataType>& parent, const DataType& data) throw(std::bad_alloc) {
   TreeNode<DataType>* child;
   try {
      child = new TreeNode<DataType>(data, parent._pointer);
   }
   catch(std::bad_alloc& ex) {
      std::cerr << ex.what() << " : Failure to allocate memory for the new child" << std::endl;

      // Since we are not inside the constructor, the destructor for this object
      // will get called, hence, there won't be any memory leak
      throw;
   }

   parent._pointer->_children.push_back(child);
   child->_childIt = --(parent._pointer->_children.end());
}

//______________________________________________________________________________

template <class DataType>
void Tree<DataType>::insertChild(const TreeIterator<DataType>& parent,
                                 const TreeIterator<DataType>& childNode,
                                 const DataType& data)
   throw(std::bad_alloc)
{

   TreeNode<DataType>* child;
   try {
      child = new TreeNode<DataType>(data, parent._pointer);
   }
   catch(std::bad_alloc& ex) {
      std::cerr << ex.what() << " : Failure to allocate memory for the new child when inserting" << std::endl;

      // Since we are not inside the constructor, the destructor for this object
      // will get called, hence, there won't be any memory leak
      throw;
   }

   typename std::list< TreeNode<DataType>* >::iterator it(childNode._pointer->_childIt);
   parent._pointer->_children.insert(it, child);
   child->_childIt = --it;
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
bool Tree<DataType>::empty() const {
   return _root == NULL ? true : false;
}

//______________________________________________________________________________

// If an iterator pointing to the end is passed (iterator pointing to null) the
// method will fail. NULL ITERATORS CAN'T BE PASSED AS AN ARGUMENT TO THIS FUNCTION
template <class DataType>
void Tree<DataType>::erase(TreeIterator<DataType>& node) throw(RootNotErasableException) {
   TreeNode<DataType>* nodePtr(node.getPointer());
   // By definition a tree has a single root, hence, the root node can't be
   // erased
   if(nodePtr == _root)
      throw RootNotErasableException("Error: Attempting to erase the root node");

   // Insert every child under the position that the iterator of the current
   // node indicates (in the parent node)
   typename std::list< TreeNode<DataType>* >::iterator it(nodePtr->_children.begin());
   for(; it != nodePtr->_children.end(); ++it) {
      nodePtr->_parent->_children.insert(nodePtr->_childIt, *it);
      // Update _childIt for each relinked child
      (*it)->_childIt = nodePtr->_childIt;
      --((*it)->_childIt);
   }

   // Erase the node
   nodePtr->_parent->_children.erase(nodePtr->_childIt);
   delete nodePtr;
}

//______________________________________________________________________________

// If an iterator pointing to the end is passed (iterator pointing to null) the
// method will fail. NULL ITERATORS CAN'T BE PASSED AS ARGUMENTS
template <class DataType>
Tree<DataType> Tree<DataType>::prune(TreeIterator<DataType>& rootNode) {
   TreeNode<DataType>* nodePtr = rootNode.getPointer();

   // Erase the child reference to this node on the parent node if there is a
   // parent node
   nodePtr->_parent->_children.erase(nodePtr->_childIt);

   return Tree<DataType>(nodePtr);
}

//______________________________________________________________________________

// If an iterator pointing to the end is passed (iterator pointing to null) the
// method will fail. NULL ITERATORS CAN'T BE PASSED AS ARGUMENTS
template <class DataType>
void Tree<DataType>::chop(TreeIterator<DataType>& rootNode) {
   TreeNode<DataType>* rootPtr(rootNode.getPointer());
   TreeNode<DataType>* parentPtr(rootPtr->parent());

   // Erase the child reference to this node on the parent node if there is a
   // parent node
   if(parentPtr != NULL)
      parentPtr->_children.erase(rootPtr->_childIt);

   // Deallocate memory for every node under 'rootNode'
   for(PostOrderIterator postIt(rootPtr); postIt != postEnd(); ++postIt)
      delete postIt.getPointer();
}

//______________________________________________________________________________

// The passed tree will be a subtree of '*this' tree. The given tree to be grafted
// will be empty after the execution of this method. '*this' tree will have the
// responsability of deallocating resources
template <class DataType>
void Tree<DataType>::graftFront(const TreeIterator<DataType>& parent, Tree<DataType>& adoptTree) {
   // The current tree adopts the new tree created and assumes the responsability
   // of liberating the corresponding resources
   parent._pointer->_children.push_front(adoptTree._root);
   adoptTree._root->_childIt = parent._pointer->_children.begin();
   adoptTree._root = NULL;
}

//______________________________________________________________________________

// The passed tree will be a subtree of '*this' tree. The given tree to be grafted
// will be empty after the execution of this method. '*this' tree will have the
// responsability of deallocating resources
template <class DataType>
void Tree<DataType>::graftBack(const TreeIterator<DataType>& parent, Tree<DataType>& adoptTree) {
   // The current tree adopts the new tree created and assumes the responsability
   // of liberating the corresponding resources
   parent._pointer->_children.push_back(adoptTree._root);
   adoptTree._root->_childIt = --(parent._pointer->_children.end());
   adoptTree._root = NULL;
}

//______________________________________________________________________________

template <class DataType>
void Tree<DataType>::graftAt(const TreeIterator<DataType>& parent, const TreeIterator<DataType>& childNode, Tree<DataType>& adoptTree) {
   typename std::list< TreeNode<DataType>* >::iterator it(childNode._pointer->_childIt);
   parent._pointer->_children.insert(it, adoptTree._root);
   adoptTree._root->_childIt = --it;
   adoptTree._root = NULL;
}

//______________________________________________________________________________

template <class DataType>
Tree<DataType>::Tree(TreeNode<DataType>* root) {
   this->_root = root;
}

//______________________________________________________________________________

// DEPRECATED <- To be implemented as a copy-on-write
template <class DataType>
void Tree<DataType>::clone(const Tree<DataType>& source) throw(std::bad_alloc) {
   // If the tree already had data stored, delete it
   if(_root != NULL) {
      clean();
      _root = NULL;
   }

   // This map is going to tell us which node is the parent of who
   std::map< TreeNode<DataType>*, TreeNode<DataType>* > parentMap;
   parentMap[NULL] = NULL;

   // Allocate memory for the new root
   try {
      _root = new TreeNode<DataType>(*source.preBegin());
   }
   catch(std::bad_alloc& ex) {
      std::cerr << ex.what() << " : Failure to allocate memory for the root node when executing clone()" << std::endl;
      throw;
   }
   parentMap[source._root] = _root;

   for(PreOrderIterator srcIt = source.preBegin(), myIt = preBegin(); srcIt != source.preEnd(); ++srcIt, ++myIt) {
      // Temp variables
      TreeNode<DataType>* myPt = myIt.getPointer();
      TreeNode<DataType>* srcPt = srcIt.getPointer();
      PreOrderIterator tmpParent;
      tmpParent = srcIt.parent();

      // Link the current node to the corresponding parent
      myPt->_parent = parentMap[tmpParent.getPointer()];

      // Copy node data
      *myIt = *srcIt;

      // Allocate memory for descendants if any and put them in the dictionary
      typename std::list< TreeNode<DataType>* >::iterator it;
      for(it = srcPt->_children.begin(); it != srcPt->_children.end(); ++it) {
         TreeNode<DataType>* newChild;
         try {
            newChild = new TreeNode<DataType>;
         }
         catch(std::bad_alloc& ex) {
            std::cerr << ex.what() << " : Failure to allocate memory when creating children in clone()" << std::endl;
            throw;
         }

         // Allocate memory for a new child
         myPt->_children.push_back(newChild);
         // Store the parent iterator that points to this child, in the child
         // so we can erase nodes easily
         newChild->_childIt = --(myPt->_children.end());
         // Make a correspondence in the dictionary
         parentMap[*it] = newChild;
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
      // Because TreeIterator is abstract we can't implement operator++(int) like this
      // because a reference to TreeIterator<T> can't be returned, hence, we need
      // to implement it, in each derived class independently
      //virtual TreeIterator<DataType> operator++(int notUsed) = 0;

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

      inline unsigned int nChildren();
      virtual TreeIterator<DataType>& firstChild() = 0;
      virtual TreeIterator<DataType>& lastChild() = 0;
      virtual TreeIterator<DataType>& nextChild() = 0;
      virtual TreeIterator<DataType>& previousChild() = 0;
   //protected:
      TreeIterator(TreeNode<DataType>* data);

      // _currentChild need not be initialized because it should always be called
      // by firstChild() or lastChild(), meaning that its value will be override
      // during each call, furthermore, this iterator shouldn't be copied when using
      // operator= because we want to enforce the use of firstChild() and lastChild()
      typename std::list< TreeNode<DataType>* >::iterator _currentChild;
   //private:
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
TreeNode<DataType>* TreeIterator<DataType>::getPointer() {
   return _pointer;
}

//______________________________________________________________________________

template <class DataType>
void TreeIterator<DataType>::setPointer(TreeNode<DataType>* newPointer) {
   _pointer = newPointer;
}

//______________________________________________________________________________

template <class DataType>
unsigned int TreeIterator<DataType>::nChildren() {
   return _pointer->_children.size();
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
      // Converting constructor
      PreOrderIterator(const PostOrderIterator& postIt);
      PreOrderIterator(const PreOrderIterator& source);

      virtual ~PreOrderIterator();

      PreOrderIterator& operator=(const TreeIterator<DataType>& rhs);

      virtual PreOrderIterator& operator++();
      PreOrderIterator operator++(int notUsed);

      virtual TreeIterator<DataType>& parent();

      virtual TreeIterator<DataType>& firstChild();
      virtual TreeIterator<DataType>& lastChild();
      virtual TreeIterator<DataType>& nextChild();
      virtual TreeIterator<DataType>& previousChild();
   //private:
      friend PreOrderIterator Tree<DataType>::preBegin() const;
      friend PreOrderIterator Tree<DataType>::preEnd() const;

      PreOrderIterator(TreeNode<DataType>* data);

      std::stack< std::pair<TreeNode<DataType>*, typename std::list< TreeNode<DataType>* >::iterator> > _pathStack;
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
Tree<DataType>::PreOrderIterator::PreOrderIterator(const PostOrderIterator& postIt) {
   TreeIterator<DataType>::setPointer(postIt._pointer);
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
   std::pair< TreeNode<DataType>*, typename std::list< TreeNode<DataType>* >::iterator > topNode;
   typename std::list< TreeNode<DataType>* >::iterator tmp;
   // nodePt is the pointer to the TreeNode stored inside the TreeIterator
   TreeNode<DataType>* nodePt = TreeIterator<DataType>::getPointer();

   int nChildren = nodePt->nChildren();
   // If the current node has children, we must visit them and keep the current
   // node in the stack in case there are more children
   if(nChildren > 0) {
      // If the current node is the one on the top of the stack, get the next
      // child to visit
      typename std::list< TreeNode<DataType>* >::iterator nextChild;
      if(_pathStack.empty() || nodePt != _pathStack.top().first) {
         nextChild = nodePt->_children.begin();
         tmp = nextChild;
         _pathStack.push(std::pair< TreeNode<DataType>*, typename std::list< TreeNode<DataType>* >::iterator >(nodePt, ++tmp));
      }
      else {
         topNode = _pathStack.top();
         nextChild = topNode.second;
         tmp = nextChild;
         _pathStack.top() = std::pair<TreeNode<DataType>*, typename std::list< TreeNode<DataType>* >::iterator >(topNode.first, ++tmp);
      }

      TreeIterator<DataType>::setPointer(*nextChild);
   }
   else {
      while(!_pathStack.empty()) {
         topNode = _pathStack.top();
         // If there are children that haven't been visited
         if(topNode.second != topNode.first->_children.end()) {
            // Current node is the next child to visit
            tmp = topNode.second;
            TreeIterator<DataType>::setPointer(*topNode.second);
            // Update next child to be visited
            _pathStack.top() = std::pair<TreeNode<DataType>*, typename std::list< TreeNode<DataType>* >::iterator>(topNode.first, ++tmp);

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
typename Tree<DataType>::PreOrderIterator Tree<DataType>::PreOrderIterator::operator++(int notUsed) {
   PreOrderIterator tmp(*this);
   ++(*this);
   return tmp;
}

//______________________________________________________________________________

template <class DataType>
TreeIterator<DataType>& Tree<DataType>::PreOrderIterator::parent() {
   static Tree<DataType>::PreOrderIterator tmp;
   tmp.setPointer(TreeIterator<DataType>::getPointer()->_parent);
   return tmp;
}

//______________________________________________________________________________

template <class DataType>
TreeIterator<DataType>& Tree<DataType>::PreOrderIterator::firstChild() {
   static Tree<DataType>::PreOrderIterator tmp;

   // Update the current child selected
   TreeIterator<DataType>::_currentChild = TreeIterator<DataType>::getPointer()->_children.begin();

   // Build a pre-order iterator
   tmp.setPointer(*TreeIterator<DataType>::_currentChild);
   return tmp;
}

//______________________________________________________________________________

template <class DataType>
TreeIterator<DataType>& Tree<DataType>::PreOrderIterator::lastChild() {
   static Tree<DataType>::PreOrderIterator tmp;

   // Update the current child selected
   TreeIterator<DataType>::_currentChild = --(TreeIterator<DataType>::getPointer()->_children.end());

   // Build a pre-order iterator
   tmp.setPointer(*TreeIterator<DataType>::_currentChild);
   return tmp;
}

//______________________________________________________________________________

template <class DataType>
TreeIterator<DataType>& Tree<DataType>::PreOrderIterator::nextChild() {
   static Tree<DataType>::PreOrderIterator tmp;

   // Update iterator position
   ++TreeIterator<DataType>::_currentChild;

   tmp.setPointer(*TreeIterator<DataType>::_currentChild);
   return tmp;
}

//______________________________________________________________________________

template <class DataType>
TreeIterator<DataType>& Tree<DataType>::PreOrderIterator::previousChild() {
   static Tree<DataType>::PreOrderIterator tmp;

   // Update iterator position
   --TreeIterator<DataType>::_currentChild;

   tmp.setPointer(*TreeIterator<DataType>::_currentChild);
   return tmp;
}











// *****************************************************************************
//                           POST-ORDER ITERATOR HEADER
// *****************************************************************************


template <class DataType>
class Tree<DataType>::PostOrderIterator : public TreeIterator<DataType> {
   public:
      PostOrderIterator();
      // Converting constructor
      PostOrderIterator(const PreOrderIterator& preIt);
      // If we have to return an iterator from a function
      // DO NOT ever construct it using this constructor, use the one that's private
      PostOrderIterator(const PostOrderIterator& source);

      virtual ~PostOrderIterator();

      PostOrderIterator& operator=(const PostOrderIterator& rhs);

      virtual PostOrderIterator& operator++();
      PostOrderIterator operator++(int notUsed);

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

      virtual TreeIterator<DataType>& firstChild();
      virtual TreeIterator<DataType>& lastChild();
      virtual TreeIterator<DataType>& nextChild();
      virtual TreeIterator<DataType>& previousChild();
   //private:
      friend PostOrderIterator Tree<DataType>::postBegin() const;
      friend PostOrderIterator Tree<DataType>::postEnd() const;

      PostOrderIterator(TreeNode<DataType>* data);

      std::stack< std::pair<TreeNode<DataType>*, typename std::list< TreeNode<DataType>* >::iterator> > _pathStack;
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
Tree<DataType>::PostOrderIterator::PostOrderIterator(const PreOrderIterator& preIt) {
   TreeIterator<DataType>::setPointer(preIt._pointer);
   TreeNode<DataType>* ptr = preIt._pointer;
   if(ptr != NULL) {
      _pathStack.push(std::pair<TreeNode<DataType>*, typename std::list< TreeNode<DataType>* >::iterator >(ptr, ptr->_children.begin()));
      operator++();
      _justCreated = true;
   }
}

//______________________________________________________________________________

template <class DataType>
Tree<DataType>::PostOrderIterator::PostOrderIterator(TreeNode<DataType>* data) : TreeIterator<DataType>(data) {
   TreeNode<DataType>* ptr = TreeIterator<DataType>::getPointer();
   if(ptr != NULL) {
      _pathStack.push(std::pair<TreeNode<DataType>*, typename std::list< TreeNode<DataType>* >::iterator >(ptr, ptr->_children.begin()));
      operator++();
      _justCreated = true;
   }
}

//______________________________________________________________________________

template <class DataType>
Tree<DataType>::PostOrderIterator::PostOrderIterator(const PostOrderIterator& source) : TreeIterator<DataType>(source) {
   TreeNode<DataType>* ptr = TreeIterator<DataType>::getPointer();
   if(ptr != NULL) {
      _pathStack.push(std::pair<TreeNode<DataType>*, typename std::list< TreeNode<DataType>* >::iterator >(ptr, ptr->_children.begin()));
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
            _pathStack.push(std::pair<TreeNode<DataType>*, typename std::list< TreeNode<DataType>* >::iterator >(rhsPtr, rhsPtr->_children.begin()));
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
   typename std::list< TreeNode<DataType>* >::iterator tmp;

   // Raise a flag indicating that this iterator is no longer on the initialization state
   _justCreated = false;
   while(!_pathStack.empty()) {
      std::pair<TreeNode<DataType>*, typename std::list< TreeNode<DataType>* >::iterator> topNode = _pathStack.top();

      // If there are children nodes non explored, find the last one
      while(topNode.second != topNode.first->_children.end()) {
         tmp = topNode.second;
         _pathStack.top() = std::pair<TreeNode<DataType>*, typename std::list< TreeNode<DataType>* >::iterator>(topNode.first, ++tmp);
         _pathStack.push(std::pair<TreeNode<DataType>*, typename std::list< TreeNode<DataType>* >::iterator>(*topNode.second, (*topNode.second)->_children.begin()));
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
typename Tree<DataType>::PostOrderIterator Tree<DataType>::PostOrderIterator::operator++(int notUsed) {
   PostOrderIterator tmp(*this);
   ++(*this);
   return tmp;
}

//______________________________________________________________________________

template <class DataType>
TreeIterator<DataType>& Tree<DataType>::PostOrderIterator::parent() {
   static Tree<DataType>::PostOrderIterator tmp;
   tmp.setPointer(TreeIterator<DataType>::getPointer()->_parent);
   return tmp;
}

//______________________________________________________________________________

template <class DataType>
TreeIterator<DataType>& Tree<DataType>::PostOrderIterator::firstChild() {
   static Tree<DataType>::PostOrderIterator tmp;

   // Update the current child selected
   TreeIterator<DataType>::_currentChild = TreeIterator<DataType>::getPointer()->_children.begin();

   // Build a post-order iterator
   tmp.setPointer(*TreeIterator<DataType>::_currentChild);
   return tmp;
}

//______________________________________________________________________________

template <class DataType>
TreeIterator<DataType>& Tree<DataType>::PostOrderIterator::lastChild() {
   static Tree<DataType>::PostOrderIterator tmp;

   // Update the current child selected
   TreeIterator<DataType>::_currentChild = --(TreeIterator<DataType>::getPointer()->_children.end());

   // Build a post-order iterator
   tmp.setPointer(*TreeIterator<DataType>::_currentChild);
   return tmp;
}

//______________________________________________________________________________

template <class DataType>
TreeIterator<DataType>& Tree<DataType>::PostOrderIterator::nextChild() {
   static Tree<DataType>::PostOrderIterator tmp;

   // Update iterator position
   ++TreeIterator<DataType>::_currentChild;

   tmp.setPointer(*TreeIterator<DataType>::_currentChild);
   return tmp;
}

//______________________________________________________________________________

template <class DataType>
TreeIterator<DataType>& Tree<DataType>::PostOrderIterator::previousChild() {
   static Tree<DataType>::PostOrderIterator tmp;

   // Update iterator position
   --TreeIterator<DataType>::_currentChild;

   tmp.setPointer(*TreeIterator<DataType>::_currentChild);
   return tmp;
}

#endif