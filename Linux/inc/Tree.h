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
#include <map>
#include <new>
#include <stack>


// *****************************************************************************
//                             FORWARD DELCARATIONS
// *****************************************************************************


template <class T>
class TreeIterator;


// *****************************************************************************
// *****************************************************************************
// *****************************************************************************
// ***                                                                       ***
// ***                                                                       ***
// ***                                                                       ***
// ***                                                                       ***
// ***                                                                       ***
// ***                                                                       ***
// ***                                                                       ***
// ***                                                                       ***
// ***                                                                       ***
// ***                                                                       ***
// ***                              TREE HEADER                              ***
// ***                                                                       ***
// ***                                                                       ***
// ***                                                                       ***
// ***                                                                       ***
// ***                                                                       ***
// ***                                                                       ***
// ***                                                                       ***
// ***                                                                       ***
// ***                                                                       ***
// ***                                                                       ***
// *****************************************************************************
// *****************************************************************************
// *****************************************************************************

/**
 * This class represents a traditional tree structure.
 *
 * It is meant to be used as a topology tree or search tree (backtracking,
 * branch and bound). This is the main reason why children nodes have been
 * implemented using lists, because we are going to be accessing the nodes in a
 * secuential fashion.
 *
 * Note that the ostream and istream operators haven't been implemented. The reason
 * is because a tree can be travelled in many different ways. The client is free
 * to implement an ostream operator however he wants (it shouldn't be a problem
 * since there are pre-order and post-order iterators available).
 *
 * Because 'TreeIterator', 'TreeNode' and 'Tree' are tightly bound together, I 
 * decided to code them using a friend relationship between them (the three of
 * them). Although this decision breaks a bit the rules of OOP, it makes the tree
 * structure behave more efficiently.
 *
 * @author Francisco Aisa García
 * @version 0.1
 */
template <class T>
class Tree {
   public:
      // =======================================================================
      //                          INNER DECLARATIONS
      // =======================================================================


      class PreOrderIterator;
      class PostOrderIterator;


      // =======================================================================
      //                     CONSTRUCTORS AND DESTRUCTORS
      // =======================================================================


      /**
       * Default constructor.
       *
       * It creates an empty tree.
       */
      inline Tree();

      //________________________________________________________________________

      /**
       * Custom constructor.
       * 
       * @param data Data to be assigned to the root node.
       * @throws std::bad_alloc Thrown if memory allocation for the root node fails.
       */
      Tree(const T& data) throw (std::bad_alloc);

      //________________________________________________________________________

      /**
       * Copy constructor.
       * 
       * @param source Source tree.
       * @throws std::bad_alloc Thrown if memory allocation fails when copying.
       */
      Tree(const Tree<T>& source) throw(std::bad_alloc);

      //________________________________________________________________________

      /** Destructor. */
      inline virtual ~Tree();


      // =======================================================================
      //                               OPERATORS
      // =======================================================================


      /**
       * Assignment operator.
       *
       * @param rhs Right hand side tree to be assigned.
       * @return A reference to 'this' tree.
       * @throws std::bad_alloc Thrown if memory allocation fails when copying.
       */
      Tree<T>& operator=(const Tree<T>& rhs) throw(std::bad_alloc);

      //________________________________________________________________________

      /**
       * Equality operator.
       *
       * @param rhs Right hand side tree to be compared.
       * @return 'true' if both trees have the same nodes with the same values.
       */
      bool operator==(const Tree<T>& rhs) const;

      //________________________________________________________________________

      /**
       * Inequality operator.
       *
       * @param rhs Right hand side tree to be compared.
       * @return 'true' if the trees are different.
       */
      inline bool operator!=(const Tree<T>& rhs) const;


      // =======================================================================
      //                               ITERATORS
      // =======================================================================


      /**
       * Retrieve a pre-order iterator pointing to the root node.
       *
       * Although this method can also be assigned to a post-order iterator due
       * to the existance of conversion constructors, it should NEVER be done.
       * That's the reason why we have specific methods to retrieve each kind of
       * iterator. 
       *
       * @return 'PreOrderIterator' to the root node.
       */
      inline PreOrderIterator preBegin() const;

      //________________________________________________________________________

      /**
       * Retrieve a pre-order iterator that marks the end of the tree.
       *
       * Although this method can also be assigned to a post-order iterator due
       * to the existance of conversion constructors, it should NEVER be done.
       * That's the reason why we have specific methods to retrieve each kind of
       * iterator. 
       * 
       * @return 'PreOrderIterator' that marks the end of the tree.
       */
      inline PreOrderIterator preEnd() const;

      //________________________________________________________________________

      /**
       * Retrieve a post-order iterator pointing to the root node.
       *
       * Although this method can also be assigned to a pre-order iterator due
       * to the existance of conversion constructors, it should NEVER be done.
       * That's the reason why we have specific methods to retrieve each kind of
       * iterator. 
       * 
       * @return 'PostOrderIterator' to the root node.
       */
      inline PostOrderIterator postBegin() const;

      //________________________________________________________________________

      /**
       * Retrieve a post-order iterator pointing to the root node.
       *
       * Although this method can also be assigned to a pre-order iterator due
       * to the existance of conversion constructors, it should NEVER be done.
       * That's the reason why we have specific methods to retrieve each kind of
       * iterator. 
       * 
       * @return 'PostOrderIterator' to the root node.
       */
      inline PostOrderIterator postEnd() const;


      // =======================================================================
      //                               CAPACITY
      // =======================================================================


      /**
       * Check if the tree is empty (has no nodes).
       *
       * @return 'true' if the tree is empty, 'false' otherwise.
       */
      inline bool empty() const;


      // =======================================================================
      //                               MODIFIERS
      // =======================================================================


      /**
       * Set the root value.
       *
       * If the tree is empty, this method creates a new root node and assigns
       * the given value, otherwise, it just assigns the value.
       *
       * @param data Data to be assigned to the root node.
       * @throws std::bad_alloc Thrown if memory allocation for the root node fails.
       */
      void setRoot(const T& data) throw(std::bad_alloc);

      //________________________________________________________________________

      /**
       * Given a value and an iterator to a node, create a new child at the front of the children list.
       *
       * @param parent Iterator to the node to which we want to attach the new node to be created.
       * @param data Data to be assigned to the new node to be created.
       * @return 'PreOrderIterator' to the new children node created.
       * @throws std::bad_alloc Thrown if memory allocation for the children node fails.
       */
      Tree<T>::PreOrderIterator pushFrontChild(const TreeIterator<T>& parent, const T& data) throw(std::bad_alloc);

      //________________________________________________________________________

      /**
       * Given a value and an iterator to a node, create a new child at the end of the children list.
       *
       * @param parent Iterator to the node to which we want to attach the new node to be created.
       * @param data Data to be assigned to the new node to be created.
       * @return 'PreOrderIterator' to the new children node created.
       * @throws std::bad_alloc Thrown if memory allocation for the children node fails.
       */
      Tree<T>::PreOrderIterator pushBackChild(const TreeIterator<T>& parent, const T& data) throw(std::bad_alloc);

      //________________________________________________________________________

      /**
       * Given a value and an iterator to a node, create a new child and insert in the position
       * given by the second given iterator.
       *
       * Note that this method doesn't do any kind iterator validity checking.
       * This means that the client is responsible for passing a valid iterator
       * to the method to insert the new node to be created.
       *
       * @param parent Iterator to the node to which we want to attach the new node to be created.
       * @param childNode Iterator to the child node where we want to insert the new node to be created.
       * @param data Data to be assigned to the new node to be created.
       * @return 'PreOrderIterator' to the new child node created.
       * @throws std::bad_alloc Thrown if memory allocation for the children node fails.
       */
      Tree<T>::PreOrderIterator insertChild(const TreeIterator<T>& parent, const TreeIterator<T>& childNode, const T& data) throw(std::bad_alloc);

      //________________________________________________________________________

      /**
       * Erase a single node.
       *
       * Given an iterator to a node, this method erases the node and relinks its
       * direct descendats to the erased node's parent.
       *
       * @param node Iterator to the node that we want to erase.
       * @throws RootNotErasableException Thrown if the given iterator points to
       * the root node (because the root node can't/shouldn't be erased).
       */
      void erase(TreeIterator<T>& node) throw(RootNotErasableException);

      //________________________________________________________________________

      /**
       * Prune a subtree.
       *
       * Given an iterator, this method prunes the subtree hanging from the node
       * pointed by the iterator and returns the tree. Note that this method doesn't
       * make a copy of the subtree, it literally prunes it.
       *
       * @param rootNode Iterator to the node from which the subtree that we want
       * to prune hangs.
       * @return The subtree that hangs from the node pointed by 'rootNode'.
       */
      Tree<T> prune(TreeIterator<T>& rootNode);

      //________________________________________________________________________

      /**
       * Erase a subtree.
       *
       * Given an iterator, this method erases the subtree hanging from the node
       * pointed by the iterator. Note that memory is actually deallocated, unlike
       * with the prune method.
       *
       * @param rootNode Iterator to the node from which the subtree that we want
       * to erase hangs.
       */
      void chop(TreeIterator<T>& rootNode);

      //________________________________________________________________________

      /**
       * Graft a tree and attach it to the front of the children list of a given node.
       *
       * This method attaches to the front of the children list of the node pointed
       * by the given iterator a whole tree. Note that the given tree is actually
       * modified, which means that after the execution of this method, the given
       * tree will be empty.
       *
       * @param parent Iterator to the node where we want to graft the given tree.
       * @param tree Tree to be grafted.
       */
      void graftFront(const TreeIterator<T>& parent, Tree<T>& tree);

      //________________________________________________________________________

      /**
       * Graft a tree and attach it to the back of the children list of a given node.
       *
       * This method attaches to the back of the children list of the node pointed
       * by the given iterator a whole tree. Note that the given tree is actually
       * modified, which means that after the execution of this method, the given
       * tree will be empty.
       *
       * @param parent Iterator to the node where we want to graft the given tree.
       * @param tree Tree to be grafted.
       */
      void graftBack(const TreeIterator<T>& parent, Tree<T>& tree);

      //________________________________________________________________________

      /**
       * Graft a tree and insert it into the children list of a given node.
       *
       * This method inserts a whole tree as a child of a node given by an iterator
       * in the position of a second given iterator. Note that the given tree is actually
       * modified, which means that after the execution of this method, the given
       * tree will be empty. Also note that this method doesn't do any kind of
       * range checking, which means that the client is responsible for passing
       * a valid iterator as an argument.
       *
       * @param parent Iterator to the node where we want to graft the given tree.
       * @param childNode Iterator to the child node where we want to graft the given tree.
       * @param tree Tree to be grafted.
       */
      void graftAt(const TreeIterator<T>& parent, const TreeIterator<T>& childNode, Tree<T>& adoptTree);

   private:
      // =======================================================================
      //                            PRIVATE METHODS
      // =======================================================================


      /**
       * Custom constructor.
       *
       * This constructor has been made private because the client should never
       * have to deal with TreeNodes (as a matter of fact, it should never be
       * allowed to handle them).
       *
       * @param root Pointer to the tree node that is going to be the root node.
       */
      inline Tree(TreeNode<T>* root);

      //________________________________________________________________________

      /**
       * Make a full copy of 'this' object.
       *
       * @param source Tree that is going to be copied.
       * @throws std::bad_alloc Thrown if memory allocation fails when copying. 
       */
      void clone(const Tree<T>& source) throw(std::bad_alloc);

      //________________________________________________________________________

      /** Deallocate any memory allocated by the tree */
      inline void clean();


      // =======================================================================
      //                            PRIVATE FIELDS
      // =======================================================================


      /** Pointer to the root node */
      TreeNode<T>* _root;
};


// *****************************************************************************
// *****************************************************************************
// *****************************************************************************
// ***                                                                       ***
// ***                                                                       ***
// ***                                                                       ***
// ***                                                                       ***
// ***                                                                       ***
// ***                                                                       ***
// ***                                                                       ***
// ***                                                                       ***
// ***                                                                       ***
// ***                                                                       ***
// ***                          TREE IMPLEMENTATION                          ***
// ***                                                                       ***
// ***                                                                       ***
// ***                                                                       ***
// ***                                                                       ***
// ***                                                                       ***
// ***                                                                       ***
// ***                                                                       ***
// ***                                                                       ***
// ***                                                                       ***
// ***                                                                       ***
// *****************************************************************************
// *****************************************************************************
// *****************************************************************************


template <class T>
Tree<T>::Tree() : _root(NULL) {
   // Nothing to do
}

//______________________________________________________________________________

template <class T>
Tree<T>::Tree(const T& data) throw (std::bad_alloc) {
   try {
      _root = new TreeNode<T>(data);
   }
   catch(std::bad_alloc& ex) {
      std::cerr << ex.what() << " : Failure to allocate memory for the root node when building the tree" << std::endl;

      // No resources need to be deallocated here
      // Because we are dealing with a run-time exception, rethrow it
      throw;
   }
}

//______________________________________________________________________________

template <class T>
Tree<T>::Tree(const Tree<T>& source) throw(std::bad_alloc) : _root(NULL) {
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

template <class T>
Tree<T>::~Tree() {
   clean();
}

//______________________________________________________________________________

template <class T>
Tree<T>& Tree<T>::operator=(const Tree<T>& rhs) throw(std::bad_alloc) {
   if(this != &rhs) {
      // No need to check for exceptions. If something fails, memory deallocation
      // will automatically happen because of the execution of the destructor
      clone(rhs);
   }

   return *this;
}

//______________________________________________________________________________

template <class T>
bool Tree<T>::operator==(const Tree<T>& rhs) const {
   if(this == &rhs) return true;
   if(empty() != rhs.empty()) return false;

   PreOrderIterator thisIt = this->preBegin();
   PreOrderIterator rhsIt = rhs.preBegin();
   for(; rhsIt != rhs.preEnd(); ++thisIt, ++rhsIt)
      if(*thisIt != *rhsIt || thisIt.nChildren() != rhsIt.nChildren())
         return false;

   return true;
}

//______________________________________________________________________________

template <class T>
bool Tree<T>::operator!=(const Tree<T>& rhs) const {
   return !(*this == rhs);
}

//______________________________________________________________________________

template <class T>
typename Tree<T>::PreOrderIterator Tree<T>::preBegin() const {
   return PreOrderIterator(_root);
}

//______________________________________________________________________________

template <class T>
typename Tree<T>::PreOrderIterator Tree<T>::preEnd() const {
   return PreOrderIterator(NULL);
}

//______________________________________________________________________________

template <class T>
typename Tree<T>::PostOrderIterator Tree<T>::postBegin() const {
   return PostOrderIterator(_root);
}

//______________________________________________________________________________

template <class T>
typename Tree<T>::PostOrderIterator Tree<T>::postEnd() const {
   return PostOrderIterator(NULL);
}

//______________________________________________________________________________

template <class T>
bool Tree<T>::empty() const {
   return _root == NULL ? true : false;
}

//______________________________________________________________________________

template <class T>
void Tree<T>::setRoot(const T& data) throw(std::bad_alloc) {
   if(_root == NULL) {
      try {
         _root = new TreeNode<T>(data);
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

template <class T>
typename Tree<T>::PreOrderIterator Tree<T>::pushFrontChild(const TreeIterator<T>& parent, const T& data) throw(std::bad_alloc) {
   TreeNode<T>* child;
   try {
      child = new TreeNode<T>(data, parent._pointer);
   }
   catch(std::bad_alloc& ex) {
      std::cerr << ex.what() << " : Failure to allocate memory for the new child" << std::endl;

      // Since we are not inside the constructor, the destructor for this object
      // will get called, hence, there won't be any memory leak
      throw;
   }

   parent._pointer->_children.push_front(child);
   child->_childIt = parent._pointer->_children.begin();

   return PreOrderIterator(child);
}

//______________________________________________________________________________

template <class T>
typename Tree<T>::PreOrderIterator Tree<T>::pushBackChild(const TreeIterator<T>& parent, const T& data) throw(std::bad_alloc) {
   TreeNode<T>* child;
   try {
      child = new TreeNode<T>(data, parent._pointer);
   }
   catch(std::bad_alloc& ex) {
      std::cerr << ex.what() << " : Failure to allocate memory for the new child" << std::endl;

      // Since we are not inside the constructor, the destructor for this object
      // will get called, hence, there won't be any memory leak
      throw;
   }

   parent._pointer->_children.push_back(child);
   child->_childIt = --(parent._pointer->_children.end());

   return PreOrderIterator(child);
}

//______________________________________________________________________________

template <class T>
typename Tree<T>::PreOrderIterator Tree<T>::insertChild(const TreeIterator<T>& parent,
                                 const TreeIterator<T>& childNode,
                                 const T& data)
   throw(std::bad_alloc)
{

   TreeNode<T>* child;
   try {
      child = new TreeNode<T>(data, parent._pointer);
   }
   catch(std::bad_alloc& ex) {
      std::cerr << ex.what() << " : Failure to allocate memory for the new child when inserting" << std::endl;

      // Since we are not inside the constructor, the destructor for this object
      // will get called, hence, there won't be any memory leak
      throw;
   }

   typename std::list< TreeNode<T>* >::iterator it(childNode._pointer->_childIt);
   parent._pointer->_children.insert(it, child);
   child->_childIt = --it;

   return PreOrderIterator(child);
}

//______________________________________________________________________________

// If an iterator pointing to the end is passed (iterator pointing to null) the
// method will fail. NULL ITERATORS CAN'T BE PASSED AS AN ARGUMENT TO THIS FUNCTION
template <class T>
void Tree<T>::erase(TreeIterator<T>& node) throw(RootNotErasableException) {
   TreeNode<T>* nodePtr(node.getPointer());
   // By definition a tree has a single root, hence, the root node can't be
   // erased
   if(nodePtr == _root)
      throw RootNotErasableException("Error: Attempting to erase the root node");

   // Insert every child under the position that the iterator of the current
   // node indicates (in the parent node)
   typename std::list< TreeNode<T>* >::iterator it(nodePtr->_children.begin());
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
template <class T>
Tree<T> Tree<T>::prune(TreeIterator<T>& rootNode) {
   TreeNode<T>* nodePtr = rootNode.getPointer();

   // Erase the child reference to this node on the parent node if there is a
   // parent node
   nodePtr->_parent->_children.erase(nodePtr->_childIt);

   return Tree<T>(nodePtr);
}

//______________________________________________________________________________

// If an iterator pointing to the end is passed (iterator pointing to null) the
// method will fail. NULL ITERATORS CAN'T BE PASSED AS ARGUMENTS
template <class T>
void Tree<T>::chop(TreeIterator<T>& rootNode) {
   TreeNode<T>* rootPtr(rootNode.getPointer());
   TreeNode<T>* parentPtr(rootPtr->parent());

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
template <class T>
void Tree<T>::graftFront(const TreeIterator<T>& parent, Tree<T>& adoptTree) {
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
template <class T>
void Tree<T>::graftBack(const TreeIterator<T>& parent, Tree<T>& adoptTree) {
   // The current tree adopts the new tree created and assumes the responsability
   // of liberating the corresponding resources
   parent._pointer->_children.push_back(adoptTree._root);
   adoptTree._root->_childIt = --(parent._pointer->_children.end());
   adoptTree._root = NULL;
}

//______________________________________________________________________________

template <class T>
void Tree<T>::graftAt(const TreeIterator<T>& parent, const TreeIterator<T>& childNode, Tree<T>& adoptTree) {
   typename std::list< TreeNode<T>* >::iterator it(childNode._pointer->_childIt);
   parent._pointer->_children.insert(it, adoptTree._root);
   adoptTree._root->_childIt = --it;
   adoptTree._root = NULL;
}

//______________________________________________________________________________

template <class T>
Tree<T>::Tree(TreeNode<T>* root) {
   this->_root = root;
}

//______________________________________________________________________________

template <class T>
void Tree<T>::clone(const Tree<T>& source) throw(std::bad_alloc) {
   // If the tree already had data stored, delete it
   if(_root != NULL) {
      clean();
      _root = NULL;
   }

   // This map is going to tell us which node is the parent of who
   std::map< TreeNode<T>*, TreeNode<T>* > parentMap;
   parentMap[NULL] = NULL;

   // Allocate memory for the new root
   try {
      _root = new TreeNode<T>(*source.preBegin());
   }
   catch(std::bad_alloc& ex) {
      std::cerr << ex.what() << " : Failure to allocate memory for the root node when executing clone()" << std::endl;
      throw;
   }
   parentMap[source._root] = _root;

   for(PreOrderIterator srcIt = source.preBegin(), myIt = preBegin(); srcIt != source.preEnd(); ++srcIt, ++myIt) {
      // Temp variables
      TreeNode<T>* myPt = myIt.getPointer();
      TreeNode<T>* srcPt = srcIt.getPointer();
      PreOrderIterator tmpParent;
      tmpParent = srcIt.parent();

      // Link the current node to the corresponding parent
      myPt->_parent = parentMap[tmpParent.getPointer()];

      // Copy node data
      *myIt = *srcIt;

      // Allocate memory for descendants if any and put them in the dictionary
      typename std::list< TreeNode<T>* >::iterator it;
      for(it = srcPt->_children.begin(); it != srcPt->_children.end(); ++it) {
         TreeNode<T>* newChild;
         try {
            newChild = new TreeNode<T>;
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

template <class T>
void Tree<T>::clean() {
   // Use post-order iterator to erase each node
   if(_root != NULL)
      for(PostOrderIterator postIt = postBegin(); postIt != postEnd(); ++postIt)
         delete postIt.getPointer();
}















// *****************************************************************************
// *****************************************************************************
// *****************************************************************************
// ***                                                                       ***
// ***                                                                       ***
// ***                                                                       ***
// ***                                                                       ***
// ***                                                                       ***
// ***                                                                       ***
// ***                                                                       ***
// ***                                                                       ***
// ***                                                                       ***
// ***                                                                       ***
// ***                         TREE-ITERATOR HEADER                          ***
// ***                                                                       ***
// ***                                                                       ***
// ***                                                                       ***
// ***                                                                       ***
// ***                                                                       ***
// ***                                                                       ***
// ***                                                                       ***
// ***                                                                       ***
// ***                                                                       ***
// ***                                                                       ***
// *****************************************************************************
// *****************************************************************************
// *****************************************************************************

/**
 * Tree Iterator abstract class used to implement any kind of iterator to iterate
 * on a tree structure.
 *
 * This class has all the functionality that one would expect from a normal iterator.
 * Because an iterator to a tree is very special kind of iterator, it also implements
 * some other features to facilitate navigation through a tree structure.
 *
 * @author Francisco Aisa García
 * @version 0.1
 */
template <class T>
class TreeIterator {
   public:
      // =======================================================================
      //                     CONSTRUCTORS AND DESTRUCTORS
      // =======================================================================


      /**
       * Default constructor.
       *
       * It sets the tree iterator pointer to NULL.
       */
      inline TreeIterator();

      //________________________________________________________________________


      /**
       * Custom constructor.
       *
       * Due to copy constructor elision, this method has been made public, but
       * it should never be used by the client. Clients don't have to deal with
       * 'TreeNodes' the less they know about it, the better for everyone.
       *
       * @param data Pointer to the 'TreeNode' that this iterator will point.
       */
      inline TreeIterator(TreeNode<T>* data);

      //________________________________________________________________________

      /**
       * Copy constructor.
       *
       * @param source Source tree iterator.
       */
      inline TreeIterator(const TreeIterator<T>& source);

      //________________________________________________________________________

      /** Destructor. */
      inline virtual ~TreeIterator();


      // =======================================================================
      //                               OPERATORS
      // =======================================================================


      /**
       * Assignment operator.
       *
       * @param rhs Right hand side tree iterator to be assigned.
       * @return A reference to 'this' tree iterator.
       */
      inline TreeIterator<T>& operator=(const TreeIterator<T>& rhs);

      //________________________________________________________________________

      /**
       * Abstract pre-increment operator.
       *
       * This operator will make the iterator move through the starting position
       * in a predetermined way such as pre-order, in-order, post-order...
       *
       * Please note that because 'TreeIterator' is an abstract class, operator++(int)
       * won't be a part of its interface since a 'TreeIterator' can't be returned.
       * This operator MUST be implemented in every derived class in order to
       * sustain coherence.
       *
       * @return A reference to 'this' tree iterator.
       */
      virtual TreeIterator<T>& operator++() = 0;

      //________________________________________________________________________

      /**
       * Equality operator.
       *
       * @param rhs Right hand side tree iterator to be compared.
       * @return 'true' if both iterators point to the same tree node, 'false'
       * otherwise.
       */
      inline bool operator==(const TreeIterator<T>& rhs) const;

      //________________________________________________________________________

      /**
       * Inequality operator.
       *
       * @param rhs Right hand side tree iterator to be comared.
       * @return 'true' if the iterators to be compared are different, 'false'
       * otherwise.
       */
      inline bool operator!=(const TreeIterator<T>& rhs) const;

      //________________________________________________________________________

      /**
       * Reference operator.
       *
       * @return A pointer to the data contained in the node pointed by 'this' iterator.
       */
      inline T* operator->() const;

      //________________________________________________________________________

      /**
       * Dereference pointer.
       *
       * @return The data contained in the node pointed by 'this' iterator.
       */
      inline T& operator*() const;


      // =======================================================================
      //                            ELEMENT ACCESS
      // =======================================================================

      /**
       * Returns a tree iterator to the parent node of the node pointed by 'this'
       * iterator if any.
       *
       * @return A reference to a tree node. The reason why we return a reference
       * is so we can use polymorphism (because 'TreeIterator' is abstract). This
       * method MUST NEVER be used to modify the returned value, because static
       * value is returned.
       */
      inline virtual TreeIterator<T>& parent() = 0;

      //________________________________________________________________________

      /**
       * Returns a tree iterator to the first child node of the node pointed by 'this'
       * iterator.
       *
       * @return A reference to a tree node. The reason why we return a reference
       * is so we can use polymorphism (because 'TreeIterator' is abstract). This
       * method MUST NEVER be used to modify the returned value, because static
       * value is returned.
       */
      virtual TreeIterator<T>& firstChild() = 0;

      //________________________________________________________________________

      /**
       * Returns a tree iterator to the last child node of the node pointed by 'this'
       * iterator.
       *
       * @return A reference to a tree node. The reason why we return a reference
       * is so we can use polymorphism (because 'TreeIterator' is abstract). This
       * method MUST NEVER be used to modify the returned value, because static
       * value is returned.
       */
      virtual TreeIterator<T>& lastChild() = 0;

      //________________________________________________________________________

      /**
       * Returns a tree iterator to the next child node of the node pointed by 'this'
       * iterator.
       *
       * The next child returned will depend on the last access we made to the
       * current node. Please note that this method doesn't do any kind of range
       * checking, which means that the client is responsible for iterating through
       * the node's children safely.
       *
       * @return A reference to a tree node. The reason why we return a reference
       * is so we can use polymorphism (because 'TreeIterator' is abstract). This
       * method MUST NEVER be used to modify the returned value, because static
       * value is returned.
       */
      virtual TreeIterator<T>& nextChild() = 0;

      //________________________________________________________________________

      /**
       * Returns a tree iterator to the previous child node of the node pointed by 'this'
       * iterator.
       *
       * The previous child returned will depend on the last access we made to the
       * current node. Please note that this method doesn't do any kind of range
       * checking, which means that the client is responsible for iterating through
       * the node's children safely.
       * 
       * @return A reference to a tree node. The reason why we return a reference
       * is so we can use polymorphism (because 'TreeIterator' is abstract). This
       * method MUST NEVER be used to modify the returned value, because static
       * value is returned.
       */
      virtual TreeIterator<T>& previousChild() = 0;


      // =======================================================================
      //                               CAPACITY
      // =======================================================================

      /**
       * Get the number of children that the node pointed by 'this' tree iterator
       * has.
       *
       * @return An unsigned integer indicating the number of children that current
       * tree node has.
       */
      inline unsigned int nChildren();

   protected:
      // =======================================================================
      //                            PROTECTED METHODS
      // =======================================================================


      /**
       * Get the pointer to the 'TreeNode' pointed by 'this' tree iterator.
       *
       * Note that a pointer to a 'TreeNode' is returned (and not a const pointer).
       * Be careful when using it, the pointer returned MUST NOT be modified.
       *
       * @return A pointer to the 'TreeNode' pointed by 'this' tree iterator.
       */
      inline TreeNode<T>* getPointer();

      //________________________________________________________________________

      /**
       * Set the value of the pointer pointed by 'this' tree iterator.
       *
       * @param newPointer Pointer to the new 'TreeNode' that 'this' tree iterator
       * will point to.
       */
      inline void setPointer(TreeNode<T>* newPointer);

      //________________________________________________________________________

      /**
       * Assignment operator (with a given pointer to a 'TreeNode'.
       *
       * A copy of the pointer is made, meaning that the current tree iterator
       * will point to the given pointer on the right hand side.
       *
       * @param rhs Right hand side 'TreeNode' to be assigned. Note that we don't
       * assign a 'TreeIterator'.
       * @return A reference to 'this' tree iterator.
       */
      inline TreeIterator<T>& operator=(TreeNode<T>* rhs);


      // =======================================================================
      //                            PROTECTED FIELDS
      // =======================================================================


      /**
       * Iterator to the parent list, that indicates which position occupies the
       * node pointed by 'this' tree iterator.
       *
       * _currentChild need not be initialized because it should always be called
       * by firstChild() or lastChild(), meaning that its value will be override
       * during each call, furthermore, this iterator shouldn't be copied when using
       * operator= because we want to enforce the use of firstChild() and lastChild()
       */
      typename std::list< TreeNode<T>* >::iterator _currentChild;

   private:
      // =======================================================================
      //                            FRIEND CLASSES
      // =======================================================================


      friend class Tree<T>;


      // =======================================================================
      //                            PRIVATE METHODS
      // =======================================================================


      /**
       * Clone the content of a given tree iterator to 'this' tree iterator.
       *
       * @param rhs Right hand side tree iterator to be cloned.
       */
      inline void clone(const TreeIterator<T>& rhs);


      // =======================================================================
      //                            PRIVATE FIELDS
      // =======================================================================


      /** Pointer to the 'TreeNode' that holds the data */
      TreeNode<T>* _pointer;
};


// *****************************************************************************
// *****************************************************************************
// *****************************************************************************
// ***                                                                       ***
// ***                                                                       ***
// ***                                                                       ***
// ***                                                                       ***
// ***                                                                       ***
// ***                                                                       ***
// ***                                                                       ***
// ***                                                                       ***
// ***                                                                       ***
// ***                                                                       ***
// ***                     TREE-ITERATOR IMPLEMENTATION                      ***
// ***                                                                       ***
// ***                                                                       ***
// ***                                                                       ***
// ***                                                                       ***
// ***                                                                       ***
// ***                                                                       ***
// ***                                                                       ***
// ***                                                                       ***
// ***                                                                       ***
// ***                                                                       ***
// *****************************************************************************
// *****************************************************************************
// *****************************************************************************


template <class T>
TreeIterator<T>::TreeIterator() : _pointer(NULL) {
   // Nothing to do
}

//______________________________________________________________________________

template <class T>
TreeIterator<T>::TreeIterator(TreeNode<T>* data) : _pointer(data) {
   // Nothing to do
}

//______________________________________________________________________________

template <class T>
TreeIterator<T>::TreeIterator(const TreeIterator<T>& source) : _pointer(source._pointer) {
   // Nothing to do
}

//______________________________________________________________________________

template <class T>
TreeIterator<T>::~TreeIterator() {
   // Nothing to do
}

//______________________________________________________________________________

template <class T>
TreeIterator<T>& TreeIterator<T>::operator=(const TreeIterator<T>& rhs) {
   if(this != &rhs)
      clone(rhs);

   return *this;
}

//______________________________________________________________________________

template <class T>
TreeIterator<T>& TreeIterator<T>::operator=(TreeNode<T>* rhs) {
   if(_pointer != rhs) {
      _pointer = rhs;
   }

   return *this;;
}

//______________________________________________________________________________

template <class T>
bool TreeIterator<T>::operator==(const TreeIterator<T>& rhs) const {
   return _pointer == rhs._pointer;
}

//______________________________________________________________________________

template <class T>
bool TreeIterator<T>::operator!=(const TreeIterator<T>& rhs) const {
   return _pointer != rhs._pointer;
}

//______________________________________________________________________________

template <class T>
T* TreeIterator<T>::operator->() const {
   return &(_pointer->_data);
}

//______________________________________________________________________________

template <class T>
T& TreeIterator<T>::operator*() const {
   return *(operator->());
}

//______________________________________________________________________________

template <class T>
unsigned int TreeIterator<T>::nChildren() {
   return _pointer->_children.size();
}

//______________________________________________________________________________

template <class T>
TreeNode<T>* TreeIterator<T>::getPointer() {
   return _pointer;
}

//______________________________________________________________________________

template <class T>
void TreeIterator<T>::setPointer(TreeNode<T>* newPointer) {
   _pointer = newPointer;
}

//______________________________________________________________________________

template <class T>
void TreeIterator<T>::clone(const TreeIterator<T>& rhs) {
   _pointer = rhs._pointer;
}














// *****************************************************************************
// *****************************************************************************
// *****************************************************************************
// ***                                                                       ***
// ***                                                                       ***
// ***                                                                       ***
// ***                                                                       ***
// ***                                                                       ***
// ***                                                                       ***
// ***                                                                       ***
// ***                                                                       ***
// ***                                                                       ***
// ***                                                                       ***
// ***                       PRE-ORDER ITERATOR HEADER                       ***
// ***                                                                       ***
// ***                                                                       ***
// ***                                                                       ***
// ***                                                                       ***
// ***                                                                       ***
// ***                                                                       ***
// ***                                                                       ***
// ***                                                                       ***
// ***                                                                       ***
// ***                                                                       ***
// *****************************************************************************
// *****************************************************************************
// *****************************************************************************

/**
 * Pre-order iterator to iterate on a tree structure.
 *
 * This class allows the user to iterate through a tree in a pre-order fashion. It
 * also lets the user navigate through descendants and ancestors in a secuential fashion.
 *
 * @author Francisco Aisa García
 * @version 0.1
 */
template <class T>
class Tree<T>::PreOrderIterator : public TreeIterator<T> {
   public:
      // =======================================================================
      //                     CONSTRUCTORS AND DESTRUCTORS
      // =======================================================================


      /**
       * Default constructor.
       *
       * It makes the iterator pointer point to NULL.
       */
      inline PreOrderIterator();

      //________________________________________________________________________

      /**
       * Conversion constructor.
       *
       * It transforms a post-order iterator into a pre-order iterator.
       *
       * @param postIt 'PostOrderIterator' to be converted.
       */
      inline PreOrderIterator(const PostOrderIterator& postIt);

      //________________________________________________________________________

      /**
       * Custom constructor.
       *
       * @param data Pointer to the 'TreeNode' that this iterator will point.
       */
      PreOrderIterator(TreeNode<T>* data);

      //________________________________________________________________________

      /**
       * Copy constructor.
       *
       * @param source Source pre-order iterator to be copied.
       */
      inline PreOrderIterator(const PreOrderIterator& source);

      //________________________________________________________________________

      /** Destructor. */
      inline virtual ~PreOrderIterator();


      // =======================================================================
      //                               OPERATORS
      // =======================================================================


      /**
       * Assignment operator.
       *
       * A copy of the pointer contained in the right hand side iterator is done,
       * which means that 'this' iterator will point to the same node.
       *
       * @param rhs Right hand side tree iterator to be assigned.
       * @return A reference to 'this' 'PreOrderIterator'.
       */
      PreOrderIterator& operator=(const TreeIterator<T>& rhs);

      //________________________________________________________________________

      /**
       * Pre-increment operator.
       *
       * Each time this operator is executed, the next node (following the pre-order
       * fashion) will be retrieved.
       *
       * @return A reference to 'this' 'PreOrderIterator'.
       */
      virtual PreOrderIterator& operator++();

      //________________________________________________________________________

      /**
       * Post-increment operator.
       *
       * Each time this operator is executed, the next node (following the pre-order
       * fashion) will be retrieved.
       *
       * @param notUsed This argument is not used.
       * @return A 'PreOrderIterator' to the node that the iterator pointed to before
       * iterating to the next node.
       */
      inline PreOrderIterator operator++(int notUsed);


      // =======================================================================
      //                            ELEMENT ACCESS
      // =======================================================================


      /**
       * Returns a tree iterator to the parent node of the node pointed by 'this'
       * iterator if any.
       *
       * @return A 'PreOrderIterator' to the parent node.
       */
      inline virtual TreeIterator<T>& parent();

      //________________________________________________________________________

      /**
       * Returns a tree iterator to the first child node of the node pointed by 'this'
       * iterator.
       *
       * @return A 'PreOrderIterator' to the first child of the node pointed by
       * 'this' iterator.
       */
      virtual TreeIterator<T>& firstChild();

      //________________________________________________________________________

      /**
       * Returns a tree iterator to the last child node of the node pointed by 'this'
       * iterator.
       *
       * @return A 'PreOrderIterator' to the last child of the node pointed by 'this'
       * iterator.
       */
      virtual TreeIterator<T>& lastChild();

      //________________________________________________________________________

      /**
       * Returns a tree iterator to the next child node of the node pointed by 'this'
       * iterator.
       *
       * The next child returned will depend on the last access we made to the
       * current node. Please note that this method doesn't do any kind of range
       * checking, which means that the client is responsible for iterating through
       * the node's children safely.
       *
       * @return A 'PreOrderIterator' to the next child of the node pointed by 'this'
       * iterator.
       */
      virtual TreeIterator<T>& nextChild();

      //________________________________________________________________________

      /**
       * Returns a tree iterator to the previous child node of the node pointed by 'this'
       * iterator.
       *
       * The previous child returned will depend on the last access we made to the
       * current node. Please note that this method doesn't do any kind of range
       * checking, which means that the client is responsible for iterating through
       * the node's children safely.
       *
       * @return A 'PreOrderIterator' to the previous child of the node pointed by 'this'
       * iterator.
       */
      virtual TreeIterator<T>& previousChild();

   private:
      // =======================================================================
      //                            FRIEND METHODS
      // =======================================================================


      friend PreOrderIterator Tree<T>::preBegin() const;
      friend PreOrderIterator Tree<T>::preEnd() const;
      friend PreOrderIterator Tree<T>::pushBackChild(const TreeIterator<T>& parent, const T& data) throw(std::bad_alloc);
      friend PreOrderIterator Tree<T>::pushFrontChild(const TreeIterator<T>& parent, const T& data) throw(std::bad_alloc);
      friend PreOrderIterator Tree<T>::insertChild(const TreeIterator<T>& parent, const TreeIterator<T>& childNode, const T& data) throw(std::bad_alloc);


      // =======================================================================
      //                            PRIVATE FIELDS
      // =======================================================================


      /** Needed to know which is the next node to visit when using operator++ */
      std::stack< std::pair<TreeNode<T>*, typename std::list< TreeNode<T>* >::iterator> > _pathStack;
};


// *****************************************************************************
// *****************************************************************************
// *****************************************************************************
// ***                                                                       ***
// ***                                                                       ***
// ***                                                                       ***
// ***                                                                       ***
// ***                                                                       ***
// ***                                                                       ***
// ***                                                                       ***
// ***                                                                       ***
// ***                                                                       ***
// ***                                                                       ***
// ***                   PRE-ORDER ITERATOR IMPLEMENTATION                   ***
// ***                                                                       ***
// ***                                                                       ***
// ***                                                                       ***
// ***                                                                       ***
// ***                                                                       ***
// ***                                                                       ***
// ***                                                                       ***
// ***                                                                       ***
// ***                                                                       ***
// ***                                                                       ***
// *****************************************************************************
// *****************************************************************************
// *****************************************************************************

// Parent sets _pointer to NULL
template <class T>
Tree<T>::PreOrderIterator::PreOrderIterator() {
   // Nothing to do
}

//______________________________________________________________________________

template <class T>
Tree<T>::PreOrderIterator::PreOrderIterator(const PostOrderIterator& postIt) {
   TreeIterator<T>::setPointer(postIt._pointer);
}

//______________________________________________________________________________

template <class T>
Tree<T>::PreOrderIterator::PreOrderIterator(TreeNode<T>* data) : TreeIterator<T>(data) {
   // Nothing to do
}

//______________________________________________________________________________

template <class T>
Tree<T>::PreOrderIterator::PreOrderIterator(const PreOrderIterator& source) : TreeIterator<T>(source), _pathStack(source._pathStack) {
   // Nothing to do
}

//______________________________________________________________________________

template <class T>
Tree<T>::PreOrderIterator::~PreOrderIterator() {
   // Nothing to do
}

//______________________________________________________________________________

template <class T>
typename Tree<T>::PreOrderIterator& Tree<T>::PreOrderIterator::operator=(const TreeIterator<T>& rhs) {
   if(this != &rhs) {
      TreeIterator<T>::operator=(rhs);

      // Clear the stack
      while(!_pathStack.empty()) {
         _pathStack.pop();
      }
   }

   return *this;
}

//______________________________________________________________________________

// THE CURRENT NODE CAN'T BE NULL
template <class T>
typename Tree<T>::PreOrderIterator& Tree<T>::PreOrderIterator::operator++() {
   std::pair< TreeNode<T>*, typename std::list< TreeNode<T>* >::iterator > topNode;
   typename std::list< TreeNode<T>* >::iterator tmp;
   // nodePt is the pointer to the TreeNode stored inside the TreeIterator
   TreeNode<T>* nodePt = TreeIterator<T>::getPointer();

   int nChildren = nodePt->nChildren();
   // If the current node has children, we must visit them and keep the current
   // node in the stack in case there are more children
   if(nChildren > 0) {
      // If the current node is the one on the top of the stack, get the next
      // child to visit
      typename std::list< TreeNode<T>* >::iterator nextChild;
      if(_pathStack.empty() || nodePt != _pathStack.top().first) {
         nextChild = nodePt->_children.begin();
         tmp = nextChild;
         _pathStack.push(std::pair< TreeNode<T>*, typename std::list< TreeNode<T>* >::iterator >(nodePt, ++tmp));
      }
      else {
         topNode = _pathStack.top();
         nextChild = topNode.second;
         tmp = nextChild;
         _pathStack.top() = std::pair<TreeNode<T>*, typename std::list< TreeNode<T>* >::iterator >(topNode.first, ++tmp);
      }

      TreeIterator<T>::setPointer(*nextChild);
   }
   else {
      while(!_pathStack.empty()) {
         topNode = _pathStack.top();
         // If there are children that haven't been visited
         if(topNode.second != topNode.first->_children.end()) {
            // Current node is the next child to visit
            tmp = topNode.second;
            TreeIterator<T>::setPointer(*topNode.second);
            // Update next child to be visited
            _pathStack.top() = std::pair<TreeNode<T>*, typename std::list< TreeNode<T>* >::iterator>(topNode.first, ++tmp);

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
      TreeIterator<T>::setPointer(NULL);
   }

   return *this;
}

//______________________________________________________________________________

template <class T>
typename Tree<T>::PreOrderIterator Tree<T>::PreOrderIterator::operator++(int notUsed) {
   PreOrderIterator tmp(*this);
   ++(*this);
   return tmp;
}

//______________________________________________________________________________

template <class T>
TreeIterator<T>& Tree<T>::PreOrderIterator::parent() {
   static Tree<T>::PreOrderIterator tmp;
   tmp.setPointer(TreeIterator<T>::getPointer()->_parent);
   return tmp;
}

//______________________________________________________________________________

template <class T>
TreeIterator<T>& Tree<T>::PreOrderIterator::firstChild() {
   static Tree<T>::PreOrderIterator tmp;

   // Update the current child selected
   TreeIterator<T>::_currentChild = TreeIterator<T>::getPointer()->_children.begin();

   // Build a pre-order iterator
   tmp.setPointer(*TreeIterator<T>::_currentChild);
   return tmp;
}

//______________________________________________________________________________

template <class T>
TreeIterator<T>& Tree<T>::PreOrderIterator::lastChild() {
   static Tree<T>::PreOrderIterator tmp;

   // Update the current child selected
   TreeIterator<T>::_currentChild = --(TreeIterator<T>::getPointer()->_children.end());

   // Build a pre-order iterator
   tmp.setPointer(*TreeIterator<T>::_currentChild);
   return tmp;
}

//______________________________________________________________________________

template <class T>
TreeIterator<T>& Tree<T>::PreOrderIterator::nextChild() {
   static Tree<T>::PreOrderIterator tmp;

   // Update iterator position
   ++TreeIterator<T>::_currentChild;

   tmp.setPointer(*TreeIterator<T>::_currentChild);
   return tmp;
}

//______________________________________________________________________________

template <class T>
TreeIterator<T>& Tree<T>::PreOrderIterator::previousChild() {
   static Tree<T>::PreOrderIterator tmp;

   // Update iterator position
   --TreeIterator<T>::_currentChild;

   tmp.setPointer(*TreeIterator<T>::_currentChild);
   return tmp;
}
















// *****************************************************************************
// *****************************************************************************
// *****************************************************************************
// ***                                                                       ***
// ***                                                                       ***
// ***                                                                       ***
// ***                                                                       ***
// ***                                                                       ***
// ***                                                                       ***
// ***                                                                       ***
// ***                                                                       ***
// ***                                                                       ***
// ***                                                                       ***
// ***                      POST-ORDER ITERATOR HEADER                       ***
// ***                                                                       ***
// ***                                                                       ***
// ***                                                                       ***
// ***                                                                       ***
// ***                                                                       ***
// ***                                                                       ***
// ***                                                                       ***
// ***                                                                       ***
// ***                                                                       ***
// ***                                                                       ***
// *****************************************************************************
// *****************************************************************************
// *****************************************************************************

/**
 * Post-order iterator to iterate on a tree structure.
 *
 * This class allows the user to iterate through a tree in a post-order fashion. It
 * also lets the user navigate through descendants and ancestors in a secuential fashion.
 *
 * @author Francisco Aisa García
 * @version 0.1
 */
template <class T>
class Tree<T>::PostOrderIterator : public TreeIterator<T> {
   public:
      // =======================================================================
      //                     CONSTRUCTORS AND DESTRUCTORS
      // =======================================================================


      /**
       * Default constructor.
       *
       * It makes the iterator pointer point to NULL.
       */
      inline PostOrderIterator();

      //________________________________________________________________________

      /**
       * Conversion constructor.
       *
       * It transforms a pre-order iterator into a post-order iterator. In the tree
       * class, when new nodes are inserted/created, pre-order iterators to them
       * are returned. For the sake of uniformity, post-order iterators can be used
       * with those methods thanks to this conversion constructor. Use it with care
       * since is not as efficient as using a pre-order iterator (due to the construction
       * of a temporary iterator).
       *
       * @param preIt 'PreOrderIterator' to be converted.
       */
      PostOrderIterator(const PreOrderIterator& preIt);

      //________________________________________________________________________

      /**
       * Custom constructor.
       *
       * Note that when the post-order iterator is constructed, the iterator actually
       * doesn't point to the node pointed by the iterator given, instead, it points
       * to the first node to be retreived in post-order.
       *
       * @param data Pointer to the 'TreeNode' that this iterator will point.
       */
      PostOrderIterator(TreeNode<T>* data);

      //________________________________________________________________________

      /**
       * Copy constructor.
       *
       * Note that the pointer that this iterator will point to after the construction
       * won't be the one to which the source iterator points to. Instead, this
       * iterator will point to the first node to be retreived in post-order (starting
       * from the node pointed by the given iterator).
       *
       * @param source Source post-order iterator to be copied.
       */
      PostOrderIterator(const PostOrderIterator& source);

      //________________________________________________________________________

      /** Destructor. */
      inline virtual ~PostOrderIterator();


      // =======================================================================
      //                               OPERATORS
      // =======================================================================


      /**
       * Assignment operator.
       *
       * Note that the pointer that this iterator will point to after the assignment
       * won't be the one to which the right hand side iterator points to. Instead, this
       * iterator will point to the first node to be retreived in post-order (starting
       * from the node pointed by the given iterator).
       *
       * Also, if the assigned iterator to the right has just been copy constructed,
       * then, the iterator will actually point to the node that the given iterator
       * points to.
       *
       * @param rhs Right hand side 'PostOrderIterator' to be assigned.
       * @return A reference to 'this' 'PostOrderIterator'.
       */
      PostOrderIterator& operator=(const PostOrderIterator& rhs);

      //________________________________________________________________________

      /**
       * Pre-increment operator.
       *
       * Each time this operator is executed, the next node (following the post-order
       * fashion) will be retrieved.
       *
       * @return A reference to 'this' 'PostOrderIterator'.
       */
      virtual PostOrderIterator& operator++();

      //________________________________________________________________________

      /**
       * Post-increment operator.
       *
       * Each time this operator is executed, the next node (following the post-order
       * fashion) will be retrieved.
       *
       * @param notUsed This argument is not used.
       * @return A 'PostOrderIterator' to the node that the iterator pointed to before
       * iterating to the next node.
       */
      inline PostOrderIterator operator++(int notUsed);


      // =======================================================================
      //                            ELEMENT ACCESS
      // =======================================================================


      /**
       * Returns a tree iterator to the parent node of the node pointed by 'this'
       * iterator if any.
       *
       * @return A 'PostOrderIterator' to the parent node.
       */
      inline virtual TreeIterator<T>& parent();

      //________________________________________________________________________

      /**
       * Returns a tree iterator to the first child node of the node pointed by 'this'
       * iterator.
       *
       * @return A 'PostOrderIterator' to the first child of the node pointed by
       * 'this' iterator.
       */
      virtual TreeIterator<T>& firstChild();

      //________________________________________________________________________

      /**
       * Returns a tree iterator to the last child node of the node pointed by 'this'
       * iterator.
       *
       * @return A 'PostOrderIterator' to the last child of the node pointed by 'this'
       * iterator.
       */
      virtual TreeIterator<T>& lastChild();

      //________________________________________________________________________

      /**
       * Returns a tree iterator to the next child node of the node pointed by 'this'
       * iterator.
       *
       * The next child returned will depend on the last access we made to the
       * current node. Please note that this method doesn't do any kind of range
       * checking, which means that the client is responsible for iterating through
       * the node's children safely.
       *
       * @return A 'PostOrderIterator' to the next child of the node pointed by 'this'
       * iterator.
       */
      virtual TreeIterator<T>& nextChild();

      //________________________________________________________________________

      /**
       * Returns a tree iterator to the previous child node of the node pointed by 'this'
       * iterator.
       *
       * The previous child returned will depend on the last access we made to the
       * current node. Please note that this method doesn't do any kind of range
       * checking, which means that the client is responsible for iterating through
       * the node's children safely.
       *
       * @return A 'PostOrderIterator' to the previous child of the node pointed by 'this'
       * iterator.
       */
      virtual TreeIterator<T>& previousChild();

   private:
      // =======================================================================
      //                            FRIEND METHODS
      // =======================================================================


      friend PostOrderIterator Tree<T>::postBegin() const;
      friend PostOrderIterator Tree<T>::postEnd() const;


      // =======================================================================
      //                            PRIVATE FIELDS
      // =======================================================================


      /** Needed to know which is the next node to visit when using operator++ */
      std::stack< std::pair<TreeNode<T>*, typename std::list< TreeNode<T>* >::iterator> > _pathStack;

      //________________________________________________________________________

      /**
       * Because copy constructor elision occurs, this field will make sure that
       * the state of the iterator is correct.
       */
      bool _justCreated;
};

// *****************************************************************************
// *****************************************************************************
// *****************************************************************************
// ***                                                                       ***
// ***                                                                       ***
// ***                                                                       ***
// ***                                                                       ***
// ***                                                                       ***
// ***                                                                       ***
// ***                                                                       ***
// ***                                                                       ***
// ***                                                                       ***
// ***                                                                       ***
// ***                  POST-ORDER ITERATOR IMPLEMENTATION                   ***
// ***                                                                       ***
// ***                                                                       ***
// ***                                                                       ***
// ***                                                                       ***
// ***                                                                       ***
// ***                                                                       ***
// ***                                                                       ***
// ***                                                                       ***
// ***                                                                       ***
// ***                                                                       ***
// *****************************************************************************
// *****************************************************************************
// *****************************************************************************

// Parent sets _pointer to NULL
template <class T>
Tree<T>::PostOrderIterator::PostOrderIterator() : _justCreated(false) {
   // Nothing to do
}

//______________________________________________________________________________

template <class T>
Tree<T>::PostOrderIterator::PostOrderIterator(const PreOrderIterator& preIt) {
   TreeIterator<T>::setPointer(preIt._pointer);
   TreeNode<T>* ptr = preIt._pointer;
   if(ptr != NULL) {
      _pathStack.push(std::pair<TreeNode<T>*, typename std::list< TreeNode<T>* >::iterator >(ptr, ptr->_children.begin()));
      operator++();
      _justCreated = true;
   }
}

//______________________________________________________________________________

template <class T>
Tree<T>::PostOrderIterator::PostOrderIterator(TreeNode<T>* data) : TreeIterator<T>(data) {
   TreeNode<T>* ptr = TreeIterator<T>::getPointer();
   if(ptr != NULL) {
      _pathStack.push(std::pair<TreeNode<T>*, typename std::list< TreeNode<T>* >::iterator >(ptr, ptr->_children.begin()));
      operator++();
      _justCreated = true;
   }
}

//______________________________________________________________________________

template <class T>
Tree<T>::PostOrderIterator::PostOrderIterator(const PostOrderIterator& source) : TreeIterator<T>(source) {
   TreeNode<T>* ptr = TreeIterator<T>::getPointer();
   if(ptr != NULL) {
      _pathStack.push(std::pair<TreeNode<T>*, typename std::list< TreeNode<T>* >::iterator >(ptr, ptr->_children.begin()));
      operator++();
      _justCreated = true;
   }
}

//______________________________________________________________________________

template <class T>
Tree<T>::PostOrderIterator::~PostOrderIterator() {
   // Nothing to do
}

//______________________________________________________________________________

template <class T>
typename Tree<T>::PostOrderIterator& Tree<T>::PostOrderIterator::operator=(const PostOrderIterator& rhs) {
   if(this != &rhs) {
      TreeIterator<T>::operator=(rhs);

      // If the right hand side element has already been used, we copy it normally
      // if not. We just copy the stack state because the constructor has just been
      // executed, which means that the state of the iterator has already been set
      if(!rhs._justCreated) {
         // Clear the stack
         while(!_pathStack.empty()) {
            _pathStack.pop();
         }

         // Put the first element to be printed at the top of the stack
         TreeNode<T>* rhsPtr(TreeIterator<T>::getPointer());
         if(rhsPtr != NULL) {
            _pathStack.push(std::pair<TreeNode<T>*, typename std::list< TreeNode<T>* >::iterator >(rhsPtr, rhsPtr->_children.begin()));
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

template <class T>
typename Tree<T>::PostOrderIterator& Tree<T>::PostOrderIterator::operator++() {
   typename std::list< TreeNode<T>* >::iterator tmp;

   // Raise a flag indicating that this iterator is no longer on the initialization state
   _justCreated = false;
   while(!_pathStack.empty()) {
      std::pair<TreeNode<T>*, typename std::list< TreeNode<T>* >::iterator> topNode = _pathStack.top();

      // If there are children nodes non explored, find the last one
      while(topNode.second != topNode.first->_children.end()) {
         tmp = topNode.second;
         _pathStack.top() = std::pair<TreeNode<T>*, typename std::list< TreeNode<T>* >::iterator>(topNode.first, ++tmp);
         _pathStack.push(std::pair<TreeNode<T>*, typename std::list< TreeNode<T>* >::iterator>(*topNode.second, (*topNode.second)->_children.begin()));
         topNode = _pathStack.top();
      }

      _pathStack.pop();
      TreeIterator<T>::setPointer(topNode.first);

      return *this;
   }

   TreeIterator<T>::setPointer(NULL);
   return *this;
}

//______________________________________________________________________________

template <class T>
typename Tree<T>::PostOrderIterator Tree<T>::PostOrderIterator::operator++(int notUsed) {
   PostOrderIterator tmp(*this);
   ++(*this);
   return tmp;
}

//______________________________________________________________________________

template <class T>
TreeIterator<T>& Tree<T>::PostOrderIterator::parent() {
   static Tree<T>::PostOrderIterator tmp;
   tmp.setPointer(TreeIterator<T>::getPointer()->_parent);
   return tmp;
}

//______________________________________________________________________________

template <class T>
TreeIterator<T>& Tree<T>::PostOrderIterator::firstChild() {
   static Tree<T>::PostOrderIterator tmp;

   // Update the current child selected
   TreeIterator<T>::_currentChild = TreeIterator<T>::getPointer()->_children.begin();

   // Build a post-order iterator
   tmp.setPointer(*TreeIterator<T>::_currentChild);
   return tmp;
}

//______________________________________________________________________________

template <class T>
TreeIterator<T>& Tree<T>::PostOrderIterator::lastChild() {
   static Tree<T>::PostOrderIterator tmp;

   // Update the current child selected
   TreeIterator<T>::_currentChild = --(TreeIterator<T>::getPointer()->_children.end());

   // Build a post-order iterator
   tmp.setPointer(*TreeIterator<T>::_currentChild);
   return tmp;
}

//______________________________________________________________________________

template <class T>
TreeIterator<T>& Tree<T>::PostOrderIterator::nextChild() {
   static Tree<T>::PostOrderIterator tmp;

   // Update iterator position
   ++TreeIterator<T>::_currentChild;

   tmp.setPointer(*TreeIterator<T>::_currentChild);
   return tmp;
}

//______________________________________________________________________________

template <class T>
TreeIterator<T>& Tree<T>::PostOrderIterator::previousChild() {
   static Tree<T>::PostOrderIterator tmp;

   // Update iterator position
   --TreeIterator<T>::_currentChild;

   tmp.setPointer(*TreeIterator<T>::_currentChild);
   return tmp;
}

#endif