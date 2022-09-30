/**
* \author Jack Owen Shelton
* Framework used in both my CS 3520 and CS 4322 projects.
* \date Spring 2009
*/

#ifndef BINDABLE_H_INCLUDED
#define BINDABLE_H_INCLUDED

#include "dll.h"

/** Basic reference counted object class, intended for use with AngelScript.
* Classes that need to be created and destroyed in AngelScript but treated as reference objects should inherit from this class.
*/
class EXPORT_FRAME Bindable
{
protected:
	///Number of references in use.
    unsigned int refCount;
public:
	///Required virtual destructor.
    virtual ~Bindable(){}

	///Special m,ethod called when a new reference has been created that points to this object.
    void addRef()
    {
        ++refCount;
    }

	///Special m,ethod called when a reference pointing to this object goes out of scope.
    void release()
    {
        if (--refCount == 0)
            delete this;
    }
};

#endif // BINDABLE_H_INCLUDED
