/**
* \author Jack Owen Shelton
* Framework used in both my CS 3520 and CS 4322 projects.
* \date Spring 2009
*/

#ifndef UPDATEORIGINATOR_H_INCLUDED
#define UPDATEORIGINATOR_H_INCLUDED

#include <list>
#include "dll.h"

class UpdateListener;

/** Special class that acts as a logic base, allowing for objects to be updated multiple times in a single frame.
* This is especially useful in RenderTexture's where the developer might want to hide or display certain objects only in the RenderTexture.
*/
class EXPORT_FRAME UpdateOriginator
{
protected:
    ///List of UpdateListeners listening for the UpdateOriginator's update.
    std::list<UpdateListener*> updateListeners;

public:
    ///Required virtual deconstructor.
    virtual ~UpdateOriginator(){}

    /** Register a new UpdateListener to listen to the UpdateOriginator.
    * \param listener The UpdateListener to add.
    * \remark If listener has already been registered nothing will happen.
    */
    virtual void registerUpdateListener(UpdateListener* listener);
    /** Remove an UpdateListener from the UpdateOriginator's registry.
    * \param listener The UpdateListener to remove.
    */
    virtual void removeUpdateListener(UpdateListener* listener);

    /** Remove all UpdateListeners registered to the UpdateOriginator.
    * \remark This method should typically be called in the deconstructor of any subclasses of UpdateOriginator.
    */
    inline void removeAllUpdateListeners()
    {
        while (updateListeners.size() > 0)
            removeUpdateListener(updateListeners.front());
    }

    ///Update method, this is abstract since Update Originators require context.
    virtual void update() = 0;
};

#endif // UPDATEORIGINATOR_H_INCLUDED
