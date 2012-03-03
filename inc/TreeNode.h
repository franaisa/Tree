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


template <class DataType>
class TreeNode {
   public:
      TreeNode();
      TreeNode(const DataType& data);
      TreeNode(const DataType& data, TreeNode<DataType>* parent);
      // Careful!!! It copies the references
      TreeNode(const TreeNode<DataType>& source);

      virtual ~TreeNode();

      // WE NEED TO RETURN AN ITERATOR
      TreeNode<DataType>& operator=(const TreeNode<DataType>& rhs);
      TreeNode<DataType>& operator=(const DataType& rightData);

      friend std::ostream& operator<< <DataType>(std::ostream& out, const TreeNode<DataType>& node);

      inline TreeNode<DataType>* const parent() const;
      inline int nChildren();
   private:
      DataType _data;
      TreeNode<DataType>* _parent;
      typename std::list< TreeNode<DataType>* >::iterator _childIt; 
      std::list< TreeNode<DataType>* > _children;

      friend class Tree<DataType>;
      friend class TreeIterator<DataType>;

      void clone(const TreeNode<DataType>& source);
};


// *****************************************************************************
//                               IMPLEMENTATION
// *****************************************************************************


template <class DataType>
TreeNode<DataType>::TreeNode() : _parent(NULL) {
   // Nothing to do
}

//______________________________________________________________________________

// Once created, the iterator has to be modified manually
template <class DataType>
TreeNode<DataType>::TreeNode(const DataType& data) : _data(data), _parent(NULL) {
   // Nothing to do
}

//______________________________________________________________________________

// Once created, the iterator has to be modified manually
template <class DataType>
TreeNode<DataType>::TreeNode(const DataType& data, TreeNode<DataType>* parent) : _data(data), _parent(parent) {
   // Nothing to do
}

//______________________________________________________________________________

// COMPLETE COPY OF A TREE NODE, POINTERS ARE COPIED!! BE CAREFUL USING IT
template <class DataType>
TreeNode<DataType>::TreeNode(const TreeNode<DataType>& source) :
   _data(source._data),
   _parent(source._parent),
   _childIt(source._childIt),
   _children(source._children)
{
   // Nothing to do
}

//______________________________________________________________________________

template <class DataType>
TreeNode<DataType>::~TreeNode() {
   // Nothing to do
   // The destructors of the objects contained are called here automatically
}

//______________________________________________________________________________

template <class DataType>
TreeNode<DataType>& TreeNode<DataType>::operator=(const TreeNode<DataType>& rhs) {
   if(this != &rhs)
      clone(rhs);

   return *this;
}

//______________________________________________________________________________

template <class DataType>
TreeNode<DataType>& TreeNode<DataType>::operator=(const DataType& rightData) {
   _data = rightData;

   return *this;
}

//______________________________________________________________________________

template <class DataType>
std::ostream& operator<<(std::ostream& out, const TreeNode<DataType>& node) {
   out << node._data;

   return out;
}

//______________________________________________________________________________

template <class DataType>
TreeNode<DataType>* const TreeNode<DataType>::parent() const {
   return _parent;
}

//______________________________________________________________________________

template <class DataType>
int TreeNode<DataType>::nChildren() {
   return _children.size();
}

//______________________________________________________________________________

// COMPLETE COPY OF A TREE NODE, POINTERS ARE COPIED!! BE CAREFUL USING IT
template <class DataType>
void TreeNode<DataType>::clone(const TreeNode<DataType>& source) {
   _data = source._data;
   _parent = source._parent;
   _childIt = source._childIt;
   _children = source._children;
}

#endif
