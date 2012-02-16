#ifndef _TREE_H_
#define _TREE_H_

#include "TreeNode.h"
#include "TreeIterator.h"
#include <iterator>
#include <new>
#include <stack>

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
      class InOrderIterator;

      Tree();
      Tree(const DataType& data);
      Tree(const Tree<DataType>& source);

      virtual ~Tree();

      Tree<DataType>& operator=(const Tree<DataType>& rhs);

      void setRoot(const DataType& data);

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
      // graft

      void prePrint() {
         PreOrderIterator it;
         for(it = preBegin(); it != preEnd(); ++it) {
            std::cout << *it << " ";
         }
         std::cout << std::endl;
      }

      void postPrint() {
         PostOrderIterator it;
         for(it = postBegin(); it != postEnd(); ++it) {
            std::cout << *it << " ";
         }
         std::cout << std::endl;
      }

   protected:
      // Nothing yet
   private:
      TreeNode<DataType>* _root;
      unsigned int _nNodes;
      unsigned int _levels;

      void clone(const Tree<DataType>& source);
};


// *****************************************************************************
//                              TREE IMPLEMENTATION
// *****************************************************************************


template <class DataType>
Tree<DataType>::Tree() : _root(NULL), _nNodes(0), _levels(0) {
   // Nothing to do
}

//______________________________________________________________________________

// DEPRECATED
template <class DataType>
Tree<DataType>::Tree(const DataType& data) : _nNodes(1), _levels(1) {
   _root = new(std::nothrow) TreeNode<DataType>(data);

   if(_root == NULL) {
      std::cerr << "Error: Failure to allocate memory" << std::endl;
   }
}

//______________________________________________________________________________

// DEPRECATED <- To be implemented as a copy-on-write
template <class DataType>
Tree<DataType>::Tree(const Tree<DataType>& source) : _nNodes(source._nNodes), _levels(source._levels) {
   // Recorrer el arbol cogiendo aquellos nodos que tienen descendientes y crear
   // memoria para el nodo y sus descendientes. Copiando los valores de cada uno
   // luego desplazarnos al siguiente descenciente que tenga descendientes y
   // repetir el proceso
   // Implementar esta funcion como clone y usarla en el operator= tambien
}

//______________________________________________________________________________

// DEPRECATED
template <class DataType>
Tree<DataType>::~Tree() {
   // Use post-order iterator to erase each node
   if(_root != NULL) {
      PostOrderIterator postIt;
      for(postIt = postBegin(); postIt != postEnd(); ++postIt) {
         delete postIt.getPointer();
      }
   }
}

//______________________________________________________________________________

// DEPRECATED
template <class DataType>
Tree<DataType>& Tree<DataType>::operator=(const Tree<DataType>& rhs) {
   // TO BE IMPLEMENTED
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

// DEPRECATED
template <class DataType>
void Tree<DataType>::clone(const Tree<DataType>& source) {

}

// *****************************************************************************
//                            PRE-ORDER ITERATOR HEADER
// *****************************************************************************


template <class DataType>
class Tree<DataType>::PreOrderIterator : public TreeIterator<DataType> {
   public:
      PreOrderIterator();
      PreOrderIterator(TreeNode<DataType>* data);
      PreOrderIterator(const PreOrderIterator& source);

      virtual ~PreOrderIterator();

      PreOrderIterator& operator=(const PreOrderIterator& rhs);

      virtual PreOrderIterator& operator++();
      virtual void parent(TreeIterator<DataType>& iterator);
      virtual void children(int child, TreeIterator<DataType>& iterator);
   private:
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
typename Tree<DataType>::PreOrderIterator& Tree<DataType>::PreOrderIterator::operator=(const PreOrderIterator& rhs) {
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
void Tree<DataType>::PreOrderIterator::parent(TreeIterator<DataType>& iterator) {
   iterator = Tree<DataType>::PreOrderIterator(TreeIterator<DataType>::_pointer->parent());
}

//______________________________________________________________________________

template <class DataType>
void Tree<DataType>::PreOrderIterator::children(int child, TreeIterator<DataType>& iterator) {
   if(TreeIterator<DataType>::_pointer->_children.size() > 0)
      iterator = Tree<DataType>::PreOrderIterator(TreeIterator<DataType>::_pointer->children(child));
   else {
      iterator = Tree<DataType>::PreOrderIterator(NULL);
   }
}

// *****************************************************************************
//                            IN-ORDER ITERATOR HEADER 
// *****************************************************************************


// It behaves differently for binary trees
template <class DataType>
class Tree<DataType>::InOrderIterator : public std::iterator<std::forward_iterator_tag, DataType> {
   public:
      InOrderIterator() {};
      InOrderIterator(const InOrderIterator& other);

      InOrderIterator& operator++();
      InOrderIterator operator++(int notUsed);

      bool operator==(const InOrderIterator& rhs);
      bool operator!=(const InOrderIterator& rhs);

      int& operator*();
   private:
      TreeNode<DataType>* pointer;
};


// *****************************************************************************
//                           POST-ORDER ITERATOR HEADER
// *****************************************************************************


template <class DataType>
class Tree<DataType>::PostOrderIterator : public TreeIterator<DataType> {
   public:
      PostOrderIterator();
      PostOrderIterator(TreeNode<DataType>* data);
      PostOrderIterator(const PostOrderIterator& other);

      virtual ~PostOrderIterator();

      PostOrderIterator& operator=(const PostOrderIterator& rhs);

      virtual PostOrderIterator& operator++();

      virtual void parent(TreeIterator<DataType>& iterator);
      virtual void children(int child, TreeIterator<DataType>& iterator);

      void printStack();

   private:
      std::stack< std::pair<TreeNode<DataType>*, int> > _pathStack;
};

// *****************************************************************************
//                       POST-ORDER ITERATOR IMPLEMENTATION
// *****************************************************************************

// Parent sets _pointer to NULL
template <class DataType>
Tree<DataType>::PostOrderIterator::PostOrderIterator() {
   // Nothing to do
}

//______________________________________________________________________________

template <class DataType>
Tree<DataType>::PostOrderIterator::PostOrderIterator(TreeNode<DataType>* data) : TreeIterator<DataType>(data) {
   _pathStack.push(std::pair<TreeNode<DataType>*, int>(TreeIterator<DataType>::getPointer(), 0));
}

//______________________________________________________________________________

template <class DataType>
Tree<DataType>::PostOrderIterator::PostOrderIterator(const PostOrderIterator& source) : TreeIterator<DataType>(source), _pathStack(source._pathStack) {
   // Nothing to do
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

      // Clear the stack
      while(!_pathStack.empty()) {
         _pathStack.pop();
      }

      // Put the first element to be printed at the top of the stack
      _pathStack.push(std::pair<TreeNode<DataType>*, int>(TreeIterator<DataType>::getPointer(), 0));
      operator++();
   }

   return *this;
}

//______________________________________________________________________________

template <class DataType>
typename Tree<DataType>::PostOrderIterator& Tree<DataType>::PostOrderIterator::operator++() {
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
void Tree<DataType>::PostOrderIterator::parent(TreeIterator<DataType>& iterator) {
   iterator = Tree<DataType>::PostOrderIterator(TreeIterator<DataType>::_pointer->parent());
}

//______________________________________________________________________________

template <class DataType>
void Tree<DataType>::PostOrderIterator::children(int child, TreeIterator<DataType>& iterator) {
   if(TreeIterator<DataType>::_pointer->_children.size() > 0)
      iterator = Tree<DataType>::PostOrderIterator(TreeIterator<DataType>::_pointer->children(child));
   else {
      iterator = Tree<DataType>::PostOrderIterator(NULL);
   }
}

// *****************************************************************************
//                            TREE-ITERATOR HEADER
// *****************************************************************************

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
      // Careful when using it, the pointer returned MUST NOT be modified
      inline TreeNode<DataType>* getPointer();
      inline void setPointer(TreeNode<DataType>* newPointer);

      virtual void parent(TreeIterator<DataType>& iterator) = 0;
      virtual void children(int child, TreeIterator<DataType>& iterator) = 0;
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

#endif