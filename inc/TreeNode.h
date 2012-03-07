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
// *****************************************************************************
// *****************************************************************************
//                                   HEADER
// *****************************************************************************
// *****************************************************************************
// *****************************************************************************


/**
 * This class represents a node that belongs to a tree.
 *
 * Each node contains the data stored in it and pointers to its children and
 * parent.
 *
 * The copy constructor and the operator= haven't been implemented because when
 * a TreeNode is copied, the memory allocation needed to copy the references
 * is handled by the tree (to which the node belongs to).
 * 
 * @author Francisco Aisa García
 * @version 0.1
 * @since 27/01/2012
 */
template <class T>
class TreeNode {
   public:
      // =======================================================================
      //                     CONSTRUCTORS AND DESTRUCTORS
      // =======================================================================


      /** Default constructor. */
      inline TreeNode();

      //________________________________________________________________________

      /**
       * Custom constructor.
       * @param data Data to initialize the data content of the node.
       */
      inline TreeNode(const T& data);

      //________________________________________________________________________

      /**
       * Custom constructor.
       * @param data Data to initialize the data content of the node.
       * @param parent Parent node of the node to be constructed.
       */
      inline TreeNode(const T& data, TreeNode<T>* parent);

      //________________________________________________________________________

      /** Destructor. */
      inline ~TreeNode();


      // =======================================================================
      //                               OPERATORS
      // =======================================================================


      /**
       * Ostream operator.
       * @param out Ostream stream.
       * @param node *This.
       */
      friend std::ostream& operator<< <T>(std::ostream& out, const TreeNode<T>& node);


      // =======================================================================
      //                            ELEMENT ACCESS
      // =======================================================================


      /**
       * Get the parent node of this node.
       * @return A pointer to the parent node.
       */
      inline TreeNode<T>* const parent() const;


      // =======================================================================
      //                               CAPACITY
      // =======================================================================


      /**
       * Get how many children this node has.
       * @return An integer indicating how many children the current node has.
       */
      inline unsigned int nChildren() const;

   private:
      // =======================================================================
      //                            FRIEND CLASSES
      // =======================================================================


      friend class Tree<T>;


      // =======================================================================
      //                            PRIVATE FIELDS
      // =======================================================================


      /** Data to be stored in the node. */
      T _data;

      //________________________________________________________________________

      /** Pointer to parent node. */
      TreeNode<T>* _parent;

      //________________________________________________________________________

      /**
       * Iterator to  parent children list.
       *
       * It is mainly used to accelarate operations like erase() or chop() where
       * a node is erased (and has to be eliminated from the parent list in a fast
       * manner).
       *
       * This field is not set by the TreeNode class, instead, it is handled by
       * the Tree class (to which this node belongs to).
       */
      typename std::list< TreeNode<T>* >::iterator _childIt;

      //________________________________________________________________________

      /** List of pointers to children nodes.  */
      std::list< TreeNode<T>* > _children;
};


// *****************************************************************************
// *****************************************************************************
// *****************************************************************************
//                               IMPLEMENTATION
// *****************************************************************************
// *****************************************************************************
// *****************************************************************************


template <class T>
TreeNode<T>::TreeNode() : _parent(NULL) {
   // Nothing to do
}

//______________________________________________________________________________

template <class T>
TreeNode<T>::TreeNode(const T& data) : _data(data), _parent(NULL) {
   // Nothing to do
}

//______________________________________________________________________________

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
unsigned int TreeNode<T>::nChildren() const {
   return _children.size();
}

#endif
