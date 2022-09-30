/**
* \author Jack Owen Shelton
* Framework used in both my CS 3520 and CS 4322 projects.
* \date Spring 2009
*/

#ifndef BINDABLEMANAGED_H_INCLUDED
#define BINDABLEMANAGED_H_INCLUDED

#include "dll.h"

/** Basic reference counted object class placeholder, intended for use with AngelScript.
* Classes that need to be accessed from AngelScript but should not be created or destroyed by scripts should inherit from this class.
*/
class EXPORT_FRAME BindableManaged
{
public:
	///Required virtual destructor.
    virtual ~BindableManaged(){}

	///Dummy add reference method.
    void addRef(){}
	///Dummy release reference method.
    void release(){}
};

#endif // BINDABLEMANAGED_H_INCLUDED
