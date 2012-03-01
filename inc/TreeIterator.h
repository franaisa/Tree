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

#ifndef __TREE_ITERATOR_H__
#define __TREE_ITERATOR_H__

#include "TreeNode.h"

/*template <class T>
class TreeNode;

template <class DataType>
class TreeIterator {
   public:
      TreeIterator();
      TreeIterator(TreeNode<DataType>* data);
      TreeIterator(const TreeIterator<DataType>& other);

      virtual ~TreeIterator();

      TreeIterator<DataType>& operator=(const TreeIterator<DataType>& rhs);

      // Abstract
      virtual TreeIterator<DataType>& operator++() = 0;
      TreeIterator<DataType> operator++(int notUsed);

      inline bool operator==(const TreeIterator<DataType>& rhs) const;
      inline bool operator!=(const TreeIterator<DataType>& rhs) const;

      inline DataType* operator->() const;
      inline DataType& operator*() const;

      inline TreeIterator<DataType> parent();
      inline TreeIterator<DataType> children(int child);
   private:
      friend class TreeNode<DataType>;

      TreeNode<DataType>* _pointer;

      inline void clone(const TreeIterator<DataType>& rhs);
};


// *****************************************************************************
//                       PRE-ORDER ITERATOR IMPLEMENTATION
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

// DEPRECATED <- THROW EXCEPTION IF NO PARENT
template <class DataType>
TreeIterator<DataType> TreeIterator<DataType>::parent() {
   return TreeIterator<DataType>(_pointer->_parent);
}

//______________________________________________________________________________

// DEPRECATED <- THROW EXCEPTION IF NO CHILDREN
template <class DataType>
TreeIterator<DataType> TreeIterator<DataType>::children(int child) {
   if(_pointer->children.size() > 0)
      return TreeIterator<DataType>(_pointer->children[child]);

   return NULL;
}

//______________________________________________________________________________

template <class DataType>
void TreeIterator<DataType>::clone(const TreeIterator<DataType>& rhs) {
   _pointer = rhs._pointer;
}
*/
#endif