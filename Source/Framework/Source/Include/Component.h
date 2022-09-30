/**
* \author Jack Owen Shelton
* Framework used in both my CS 3520 and CS 4322 projects.
* \date Spring 2009
*/

#ifndef COMPONENT_H_INCLUDED
#define COMPONENT_H_INCLUDED

#include <string>
#include <list>
#include "dll.h"
#include "BindableManaged.h"

class SceneNode;

/** Base component class.
* Components are special objects that can be attached to SceneNodes.
* Components are created by the SceneManager through ComponentCreators and should never be created manually.
*/
class EXPORT_FRAME Component : public BindableManaged
{
protected:
	///Name of the component.
    std::string name;
	///List of SceneNodes that the Component is attached to.
    std::list<SceneNode*> users;

public:
	///Required virtual destructor.
    virtual ~Component(){}

	///Get the name of the Component.
    const std::string& getName(){return name;}
	/**Set the name of the component.
	* Wraps SceneManager->renameComponent.
	*/
    virtual void setName(const std::string& name);
	/** Changes the name of the Component without changing anything else.
	* This is an internal method and should not be called manually.
	*/
    inline void setNameNoRemap(const std::string& name)
    {
        this->name = name;
    }

	/** Create a copy of the Component.
	* This method wraps SceneManager->CopyComponent.
	* \param name Name of the new Component, if name is already in use the previously existing Component will be returned.
	*/
    Component* copy(const std::string& name);

    /**Destroys the Component.
    * Wraps SceneManager::destroyComponent.
    * \param deleteIfInUse If this parameter is false, the Component will not be destroyed if it has any users.
    */
    virtual void destroy(const bool deleteIfInUse);

    ///Get the type of the Component, this should be the class name and should correspond to a ComponentCreators associated type.
    virtual const std::string getType() = 0;

    /** Notifies the Component that it has been attached to a SceneNode.
	* This method can be overriden to change how many SceneNode's can use the Component.
	* This method is an internal method and should not be called directly.
	* \param node SceneNode the Component has been attached to.
	*/
    virtual void registerUser(SceneNode* node)
    {
        if (isUser(node))
            return;
        users.push_back(node);
    }

    /** Remove the Component from the passed SceneNode
	* This method can be overriden for different behavior.
	* \param node The node from which the Component should be removed, nothing happens if the Component is not attached to node.
	*/
    virtual void removeUser(SceneNode* node);
    ///Removes the Component from all of the SceneNodes that use it.
    virtual void removeAllUsers();

    ///Get the number of SceneNodes that use the Component.
    inline const int getNumberOfUsers()
    {
        return users.size();
    }

    /** Notifies the Component that it has been attached to a SceneNode.
	* This method is an internal method and should not be called directly.
	* \param node SceneNode the Camera has been removed from.
	*/
    virtual void notifyRemoved(SceneNode* node)
    {
        users.remove(node);
    }

    ///Get a reference to the list of SceneNodes that use the Component.
    inline const std::list<SceneNode*>& getUsers()
    {
        return users;
    }

    /** Check if the passed SceneNode uses the Component.
    * \param node The SceneNode to check.
    * \return True if node uses the Component, false if it does not.
    */
	inline bool isUser(const SceneNode* node)
	{
		std::list<SceneNode*>::const_iterator iter;
		for (iter = users.begin(); iter != users.end(); ++iter)
		{
			if ((*iter) == node)
				return true;
		}

		return false;
	}
};

#endif // COMPONENT_H_INCLUDED
