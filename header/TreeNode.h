#ifndef __TREE_NODE_H__
#define __TREE_NODE_H__

#include <iostream>
#include <vector>


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
      // Create a new node with a certain number of children
      TreeNode(const DataType& data, int nChildren);
      // Create a new node with the right data and children references and parent reference
      TreeNode(const DataType& data, TreeNode<DataType>* parent, const std::vector< TreeNode<DataType>* >& children);
      // Careful!!! It copies the references
      TreeNode(const TreeNode<DataType>& source);

      virtual ~TreeNode();

      // WE NEED TO RETURN AN ITERATOR
      TreeNode<DataType>& operator=(const TreeNode<DataType>& rhs);
      TreeNode<DataType>& operator=(const DataType& rightData);

      friend std::ostream& operator<< <DataType>(std::ostream &out, const TreeNode<DataType>& node);

      inline TreeNode<DataType>* const parent() const;
      inline TreeNode<DataType>* const children(int nChild) const;
      inline int nChildren();
   private:
      DataType _data;
      TreeNode<DataType>* _parent;
      std::vector< TreeNode<DataType>* > _children;

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

template <class DataType>
TreeNode<DataType>::TreeNode(const DataType& data) : _data(data), _parent(NULL) {
   // Nothing to do
}

template <class DataType>
TreeNode<DataType>::TreeNode(const DataType& data, TreeNode<DataType>* parent) : _data(data), _parent(parent) {
   // Nothing to do
}

//______________________________________________________________________________

template <class DataType>
TreeNode<DataType>::TreeNode(const DataType& data, int nChildren) :
   _data(data),
   _parent(NULL),
   _children(nChildren)
{
   // Nothing to do
}

//______________________________________________________________________________

// Create a new node with the right data and children references and parent reference
template <class DataType>
TreeNode<DataType>::TreeNode(const DataType& data, TreeNode<DataType>* parent,
                             const std::vector< TreeNode<DataType>* >& children) :

   _data(data),
   _parent(parent),
   _children(children)
{
   // Nothing to do
}

//______________________________________________________________________________

// COMPLETE COPY OF A TREE NODE, POINTERS ARE COPIED!! BE CAREFUL USING IT
template <class DataType>
TreeNode<DataType>::TreeNode(const TreeNode<DataType>& source) :
   _data(source._data),
   _parent(source._parent),
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
std::ostream& operator<<(std::ostream &out, const TreeNode<DataType>& node) {
   /*out << "Data: " << node._data << std::endl;
   out << "Parent: " << node._parent << std::endl;

   int nChildren = node._children.size();
   if (nChildren == 0)
      out << "No children" << std::endl;
   else {
      out << "Children[0]: " << node._children[0];
      for(int i = 1; i < nChildren; ++i) {
         out << std::endl << "Children[" << i << "]: " << node._children[i];
      }
   }*/

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
TreeNode<DataType>* const TreeNode<DataType>::children(int nChild) const {
   return _children[nChild];
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
   _children = source._children;
}

#endif
