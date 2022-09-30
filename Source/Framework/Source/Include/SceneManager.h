/**
* \author Jack Owen Shelton
* Framework used in both my CS 3520 and CS 4322 projects.
* \date Spring 2009
*/

#ifndef SCENEMANAGER_H_INCLUDED
#define SCENEMANAGER_H_INCLUDED

#include <map>
#include <list>
#include <string>
#include <hgevector.h>
#include "dll.h"
#include "RenderOriginator.h"
#include "UpdateOriginator.h"

class Camera;
class SimpleRenderable;
class SceneNode;
class RenderableListener;
class UpdateListener;
class Component;
class ComponentCreator;

/** Perhaps the most important class in the framework, creates and manages SceneNodes and Components.
* \sa RenderOriginator, UpdateOriginator
*/
class EXPORT_FRAME SceneManager : public RenderOriginator, public UpdateOriginator
{
protected:
    ///Map of SceneNodes that make up the heart of the scene graph.
    std::map<std::string, SceneNode*> sceneGraph;
    ///Map of Cameras, these are kept seperate from regular components due to their usage requirements.
	std::map<std::string, Camera*> cameras;
	///Map of components, Components can be (but do not have to be) shared between multiple SceneNodes.
    std::map<std::string, Component*> components;
    ///Map of ComponentCreators that are used to create Components.
    std::map<std::string, ComponentCreator*> creators;
    ///A special SceneNode that SceneNodes without parents are attached to.
    SceneNode* nullSceneNode;
    ///Special SceneNode that all SceneNodes are attached to, think of it as the root node in a tree.
    SceneNode* rootSceneNode;

    ///Singleton access method, returns a pointer to the SceneManager.
    static SceneManager* scManager;

    ///Constructor.
    SceneManager();

public:
    ///Deconstructor.
    virtual ~SceneManager();

    /**Return the null SceneNode.
    * \remark This method should only be used internally, it should not be used outside the framework.
    */
    SceneNode* getNullSceneNode();
    /** Get the root SceneNode.
    * \return This method returns the root SceneNode, serves as the core object in the scene graph, all transformations occur around this node.
    */
    SceneNode* getRootSceneNode();

    /** Create a new SceneNode.
    * \param name Name of the new SceneNode to create.
    * \remark If a SceneNode named name already exists the previously existing SceneNode will be returned.
    */
    SceneNode* createSceneNode(const std::string& name);
    /** Create a new SceneNode with benefits.
    * \param name Name of the new SceneNode to create.
    * \param position The position the SceneNode should be positioned at once it is created.
    * \param z Z (depth) coordinate of the SceneNode, determines what is rendered before or after (below or on top of) the SceneNode.
    * \param scale Scale of the SceneNode, only directly affects Renderables, but since the scale of a SceneNode affects the position of its children it must be included at the SceneNode level.
    * \param rotation Heading, in degrees, that the SceneNode should initially have.
    * \remark If a SceneNode named name already exists the previously existing SceneNode will be returned.
    */
    SceneNode* createSceneNode(const std::string& name, hgeVector position, double z = 0.5, double scale = 1.0, double rotation = 0);
    /** Check if a SceneNode exists.
    * \param name The name of the SceneNode to check existence of.
    * \return True if a SceneNode named name exists, false if one does not.
    */
    const bool sceneNodeExists(const std::string& name);
    /** Get a SceneNode.
    * \param name The name of the SceneNode to retrieve.
    * \return NULL if no SceneNode named name exists.
    * \remark This method searches  through the sceneGraph map in order to find the SceneNode, which is much faster and more stable than using a recursive function.
    */
    SceneNode* getSceneNode(const std::string& name);
    /** Register a SceneNode in the sceneGraph map.
    * \param entity The SceneNode to be added.
    * \remark This methos is used by SceneNode's createChildSceneNode method and should not be called manually.
    * \sa SceneNode
    */
    void registerSceneNode(SceneNode* entity);
    /** Destroy a SceneNode.
    * \param name The name of the SceneNode to destroy.
    * \remark If no SceneNode named name exists, this method will do nothing.
    */
    void destroySceneNode(const std::string& name);
    /** Destroy a SceneNode.
    * \param enttiy A pointer to the SceneNode to be destroyed.
    */
    void destroySceneNode(SceneNode* entity);
    /** Rename a SceneNode
    * \param oldName The name of the SceneNode to change.
    * \param newName The new name of the SceneNode.
    * \remark If no SceneNode named oldName exists or a SceneNode named newName already exists this method will be ignored.
    */
    void renameSceneNode(const std::string& oldName, const std::string& newName);

    /** Create a new Camera.
    * \param name The name of the Camera to create.
    * \remark If name is already in use by another Camera, the previously existing one will be returned.
    */
	Camera* createCamera(const std::string& name);
	/** Check if a Camera exists.
    * \param name The name of the Camera to check existence of.
    * \return True if a Camera named name exists, false if one does not.
    */
    const bool cameraExists(const std::string& name);
    /** Get a Camera.
	* \param name The name of the Camera to retrieve.
	* \return The Camera named name or NULL if one named name does not exist.
	*/
	Camera* getCamera(const std::string& name);
	/** Destory a Camera.
	* \param name Name of the Camera to destroy.
	* \param destroyIfInUse If this is true the Camera will be destroyed even if it is still attached to a SceneNode (after removing itself cleanly anyway).
	* \remark The System will not allow for the default Camera to be destroyed, its name is "default".
	*/
	void destroyCamera(const std::string& name, const bool& destroyIfInUse);
	/** Destory a Camera.
	* \param cam The Camera to be destroyed.
	* \param destroyIfInUse If this is true the Camera will be destroyed even if it is still attached to a SceneNode (after removing itself cleanly anyway).
	* \remark The System will not allow for the default Camera to be destroyed, its name is "default".
	*/
	void destroyCamera(Camera* cam, const bool& destroyIfInUse);
	/** Rename a Camera.
	* \param oldName The name of the Camera to change.
    * \param newName The new name of the Camera.
    * \remark If no Camera named oldName exists or a Camera named newName already exists this method will be ignored.
	*/
	void renameCamera(const std::string& oldName, const std::string& newName);

    ///Overriden assignCamera method, does nothing in this case.
    void assignCamera(Camera* cam){}
    ///Retrieve the primary Camera
    Camera* getCamera(){ return cam; }
    ///Overriden removeCamera method, just returns the default camera.
    Camera* removeCamera(){ return cam; }

    /** Register a new Component type.
    * \param typeName This is the name of the Component type, this is associated with the ComponentCreator and should match the class name that the ComponentCreator instantiates.
    * \param creator The COmponentCreator to be registered.
    * \remark If a ComponentCreator named type has already been registered, this method will be ignored.
    */
    void registerComponentType(const std::string& typeName, ComponentCreator* creator);
    /** Create a new Component.
    * \param type The type of Component to create, this string retrieves the ComponentCreator and uses it to create the Component.
    * \param name The name to be given to the new Component.
    * \return NULL, if there is not a ComponentCreator associated with type or the previously existing Component if name is already in use.
    */
    Component* createComponent(const std::string& type, const std::string& name);
    /** Check if a Component exists.
    * \param name The name of the Component to check existence of.
    * \return True if a Component named name exists, false if one does not.
    */
    const bool componentExists(const std::string& name);
    /** Get a Component.
    * \param name The name of the Component to retrieve.
    * \return NULL if no Component named name exists.
    * \sa Component::createComponent(std::string name)
    */
    Component* getComponent(const std::string& name);
    /** Create a copy of a Component.
    * This method copies a Component using the ComponentCreator associated with the passed Component's type.
    * \param newName The name to be given to the new Component.
    * \param component The Component to be copied.
    * \return The previously existing Component if newName is already in use.
    * \remark This method assumes that component was created using a ComponentCreator and its type matches that of a registered ComponentCreator.
    * \sa  Component::copyComponent(std::string name, Component* component)
    */
    Component* copyComponent(const std::string& newName, Component* const component);
    /** Destroy a Component.
    * \param name The name of the Component to destroy.
    * \param destroyIfInUse If this is true the Component will be destroyed even if it is still attached to a SceneNode (after removing itself cleanly anyway).
    * \remark If no Component named name exists, this method will do nothing.
    */
    void destroyComponent(const std::string& name, const bool& destroyIfInUse);
    /** Destroy a Component.
    * \param name The name of the Component to destroy.
    * \param destroyIfInUse If this is true the Component will be destroyed even if it is still attached to a SceneNode (after removing itself cleanly anyway).
    */
    void destroyComponent(Component* const component,  const bool& destroyIfInUse);
    /** Rename a Component.
	* \param oldName The name of the Component to change.
    * \param newName The new name of the Component.
    * \remark If no Component named oldName exists or a Component named newName already exists this method will be ignored.
	*/
    void renameComponent(const std::string& oldName, const std::string& newName);

    ///Clear the current scene of all SceneNodes and Components.
    void clearScene();

    /** Overriden update method from UpdateOriginator.
    * \sa UpdateOriginator
    */
    void update();
    /** Overriden render method from RenderOriginator.
    * This method also renders all RenderTextures managed by the RenderTextureManager.
    * \sa RenderOriginator
    */
    void render();

    ///Singleton access method, returns a pointer to the SceneManager.
    static SceneManager* get();
};

#endif // SCENEMANAGER_H_INCLUDED
