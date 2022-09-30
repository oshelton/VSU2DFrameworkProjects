/**
* \author Jack Owen Shelton
* Framework used in both my CS 3520 and CS 4322 projects.
* \date Spring 2009
*/

#ifndef UPDATELISTENER_H_INCLUDED
#define UPDATELISTENER_H_INCLUDED

#include <list>
#include "dll.h"

class UpdateOriginator;
class RenderTexture;

/**Special class that is notified whenever an UpdateOriginator processes a frame.
* \sa UpdateOriginator
*/
class EXPORT_FRAME UpdateListener
{
private:
    ///List of UpdateOriginators the UpdateListener is listening to.
    std::list<UpdateOriginator*> listeningTo;

public:
    ///Required virtual deconstructor.
    virtual ~UpdateListener(){}

    /** Notify the UpdateListener that it has been added to an UpdateOriginator.
    * \param origin UpdateOriginator the UpdateListener has been added to.
    * \remark This is an internal method and should not be called manually.
    */
    inline void notifyAddedToOriginator(UpdateOriginator* origin)
    {
        listeningTo.push_back(origin);
    }

    /** Notify theUpdateListener that it has been removd from an UpdateOriginator.
    * \param origin The UpdateOriginator that the UpdateListener is nolonger listening to.
    * \remark This is an internal method and should not be called manually.
    */
    inline void notifyRemovedFromOriginator(UpdateOriginator* origin)
    {
        listeningTo.remove(origin);
    }

    ///Get the number of UpdateOriginators the UpdateListener is listening to.
    inline unsigned int getNumberOriginators()
    {
        return listeningTo.size();
    }

    /** Remove the UpdateListener from all UpdateOriginators it is listening to.
    * \remark This method should typically be called in the deconstructor of any classes that inherit from UpdateListener.
    */
    void removeFromUpdateOriginators();

    ///Update method, logic should go here.
    virtual void update() = 0;
    /** Special update method, logic should go here.
    * \param tex The RenderTexture that started the update.
    */
    virtual void update(RenderTexture* tex) {update(tex);}
};

#endif // UPDATELISTENER_H_INCLUDED
