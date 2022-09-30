/**
* \author Jack Owen Shelton
* Framework used in both my CS 3520 and CS 4322 projects.
* \date Spring 2009
*/

#ifndef ENTITY_H_INCLUDED
#define ENTITY_H_INCLUDED

#include <string>
#include <map>
#include <hgevector.h>
#include <hgecolor.h>
#include "dll.h"
#include "BindableManaged.h"

class SceneManager;
class Component;
class SimpleRenderable;
class Utils;

///Special values for which transformation space translations should be applied to.
enum TransformSpace
{
    TS_LOCAL,
    TS_PARENT,
    TS_GLOBAL
};

class SceneNode;

/**Simple class for iterating over the children of a SceneNode, serves as a simple iterator.
* \remark Using the SceneNode removeChildSceneNode and destroyChildSceneNode methods can invalidate instances of this class if the removed or destroyed SceneNode happens to be the one the SceneNodeIterator currently points to.
*/
class SceneNodeIterator
{
private:
    ///SceneNode whose children are being iterated over.
    SceneNode* parent;
    ///Pointer to the map containing the actual child SceneNodes.
    std::map<std::string, SceneNode*>* children;
    ///Map iterator used to keep track of where the SceneNodeIterator is in the map.
    std::map<std::string, SceneNode*>::iterator iter;

public:
    /** Constructor.
    * \param parent The SceneNode whose children are being iterated over.
    * \param childNodes Pointer to the map that actually stores the child nodes.
    */
    SceneNodeIterator(SceneNode* parent, std::map<std::string, SceneNode*>* childNodes);

    ///Get whether or not this SceneNodeIterator has any more elements.
    const bool hasNext();

    ///Advance the SceneNodeIterator to the next element and return it.
    SceneNode* next();
    ///Move the SceneNodeIterator to the previous element and return it, or the first element if it can't rewind any further.
    SceneNode* previous();
    ///Get the current element the SceneNodeIterator points to.
    SceneNode* current();

    ///Remove the current element from the SceneNode.
    void remove();
    ///Destroy the current element.
    void destroy();
};

/** Scene node class.
* This class represents an object in the scene graph and is used to keep track of position, rotation, and scale of 2d objects.
* \remark Instances of SceneNode should only be created through the SceneManager.
*/
class EXPORT_FRAME SceneNode : public BindableManaged
{
private:
    ///Parent of this SceneNode, should never be NULL.
    SceneNode* parent;
    ///Map of children SceneNodes.
    std::map<std::string, SceneNode*> children;
    ///The Component that is attached to this SceneNode.
    Component* component;

    ///Determines whether or not the SceneNode inherits its rotation from its parent.
    bool InheritRotation;
    ///Determines whether or not the SceneNode inherits its scale from its parent.
    bool inheritScale;
    ///Used to determine if the SceneNode is visible.
    bool visible;

    ///Position of the SceneNode in local space.
    hgeVector  position;
    /**Z coordinate of the SceneNode, used for determining what is rendered above or below (much more flexible than using layers).
    * 0 is closest to the screen and is reserved for CEGUI, 1 is furthest from the screen.
    */
    double z;

    ///Scale of the SceneNode.
    double scale;
    ///Heading of the SceneNode inlocal space.
    double rotation;
    ///Name of the SceneNode.
    std::string name;

public:
    /** Constructor.
    * \param name Name of the SceneNode being constructed.
    */
    SceneNode(const std::string& name);
    ///Deconstructor.
    ~SceneNode();

    /** Set the parent of the SceneNode
    * \param entity SceneNode the SceneNode was added to.
    * \remark This method is used internaly, assigning a SceneNode to another SceneNode should be done through the attachChildSceneNode method.
    */
    void setParent(SceneNode* entity);
    ///Retrieve the parent of the SceneNode.
    SceneNode* getParent();

    /** Create a new SceneNode and automatically attach it to the SceneNode.
    * Wraps SceneNode::createSceneNode
    * \param name The name of the SceneNode to be created.
    * \sa SceneManager::createSceneNode(std::string name)
    */
    SceneNode* createChildSceneNode(const std::string& name);
    /** Attach a SceneNode to the SceneNode as its child.
    * \param name The name of the SceneNode to attach.
    * \return The SceneNode that was attached or NULL if no SceneNode exist named name.
    */
    SceneNode* attachChildSceneNode(const std::string& name);
    /** Attach a SceneNode to the SceneNode as its child.
    * \param entity The SceneNode to attach.
    */
    void attachChildSceneNode(SceneNode* entity);

    /** Remove a child SceneNode from the SceneNode
    * \param name The name of the SceneNode to remove.
    * \return The SceneNode that was removed or NULL if no SceneNode named name is a direct child of the SceneNode.
    */
    SceneNode* removeChildSceneNode(const std::string& name);
    /** Remove a child SceneNode from the SceneNode
    * \param entity The SceneNode to remove.
    * \remark If entity is not a direct child of the SceneNode, the method will be ignored.
    */
    void removeChildSceneNode(SceneNode* entity);
    /** Remove a child SceneNode from the children map.
    * \param entity The SceneNode to remove.
    * \remark This is an internal method and should not be called manually.
    */
    void removeChildSceneNodeFromMap(SceneNode* entity);

    ///Destroy te SceneNode and all of its children.
    void destroy();
    /** Destroy a specific child SceneNode of the SceneNode
    * \param name The name of the child SceneNode to destroy.
    * \remark If there is no direct child of the SceneNode named name this method will not do anything.
    */
    void destroyChildSceneNode(const std::string& name);
    /** Destroy a specific child SceneNode of the SceneNode
    * \param entity The child SceneNode to destroy.
    * \remark If entity is not a direct child of the SceneNode this method will not do anything.
    */
    void destroyChildSceneNode(SceneNode* entity);
    ///This method destroys all the SceneNode's child SceneNodes.
    void destroyAllChildren();

    ///Get a SceneNodeIterator for this SceneNode.
    SceneNodeIterator getChildNodeIterator();

    /** Attach a Component to the SceneNode
    * This is technically a swap operation sinc SceneNodes can only have one Component at a time.
    * \param component The Component to attach, this removes the old Component.
    */
    void attachComponent(Component* component);
    /** Attach a Component to the SceneNode
    * This is technically a swap operation sinc SceneNodes can only have one Component at a time.
    * \param name The name of the Component to attach, this removes the old Component.
    */
    void attachComponent(const std::string& name);
    ///Retrieve the Component attached to the SceneNode.
    Component* getComponent();
    /** Remove the Component attached to the SceneNode.
    * \return The Component that was attached or NULL if one is not attached to the SceneNode.
    */
    Component* removeComponent();

    /** Set the position of the SceneNode.
    * \param position The new position of the SceneNode in parent relative space.
    */
    void setPosition(const hgeVector& position);
    ///Get the position of the SceneNode in parent relative space.
    const hgeVector getPosition();
    ///Get the position of the SceneNode in world space.
    const hgeVector getWorldPosition();

    /** Move the SceneNode.
    * \param translateVec The vector to translate the SceneNode with.
    * \param translateSpace The space in transform space in which to move the SceneNode
    * \sa TransformSpace
    */
    void translate(const hgeVector translateVec, const TransformSpace& translateSpace = TS_LOCAL);

    /** Set the scale of the SceneNode in local space.
    * \param scale Scale of the SceneNode.
    */
    void setScale(const double& scale);
    ///Get the scale of the SceneNode in local space.
    double getScale();
    ///Get the scale of the SceneNode while taking into account the scale of its parent.
    double getWorldScale();

    /** Rotate the SceneNode.
    * \param angle The angle by which to rotate the SceneNode, it should be passed in degrees.
    */
    void rotate(const double& angle);
    /** Set the heading of the SceneNode.
    * heading The angle of rotation the SceneNode should be set to use, in degrees.
    */
    void setRotation(const double heading);
    ///Get the heading of the SceneNode in local space.
    double getRotation();
    ///Get the heading of the SceneNode taking into account the heading of the SceneNode's parent.
    double getWorldRotation();

    /** Set the z coordinate of the SceneNode.
    * \param z The new z coordinate of the SceneNode, should be between 0.0 and 1.0.
    */
    void setZ(const double& z);
    ///Return the z coordinate of the SceneNode.
    double getZ();

    /** Set whether or not theSceneNode inherits its parent's scale, defaults to true.
    * \param inherit True if the SceneNode should inherit its parent's scale.
    */
    void setInheritScale(const bool& inherit);
    ///Get whether or not the SceneNode inherits thescale of its parent.
    bool doesInheritScale();

    /** Set whether or not the SceneNode inherits the heading of its parent.
    * \param inherit True if the SceneNode should inherit the heading of its parent.
    */
    void setInheritRotation(const bool& inherit);
    ///Get whether or not the SceneNode should inherit its parent's heading.
    bool doesInheritRotation();

    /** Set a SceneNodes visibility.
    * \param visible If false and the Component attached to the SceneNode is a Rederable, the Renderable will skip the SceneNode when it processes its render notifications.
    */
    void setVisible(const bool& visible);
    ///Get whther the SceneNode is visible ot not.
    bool isVisible();

    /** Set the name of the SceneNode
    * \param name New name of the SceneNode
    * \remark Wraps SceneManager::renameSceneNode
    */
    void setName(const std::string& name);
    /** Set the SceneNodes name internally.
    * \param name The new name of theSceenNode.
    * \remark This is an internal method and should not be called manually.
    * \sa SceneManager::renameSceneNode(std::string oldName, std::string newName)
    */
    void setNameNoRemap(const std::string& name);
    ///Get the name of the SceneNode.
    const std::string& getName();
};

#endif // ENTITY_H_INCLUDED
