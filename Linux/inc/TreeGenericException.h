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

#ifndef __TREE_GENERIC_EXCEPTION_H__
#define __TREE_GENERIC_EXCEPTION_H__

#include <stdexcept>

/**
 * This class represents any exception related with a Tree structure.
 *
 * Every exception thrown out of a tree class inherits from this class.
 *
 * @author Francisco Aisa García
 * @version 0.1
 */
class TreeGenericException : public std::logic_error {
   public:

      /**
       * Custom constructor.
       *
       * @param what_arg Description of the problem that is causing the exception.
       */
      explicit TreeGenericException(const std::string& what_arg);
};

#endif