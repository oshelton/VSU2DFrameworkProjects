/**
* \author Jack Owen Shelton
* Framework used in both my CS 3520 and CS 4322 projects.
* \date Spring 2009
*/

#ifndef COMPOUNDRENDERABLE_H_INCLUDED
#define COMPOUNDRENDERABLE_H_INCLUDED

#include <list>
#include <string>
#include "Renderable.h"

/** Special Renderable class that compensates for the ability of SceneNodes to only have one Component.
* This is a conveniance class.
* This class fills the role of decorator.
*/
class EXPORT_FRAME CompoundRenderable : public Renderable
{
private:
    ///map of Renderables that are attached to the CompoundDrawable.
    std::list<Renderable*> renderables;

public:
    /** Constructor.
    * \param the name of the CompundRenderable to create.
    */
    CompoundRenderable(const std::string& name);
    /** Deconstructor.
    * \remark This will not destroy any attached Renderables, but the will be notified of their removal.
    */
    ~CompoundRenderable();

    ///Get the type of the Component.
    const std::string getType()
    {
        return "CompoundRenderable";
    }

    /** Overriden from Component.
    * Needed to be overriden in order for the CompoundRenderable to be able to register the attached Renderables.
    * \param node The SceneNode to be registered.
    * \sa Component::registerUser(SceneNode* node)
    */
    void registerUser(SceneNode* node);
    /** Removes the Component from all of the SceneNodes that use it.
    * Needed to be overriden in order for the CompoundRenderable to be able to call the method on all attached Renderables.
    * \sa Component::removeAllUsers()
    */
    void removeAllUsers();
    /** Notify the CompoundRenderable that it has been removed from a SceneNode.
    * This method has been overriden in order for the CompoundRenderable to be able to notify its attached Renderables.
    * \param node The SceneNode that the CompoundRenderable has been removed from.
    * \sa Component::notifyRemoved(SceneNode* node)
    */
    void notifyRemoved(SceneNode* node);

    /** Add a new Renderable to the CompoundRenderable.
    * \param render the Renderable to add.
    */
    void addRenderable(Renderable* render);
    /** Remove a Renderable attached to the CompoundRenderable.
    * \param name The name of the Renderable to remove.
    */
    Renderable* removeRenderable(const std::string& name);
    ///Get a const reference to the list containing all the attached Renderables.
    const std::list<Renderable*>& getAttachedRenderables();

    ///Doesn't do anything for this class.
    const double getWidth(){ return 0; }
    ///Doesn't do anything for this class.
    const double getHeight(){ return 0; }

    /** Core render method.
    * The other render methods call this method once it has been determined that the object should be rendered.
    * This is the Template method, and doesn't do anything in this class.
    * \param node The node whose position, rotation, and scale are going to be used to render the object.
    * \param screenPosition The position to render the object at transformed into screen space.
    */
    void render(SceneNode* const node, const hgeVector& screenPosition, Camera* const cam){}
};

#endif // COMPOUNDRENDERABLE_H_INCLUDED
