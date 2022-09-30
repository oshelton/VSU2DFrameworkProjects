/**
* \author Jack Owen Shelton
* Framework used in both my CS 3520 and CS 4322 projects.
* \date Spring 2009
*/

#ifndef DLL_H_INCLUDED
#define DLL_H_INCLUDED

/** \mainpage Framework Documentation
\section license Licensing And Copyright.
This project was created and is maintained by Jack Owen Shelton for use on personal and academic projects.

Jack Owen Shelton can be reached at joshelton@valdosta.edu or o_shelton@yahoo.com.

\section intro Introduction
This project provides a simple and straightforward interface that is designed to make the development of simple 2d hardware
accelerated applications with GUI, Camera, and basic scene graph support.

\section features Features
The Framework provides acces to many of the features of several libraries.

\subsection system System
All core objects are initially created by the SystemManager and the main loop is handled by it as well.  The SystemManager
also manages SystemStates which represent a specific scene within the Framework.  New SystemStates can be added by inheriting
the abstract SystemState class and passing an instance of the new class to the SystemManager::addSystemState method.

\subsection graphics Graphics
The framework provides high level access to the graphical capabilities of the HGE game engine.  More information about HGE
can be found at <a href="http://hge.relishgames.com/">HGE's homepage</a>.

The framework wraps the following HGE funtionality:
<ul>
<li>Wrapper for HGE's input functionality.</li>
<li>Sprite rendering provided by SimpleRenderable with support for most hgeSprite functionality.</li>
<li>Line rendering provided by LineRenderable with support for all of HGE's line rendering functionality.</li>
<li>Text rendering provided by TextRenderable offering all of HGE's built in 2d text rendering functionality.</li>
<li>Graphics resource script management provided by the ScriptManager class that wraps HGE's own hgeResourceManager.</li>
</ul>

\subsection gui GUI
The framework also provides a high level straightforward interface for using the CEGUI GUI library.  More information about
CEGUI can be found at <a href="http://www.cegui.org.uk/wiki/index.php/Main_Page">CEGUI's homepage</a>.  The classes necesarry
for using CEGUI were written by Japhett Burt.

The Framework provides easy access to the fallowing CEGUI functionality:
<ul>
<li>One method call initialization of CEGUI.</li>
<li>Easy management of layouts.</li>
<li>Message console provided for debug and error output.</li>
<li>Methods for automatically and safely retrieving and casting CEGUI widgets.</li>
<li>Automatic and transparent GUI input handling.</li>
</ul>

\subsection scenegraph Scene Graph
The Framework provides a basic scene graph implementation that allows the creation of a simple heirarchial graph of SceneNodes
which store the rotation, scale, and position of objects within 2d space.  SceneNodes can have any number of child SceneNodes
attached to them, but the actual grunt work of rendering is performed by COmponents.  Components can be anything from Renderables
(SimpleRenderable, LineRenderable, etc) to Cameras and other objects that need to be associated with a location, rotation, or
scale within the 2d scene.

The SceneManager and SceneNode classes designs were inspired by similar classes from the Ogre3D rendering library.  More
information about Ogre3D can be found at their <a href="http://www.ogre3d.org/">homepage</a>.

The Framework's Scene Graph provides the following features.
<ul>
<li>SceneNodes can be translated in local, parent SceneNode, and global (untested) space.</li>
<li>SceneNodes normaly inherit the rotation and scale of their parents but this can be disabled.</li>
<li>New Component types can be added throught the ComponentCreator abstract class and the SceneManager::registerComponentType
method.</li>
</ul>

\subsection input Input
The Framework simply provides a less obscure interface to HGE's built in input handling functionality.

\subsection scripting Scripting
The Framework also provides several classes for simplifying the use of the AngelScript scripting library.  More information
about AngelScript can be found at its <a href="http://www.angelcode.com/">homepage</a>.

The ScriptManager class provides an easy interface for loading and executing AngelScript scripts and the ScriptBinder class can
be inherited from to generate bindings for more of the Framework's functionality or to generate bindings for client code.

\section patterns Design Patterns Used.
The following design patterns are used by the Framework.

\subsection observer Observer Pattern
The Observer pattern is used in the following classes:
<ul>
<li>RenderOriginator</li>
<li>RenderableListener</li>
<li>UpdateOriginator</li>
<li>UpdateListener</li>
</ul>

\subsection decorator Decorator Pattern
The Decorator pattern is used in the CompoundRenderable class.

\subsection factory Factory Method/Abstract Factory Pattern
The SceneManager class acts as a slightly different kind of abstract factory, where new types can be added dynamically without
ever having to inherit from the SceneManager itself through the use of the ComponentCreator abstract class and the
SceneManager::registerComponentType method.

\subsection facade Facade Pattern
The following classes implement the Facade pattern:

<ul>
<li>The GuiManager completely encapsulates the CEGUI objects.</li>
<li>The ScriptManager only encapsulates the most commonly used aspects of AngelScript and the hgeResourceManager, the wrapped
objects are still accesable.</li>
</ul>

\subsection adapter Adapter Pattern
The following classes use the Adapter pattern:

<ul>
<li>SimpleRenderable</li>
<li>TextRenderable</li>
</ul>

\subsection template Template Pattern
The Template Pattern is used in the creation of Renderables.  The Renderable class implements aspects of the rendering process that
are common to any objects that are going to be rendered such as culling and basic screen space coordinate translation and hides away
ensures that any subclasses iterate over any SceneNodes the Renderable may be attached to.  Subclasses of Renderable must only override
a single method and place their own specific rendering code within this method so the end developer only needs to be concerned with the
specific details of the type of render operation being performed and not the more mathematical details that go into the rendering process.

For a closer look, see:

<ul>
<li>Renderable</li>
<li>SimpleRenderable</li>
<li>LineRenderable</li>
<li>TriangleRenderable</li>
<li>TextRenderable</li>
</ul>

\subsection fly Flyweight Pattern
The Flyweight pattern is used inderectly within the Framework since while ScneeNodes can only have one Component at a time, Components
may be attached to multiple SceneNodes.  This is especially useful when dealing with Renderable classes since sharing the actual object
being rendered will help reduce batching which is a major performance affector in modern hardware accelerated applications.

For a more concrete example the Predator & Prey Simulator uses this pattern to restrict the number of Renderables created to one set for
each species.

\subsection iter Iterator Pattern
The SceneNode class uses a simple iterator class to iterate over attached child SceneNodes without providing direct access to the container
that actually holds the pointers to the children.

\section projects Other CS4322 Projects Completed In This Code
The Framework includes code that satisfies the requirements for more than just project 1 of CS4322.

The TimerManager and Timer classes fullfil the requirements for project 2 except for the fact that it does not provide a context for the
time and only records the elapsed seconds.  Giving a context to the time that timers store is the responsibility of the client.

Project 4 was completed through the classes mentioned in the Facade and Adapter subsections of the Design Patterns Used section.

The Flyweight pattern is usable directly through this Framework, and the Predator & Prey Simulator uses it as an efficiency step.
This framework also takes advantage of the Iterator pattern.
*/

#ifdef BUILD_DLL
    #ifndef EXPORT_FRAME
    #define EXPORT_FRAME __declspec(dllexport)
    #endif
#else
    #ifndef EXPORT_FRAME
    #define EXPORT_FRAME __declspec(dllimport)
    #endif
#endif

#endif // DLL_H_INCLUDED
