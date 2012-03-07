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

#ifndef __TREE_NODE_H__
#define __TREE_NODE_H__

#include <iostream>
#include <list>


// *****************************************************************************
//                             FORWARD DELCARATIONS
// *****************************************************************************


template <class T>
class TreeNode;

template <class T>
class TreeIterator;

template <class T>
class Tree;

template <class T>
std::ostream& operator<< (std::ostream &out, const TreeNode<T>& node);


// *****************************************************************************
//                                   HEADER
// *****************************************************************************

/*
 * Operator= and copy constructor won't be implemented in this class. When a
 * tree node is copied, the references to parent and children shouldn't be copied;
 * instead, new memory should be allocated. 
 * This responsibility lies on the tree structure, hence, the tree will be doing
 * that job; no need for us to implement such methods here.
 */

template <class T>
class TreeNode {
   public:
      inline TreeNode();
      inline TreeNode(const T& data);
      inline TreeNode(const T& data, TreeNode<T>* parent);

      inline ~TreeNode();

      friend std::ostream& operator<< <T>(std::ostream& out, const TreeNode<T>& node);

      inline TreeNode<T>* const parent() const;
      inline int nChildren();

   private:
      // FRIEND CLASSES
      friend class Tree<T>;
      friend class TreeIterator<T>;

      // PRIVATE FIELDS
      T _data;
      TreeNode<T>* _parent;
      typename std::list< TreeNode<T>* >::iterator _childIt;
      std::list< TreeNode<T>* > _children;
};


// *****************************************************************************
//                               IMPLEMENTATION
// *****************************************************************************


template <class T>
TreeNode<T>::TreeNode() : _parent(NULL) {
   // Nothing to do
}

//______________________________________________________________________________

// Once created, the iterator has to be modified manually
template <class T>
TreeNode<T>::TreeNode(const T& data) : _data(data), _parent(NULL) {
   // Nothing to do
}

//______________________________________________________________________________

// Once created, the iterator has to be modified manually
template <class T>
TreeNode<T>::TreeNode(const T& data, TreeNode<T>* parent) : _data(data), _parent(parent) {
   // Nothing to do
}

//______________________________________________________________________________

template <class T>
TreeNode<T>::~TreeNode() {
   // Nothing to do
}

//______________________________________________________________________________

template <class T>
std::ostream& operator<<(std::ostream& out, const TreeNode<T>& node) {
   out << node._data;

   return out;
}

//______________________________________________________________________________

template <class T>
TreeNode<T>* const TreeNode<T>::parent() const {
   return _parent;
}

//______________________________________________________________________________

template <class T>
int TreeNode<T>::nChildren() {
   return _children.size();
}

#endif
