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
#include <stdexcept>
#include <stdlib.h>
#include <cstring>
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


template <class T>
class TreeNode {
   public:
      TreeNode();
      TreeNode(const T& data);
      TreeNode(const T& data, TreeNode<T>* parent);
      // Careful!!! It copies the references
      TreeNode(const TreeNode<T>& source);

      virtual ~TreeNode();

      // WE NEED TO RETURN AN ITERATOR
      TreeNode<T>& operator=(const TreeNode<T>& rhs);
      TreeNode<T>& operator=(const T& rightData);

      friend std::ostream& operator<< <T>(std::ostream& out, const TreeNode<T>& node);

      inline TreeNode<T>* const parent() const;
      inline int nChildren();
   private:
      T _data;
      TreeNode<T>* _parent;
      typename std::list< TreeNode<T>* >::iterator _childIt;
      std::list< TreeNode<T>* > _children;

      friend class Tree<T>;
      friend class TreeIterator<T>;

      void clone(const TreeNode<T>& source);
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

// COMPLETE COPY OF A TREE NODE, POINTERS ARE COPIED!! BE CAREFUL USING IT
template <class T>
TreeNode<T>::TreeNode(const TreeNode<T>& source) :
   _data(source._data),
   _parent(source._parent),
   _childIt(source._childIt),
   _children(source._children)
{
   // Nothing to do
}

//______________________________________________________________________________

template <class T>
TreeNode<T>::~TreeNode() {
   // Nothing to do
   // The destructors of the objects contained are called here automatically
}

//______________________________________________________________________________

template <class T>
TreeNode<T>& TreeNode<T>::operator=(const TreeNode<T>& rhs) {
   if(this != &rhs)
      clone(rhs);

   return *this;
}

//______________________________________________________________________________

template <class T>
TreeNode<T>& TreeNode<T>::operator=(const T& rightData) {
   _data = rightData;

   return *this;
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

//______________________________________________________________________________

// COMPLETE COPY OF A TREE NODE, POINTERS ARE COPIED!! BE CAREFUL USING IT
template <class T>
void TreeNode<T>::clone(const TreeNode<T>& source) {
   _data = source._data;
   _parent = source._parent;
   _childIt = source._childIt;
   _children = source._children;
}

#endif
