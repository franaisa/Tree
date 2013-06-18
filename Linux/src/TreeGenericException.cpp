#include "TreeGenericException.h"

TreeGenericException::TreeGenericException(const std::string& what_arg) :
   std::logic_error(what_arg)
{
   // Nothing to do
}