/**
* \author Jack Owen Shelton
* CS4322 Project Predator VS. Prey Simulator.
* \date Spring 2009
*/

#ifndef ANIMAL_H_INCLUDED
#define ANIMAL_H_INCLUDED

#include <string>
#include <hgevector.h>
#include <hgecolor.h>
#include "BehaviorStates.h"

class SceneNode;

///Basic Animal class, holds all fields and methods common to Predators and Prey.
class Animal
{
protected:
	///Name of the Animal, this should be set in the Constructor of any subclasses.
	std::string name;

	///Species of the animal.
	std::string species;

    ///The current behavioral state of the Animal.
	BehaviorState currentBehavior;

	///The angle of vision of the animal. ex. A sight angle of 70 would correspond to the animal being able to see 35 degrees left and right of the direction its facing.
	double sightAngle;
	///How far the animal can see, 1 unit = 1 pixel.
	double sightDistance;
	///How far the animal can effectively hear.
	double hearingDistance;

	///Stealth factor of the Animal.  This affects when other Animals can hear the Animal and should be clamped between 0 and 1.
	double stealth;
	///Stealth factor of the Animal.  This affects when other Animals can see the Animal and should be clamped between 0 and 1.
	double camoflauge;

	///This is the weight of the animal (in pounds) and affects how a predator will react to a prey and vice versa.  An elephant won't run from a dog, and a dog won't attack an elephant.  It is clamped from 0 to 20000.
	double weight;

    ///The base speed of the Animal.  This is modified by the behaviors.
    double baseSpeed;

	///Main SceneNode representing the Animal's position and orientation.
	SceneNode* mainNode;
	///SceneNode that is attached to the Camera's node and is used to point at mainNode when the Animal is offscreen.
	SceneNode* pointerNode;

    ///Setup the node heirarchy.  This will be the same for both Predators and Prey so it is implemented in this class.  This method also regesters the Animal to receive updates from the SceneManager.
    void setupNodeHeirarchy();

    ///Destroy the node heirarchy used by the animal.  This should be called in the deconstructor of Predator and Prey.  This also makes sure to remove the Animal from the SceneManager's update listeners.
    void destroyNodeHeirarchy();

    ///Update method called by subclasses in their own update method.  This has nothing to do with the actual simulation which is why it is hidden away.
    void updatePointer();

public:
    ///Constructor, just initializes some variables.
    Animal() : currentBehavior(PASSIVE), sightAngle(0), sightDistance(0), hearingDistance(0), stealth(0), camoflauge(0), weight(0), baseSpeed(0), mainNode(NULL), pointerNode(NULL) {}

	///Required virtual deconstructor.
	virtual ~Animal(){}

    ///Get the name of the Animal.
	inline const std::string& getName(){ return name; }

    ///Get the species of the Animal.
	inline const std::string& getSpecies(){ return species; }

    ///Get the type of the Animal, either Predator or Prey.
	virtual const std::string getType() = 0;

    /** Set the behavior family to be used by the Animal
    * \param family The BehaviorFamily to use.
    */
    virtual void setBehaviorFamily(const std::string& family) = 0;

    /** Set the currently active behavioral state.
    * \param state The state for theAnimal to use.
    * \remark This method should only be called by the PredatorBehavior and PreyBehavior classes during their update cycle.
    */
    virtual void setBehaviorState(const BehaviorState& state) = 0;

    ///Get the Animal's current behavioral state.
    inline const BehaviorState getCurrentBehaviorState(){ return currentBehavior; }

    /** Set the sight cone angle of the Animal.
    * \param angle The angle in degrees.
    * \remark This angle will be split in half to represent how well the Animal can see things to its left and right.
    */
	inline void setSightAngle(double angle)
	{
		if (angle < 0)
			angle *= -1;
		while (angle > 360)
			angle -= 360;

		sightAngle = angle;
	}

    ///Get the sight angle of the Animal.  This will need to be split in half to be used effectively.
	inline const double& getSightAngle(){ return sightAngle; }

    /** Sethow far the Animal can see.
    * \param distance How far, in screen units, that the Animal can see.
    */
	inline void setSightDistance(double distance)
	{
		if (distance < 0)
			distance *= -1;
		sightDistance = distance;
	}

    ///Get how far the animal can see.
	inline const double& getSightDistance(){ return sightDistance; }

    /** Set how far the Animal can hear.
    * \param distance How far the Animal can hear.
    */
	inline void setHearingDistance(double distance)
	{
		if (distance < 0)
			distance *= -1;
		hearingDistance = distance;
	}

    ///Get how far the Animal can hear.
	inline const double& getHearingDistance(){ return hearingDistance; }

    /** Set how stealthy the Animal is.
    * This affects the distance at which another Animal can hear the animal.
    * \param stealth How stealthy this Animal is.
    * \remark This value is clamped from 0 to 1.  A value of 0 means the Animal will be detected as soon as it enters another Animal's hearing range and a value of 1 means that it will not be heard at all.
    */
	inline void setStealth(const double& stealth)
	{
		if (stealth > 1)
			this->stealth = 1;
		else if (stealth < 0)
			this->stealth = 0;
		else
			this->stealth = stealth;
	}

    ///Get the stealth value.
	inline const double& getStealth(){ return stealth; }

    /** Set how well camoflauged the Animal is.
    * This affects the distance at which another Animal can see the Animal.
    * \param camo How well camoflauged the Animal is.
    * \remark This value is clamped from 0 to 1.  A value of 0 means the Animal will be detected as soon as it enters another Animal's sight range and a value of 1 means that it will not be seen at all.
    */
	inline void setCamoflauge(const double& camo)
	{
		if (camo > 1)
			camoflauge = 1;
		else if (camo < 0)
			camoflauge = 0;
		else
			camoflauge = camo;
	}

    ///Get how well camoflauged the Animal is.
	inline const double& getCamoflauge(){ return camoflauge; }

    /** Set the weight of the Animal
    * The weight of an Animal affects how predators react to the Animal.
    * \param weight How heavy the Animal is.
    * \remark This value is clamped from 0 to 20000.
    */
	inline void setWeight(double weight)
	{
		if (weight < 0)
			weight *= -1;
		if (weight > 20000)
			weight = 20000;
		this->weight = weight;
	}

    ///Get the weight of the Animal.
	inline const double& getWeight(){ return weight; }

	/** Set the speed of the Animal.
    * \param speed How far the animal moves in a second.
    * \remark This value should be greater than 0.
    */
	inline void setSpeed(double speed)
	{
		if (speed <= 0)
			speed *= -1 + .1;
		this->baseSpeed = speed;
	}

    ///Get the base speed of the Animal.
	inline const double& getSpeed(){ return baseSpeed; }

    /** Set the position of the Animal.
    * \parm position The position of the Animal.
    */
	void setPosition(const hgeVector position);
	///Get the position of the Animal.
	hgeVector getPosition();

    /** Move the Animal
    * \param factor The amount by which to modify the base speed, should be greater than 0.  Negative values will move the Animal backwards.
    */
    virtual void move(const double& factor) = 0;
	/** Set the heading of the Animal.
	* \param angle The heading of the Animal in degrees.
	*/
	void setHeading(const double& angle);
	///Get the heading of the animal in degrees.
	const double getHeading();

	/** Construct the renderables used.
	* \param spriteName The name of the sprite to use to render the Animal.  The sprite's size should reflect the animal's weight, but it doesn't have to.
	* \param pointerSpriteName The name of the sprite to use for the pointer.
	* \param hearingColor The color to be used for the circle representing the hearing range of an animal.
	* \param sightColor The color used for the line of sight triangle.
	* \remark This should be the last step performed by an Environment when creating a Predator or Prey and should be called after all other properties have been set.
	*/
	void constructRenderables(const std::string& spriteName, const std::string& pointerSpriteName, const hgeColor& hearingColor, const hgeColor& sightColor);
};

#endif // ANIMAL_H_INCLUDED
