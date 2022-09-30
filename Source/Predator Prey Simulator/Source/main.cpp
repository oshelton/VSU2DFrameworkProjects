/**
* \author Jack Owen Shelton
* CS4322 Project Predator VS. Prey Simulator.
* \date Spring 2009
*/

/** \mainpage Predator Prey Simulator Documentation
\section license Licensing And Copyright.
This project was created and is maintained by Jack Owen Shelton for use on personal and academic projects.

Jack Owen Shelton can be reached at joshelton@valdosta.edu or o_shelton@yahoo.com.

\section intro Introduction
This project is a simple Predator Prey Simulator that is targeted towards fulfilling the requirements set forth in Dr. David
Gibsons CS 4322 project 1 instructions.  This project has been expanded to include several features not required in the original
assignment such as:

<ul>
<li>Graphics that show the simulations progress and allows for navigating around the simulation's environment.</li>
<li>GUI for controlling the simulation</li>
<li>Dynamic simulation loading through script files.</li>
<li>Animals have sight and hearing senses.</li>
<li>Weight property added to create further detail in Predator and Prey relations.</li>
<li>More options for Animal Behavior State as given by the BehaviorState enumerator.</li>
<li>Grouping of behaviors into behavior families that decide which behavior is associated with which BehaviorState.
<li>Variable simulation timing, to speed up or slow down the simulation.</li>
<li>When any major event happens in the simulation it is recorded and written to a report when the simulation ends.</li>
</ul>

\section design Design Patterns Used

\subsection abstract Abstract Factory
The abstract factory pattern is used to manage the different Environments available in the simulation.  The Environment class
serves as the base factory class and all other types of Environments inherit from this class.  The subclasses of Environment
are used to group species of Predator and Prey into regions and can have a different background image associated with the subclass
to one that may better fit the real word region the Environment represents.  The Environment that is currently in use is kept track
of in SimulationManager's currentEnvironment pointer and is switched whenever a simulation belonging to a different environment is
loaded.

\subsection observe Observable
The Observable pattern is used in the PreyManager and PredatorManager classes.  Predators can be registered as observers of the
PreyManager class and are updated once the PreyManager has prepared its moved and state changed Prey lists.  Prey are registered
with the PredatorManager in the same fashion.

\subsection fly Flyweight
The Flyweight pattern is used by the constructRenderable method of the Animal class.  This method is used to create the SimpleRenderable
and LineRenderables used by Animals and the method is written in such a way that only one set of Renderables will be created for each
seperate species of Predator and Prey thereby allowing all Predators and Prey of the same species to share the same renderables which helps
performance.

Another location this pattern is used in is the in the Behavior management of Animals.  Predator and Prey Behavior families are built from the
ground up to be shared and don't hold any concrete references to Animals tat use them.

The Flyweight pattern is also used in Animal behavior management as all animals of a species share the same PredatorbehaviorFamily or PreyBehaviorFamily.

\subsection state State
In this project the state pattern is used to seperate Animal behavior from Animal properties, and as such Predators and Prey have no clue
as to how they are being updated.  This depends entirely on which PredatorBehaviorFamily or PreyBehaviorFamily they are using and what their
current BehaviorState is.

*/

#include <SystemManager.h>
#include "SimulationState.h"

int main()
{
    SystemManager* manager = SystemManager::get();

    manager->addSystemState(new SimulationState());

    manager->start("SimulationState", "Predator & Prey Simulator");

    delete manager;

    return 0;
}
