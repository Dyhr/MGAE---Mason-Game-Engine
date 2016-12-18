#pragma once

#include <string>
#include <vector>
#include <glm/glm.hpp>
#include <map>
#include "Mason/Audio.hpp"
#include "picojson.h"


namespace Mason {

	/** @class CameraDescriptor
	* @brief Describes a Camera component  <BR>
	*
	* "camera": {
	*    "viewportMin": [ 0, 0 ]	// Optional, default: [0,0] <BR>
    *    "viewportMax": [ 1, 1 ]	// Optional, default: [1,1] <BR>
	* }
	*/

	class CameraDescriptor {
	public:
		bool found = false;
		glm::vec2 viewportMin = glm::vec2(0, 0);
		glm::vec2 viewportMax = glm::vec2(1, 1);
	};

	/** @class ParticleDescriptor
	* @brief Describes a Particle component <BR>
	*  "particles": {
	*   "texturePath": "/data/images",	// Optional, default: nullptr <BR>
	*	"rate": 60,						// Optional<BR>
	*	"lifespan": 0.5,				// Optional <BR>
	*	"velocityState": "random",		// Optional, options: FIXED | RANDOM | LINEAR | SPLINE <BR>
	*	"minVelocity": [0, 300, 0],		// Optional <BR>
	*	"maxVelocity": [20, 300, 0],	// Optional <BR>
	*	"gravity": [0, 0, 0],			// Optional <BR>
	*	"size": 1,						// Optional <BR>
	*	"minsize": 0					// Optional <BR>
	*	"maxsize": 1					// Optional <BR>
	*	"sizeState": "linear",			// Optional <BR>
	*	"initialSize": 0.3,				// Optional <BR>
	*	"finalSize": 0.7,				// Optional <BR>
	*	"initialColor": [1, 1, 0, 1],	// Optional <BR>
	*	"finalColor": [1, 0, 0, 1],		// Optional <BR>
	*	"rotationState": "fixed",		// Optional <BR>
	*	"rotation": 0,					// Optional <BR>
	*	"minrotation": 0,				// Optional <BR>
	*	"maxrotation": 1,				// Optional <BR>
	*	"initialrotation": 0,			// Optional <BR>
	*	"finalrotation": 1,				// Optional <BR>
	*	"color": [0,0,0,0],				// Optional <BR>
	*	"mincolor": [0,0,0,0],			// Optional <BR>
	*	"maxcolor": [0,0,0,0],			// Optional <BR>
	*	"initialcolor": [0,0,0,0],		// Optional <BR>
	*	"finalcolor": [0,0,0,0],		// Optional <BR>
	*	"colorState": "linear",			// Optional <BR>
	*	"splinePointsSize": [0.5, 0.5], // Optional <BR>
	*	"splinePointsColor": [0.5, 0.5],// Optional <BR>
	*	"splinePointsRotation": [0.5, 0.5], // Optional <BR>
	*	}
	*/
	class ParticleDescriptor
	{
	public:
		bool found = false;
		std::string texturePath = "";
		float rate;
		float lifespan;
		glm::vec3 velocity;
		glm::vec3 gravity;
		//Used for random
		float minSize;
		float maxSize;
		float minRotation;
		float maxRotation;
		glm::vec3 minVelocity;
		glm::vec3 maxVelocity;
		glm::vec4 minColor;
		glm::vec4 maxColor;
		//Used for interpolation
		float initialSize;
		float finalSize;
		glm::vec4 initialColor;
		glm::vec4 finalColor;
		float initialRotation;
		float finalRotation;

		std::string velocityState;
		std::string rotationState;
		std::string sizeState;
		std::string colorState;
		std::vector<glm::vec2> splinePointsSize;
		std::vector<glm::vec2> splinePointsColor;
		std::vector<glm::vec2> splinePointsRotation;
	};


	/** @class SpriteDescriptor
	* @brief Describes a Sprite component <BR>
	*  "sprite": {
    *    "name": "mario_0", // Mandatory <BR>
    *    "color": [1,1,1,1] // Optional, default [1,1,1,1] <BR>
	* 
	* }
	*/

	class SpriteDescriptor {
	public:
		bool found = false;
		std::string name;
		glm::vec4 color = glm::vec4(1, 1, 1, 1);
	};

	/** @class BoxColliderDescriptor
	* @brief Describes a kind of Collider2D component: BoxCollider (square shaped) <BR>
	*
	*  "physicsbody": { // as part of a PhysicsBody2D <BR>
	*    "boxes": [ // Optional, for giving a BoxCollider . <BR>
	*      {
	*       "center": [ 0, 0 ], // Optional, default: [0,0] <BR>
	*        "height": 1, // Optional, default: 1 <BR>
	*        "width": 1, // Optional, default: 1 <BR>
	*		 "density": 1, // Optional, default: 1 <BR>
	*		 "friction": 0.1 // Optional, default: 0.1 <BR>
	*      }
	*	   ]
	*  }
	*/
	class BoxColliderDescriptor {
	public:
		glm::vec2 center = glm::vec2(0, 0);
		float width = 1;
		float height = 1;

		float density = 1;
		float friction = 0.1f;
	};

	/** @class CircleColliderDescriptor
	* @brief Describes a kind of Collider2D component: CircleCollider (circle shaped) <BR>
	*
	*  "physicsbody": { // as part of a PhysicsBody2D <BR>
	*	 "circles": [ // Optional, for giving a CircleCollider. <BR>
	*       {
	*        "center": [ 0, 0 ], // Optional, default:  [0,0] <BR>
	*        "radius": 1, // Optional, default: 1 <BR>
	*		 "density": 1, // Optional, default: 1 <BR>
	*		 "friction": 0.1 // Optional, default: 0.1 <BR>
	*      } <BR>
	*    ] <BR>
	*  }
	*/
	class CircleColliderDescriptor {
	public:
		glm::vec2 center = glm::vec2(0, 0);
		float radius = 1;

		float density = 1;
		float friction = 0.1f;
	};

	/** @class PhysicsBodyDescriptor
	* @brief Describes a PhysicsBody component <BR>
	*
	*  "physicsbody": { <BR>
    *    "type": "kinematic", // Optional. Options: "dynamic" (default) | "static" | "kinematic"<BR>
    *    "boxes":[			// Optional, see BoxColliderDescriptor for details <BR>
	*	... <BR>
	* ] <BR>
	*	 "circles": [			// Optional, see CircleColliderDescriptor for details <BR>
	*	... <BR>
	* ] <BR>
    * }
	*/

	class PhysicsBodyDescriptor {
	public:
		bool found = false;
		int type;
		std::vector<BoxColliderDescriptor> boxColliders;
		std::vector<CircleColliderDescriptor> circleColliders;
	};

	/** @class TransformDescriptor
	* @brief Describes a Transform component <BR>
	* 
	* "transform": { <BR>
	*	"position" = [0, 0, 0],		// Optional, default: [0,0,0] <BR>
	*	"rotation" = 0,				// Optional, default: 0 <BR>
	*	"scale" = 1,				// Optional, default: 1 <BR>
	*	"parentId" = -1				// Optional, default: -1 <BR>
	* }
	*/
	class TransformDescriptor {
	public:
		glm::vec3 position = glm::vec3(0, 0, 0);
		float rotation = 0.0f;
		float scale = 1.0f;
		int parentId = -1;
	};

	/** @class AudioDescriptor
	* @brief Describes an Audio component <BR>
	*
	* "audio": { <BR>
	*	"path": "data/sounds/1-octave/A5.wav",	// Optional, default: "data/sounds" <BR>
	*	"type": "soundeffect"				// Optional. Options: "soundeffect" (default) | "music" <BR>
	* }
	*/
	class AudioDescriptor {
	public:
		std::string path ="data/sounds";
		SoundType type=EFFECT;
		bool found = false;
	};

	/** @class ScriptDescriptor
	* @brief Describes a Script component <BR>
	*
	* "name": "player"  // mandatory <BR>
	* "properties": [ "thrust", "left", "right", "shoot", "camera" ], //Optional. Defines strings used in the script. In the example, the strings contain control keys and the camera used <BR>
    *      "thrust": "w", <BR>
    *      "left": "a", <BR>
    *      "right": "d", <BR>
    *      "shoot": "e", <BR>
    *      "camera":  "Camera 1" <BR>
	*/
	class ScriptDescriptor {
	public:
		std::string name;
		std::map<std::string, std::string> strings;
		std::map<std::string, float> numbers;
	};


	/** @class GameObjectDescriptor
	* @brief Describes a GameObject <BR>
	*
	* "uniqueId": 0,		// Optional, default: 0 <BR>
    *  "name": "Object",	// Optional, default: "Object" <BR>
	* "transform": {		// Optional, created by default, see TransformDescriptor for details <BR>
	*	...	 <BR>
	* }, <BR>
	* "sprite": {			// Optional, see SpriteDescriptor for details <BR>
	*	... <BR>
	* }, <BR>
	* "camera": {			// Optional, see CameraDescriptor for details <BR>
	*	... <BR>
	* }, <BR>
	* "audio": {			// Optional, see AudioDescriptor for details <BR>
	*	... <BR>
	* }, <BR>
	* "particles": {		// Optional, see ParticleDescriptor for details <BR>
	*	... <BR>
	* }, <BR>
	* "physicsbody": {		// Optional, see PhysicsBodyDescriptor for details <BR>
	*	... <BR>
	* }, <BR>
	* "scripts": [			// Optional, list of Script, see ScriptDescriptor for details <BR>
	*	{ <BR>
	*		... <BR>
	*	} <BR>
	* ]
	*/
	class GameObjectDescriptor {
	public:
		std::string name = "Object";
		int uniqueId = 0;

		TransformDescriptor transform;
		SpriteDescriptor sprite;
		CameraDescriptor camera;
		AudioDescriptor audio;
		ParticleDescriptor particles;
		std::vector<ScriptDescriptor> scripts;
		PhysicsBodyDescriptor physicsBody2D;
	};

	/** @class SceneDescriptor
	* @brief Describes a Scene <BR>
	*
	* "scenename": "Scene",		// Optional, default: "Scene" <BR>
	* "imagepath": "data/images",	// Optional, default: "data/images" <BR>
	* "soundpath": "data/sounds",	// Optional, default: "data/sounds" <BR>
	* "templatepath": "data/templates",	// Optional, default: "data/templates" <BR>
	* "sprites": [			// Optional, list of Sprite, see SpriteDescriptor for details <BR>
	*	{ <BR>
	*		... <BR>
	*	} <BR>
	* ],
	* "gameobjects": [			// Optional, list of GameObject, see GameObjectDescriptor for details <BR>
	*	{ <BR>
	*		... <BR>
	*	} <BR>
	* ], <BR>
	* "gravity": [0, -10],		// Optional, default: [0, -10] <BR>
	* "physicsScale": 100		// Optional, default: 100 <BR>
	*/

	class SceneDescriptor {
	public:
		std::string name = "Scene";

		std::string imagepath = "data/images";
		std::string soundpath = "data/sounds";
		std::string templatepath = "data/templates";

		std::vector<std::string> sprites;

		std::vector<GameObjectDescriptor> gameobjects;

		glm::vec2 gravity = glm::vec2(0, -10);
		float physicsScale = 100;
	};

	/** @class SceneParserDescriptor
	* @brief Parses a JSON file and creates a scene with its elements.
	*/
	class SceneParser {
	protected:
		/** @brief parses a JSON file. Creates the scene that is going to be loaded in the game
		* @param filename name of the JSON file taht contains the elements of the scene
		* @return SceneDescriptor with the elements of the scene
		*/
		static SceneDescriptor parseFile(std::string filename); 

		/** @brief calls the private method parseObject
		* @param name of the JSON file that contains the elements of the Scene
		* @param path of the JSON file that contains the elements of the Scene
		* @return a GameObjectDescriptor with the info of the GameObject of the Scene
		*/
		static GameObjectDescriptor parseTemplate(std::string name, std::string path); 

		friend class Engine;
		friend class Scene;
	private:
		static GameObjectDescriptor parseObject(picojson::value o, std::string path);
	};
}
