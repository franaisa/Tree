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

#ifndef __PREORDER_ITERATOR_H__
#define __PREORDER_ITERATOR_H__

#include "TreeNode.h"
#include "Tree.h"
#include <iterator>
/*
template <class DataType>
class Tree::PreOrderIterator : public std::iterator<std::input_iterator_tag, DataType> {
   public:
      PreOrderIterator();
      PreOrderIterator(const PreOrderIterator& other);

      PreOrderIterator& operator++();
      PreOrderIterator operator++(int notUsed);

      bool operator==(const PreOrderIterator& rhs);
      bool operator!=(const PreOrderIterator& rhs);

      int& operator*();
   private:
      TreeNode<DataType>* pointer;
};
*/
#endif