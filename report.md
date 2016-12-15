Mason Engine Report
===================

## Introduction

## Software Architecture

Our current game engine supports 2D rendering of sprites defined in a scene graph defined in json. The scene graph consists of game objects, which in turn consist of components such as Transform components  (position, rotation, scale) and Rendering components (mesh, shader, color). The engine currently does not support input and thus all inputs have to be hard coded into the engine, so it is currently more of a rendering engine with physics attached than an actual game engine.

Below is a simplified class diagram of our current engine.

![class diagram](https://github.itu.dk/bjol/TeamDoesNotMatter/raw/master/images/class_diagram.png "Class Dirgram")

## Performance

## Future Work

## Work Distribution

+ Bjørn
  - Base Particle System
  - Spline Curves for the Particle System
  - Audio
  - Scene Parser
  - Component System
  - Overall Engine Strucure
  - Audio and Particle Demo
+ Carol
  - Box2D Physics
  - Sprite Renderer
  - Transforms
  - Debug GUI
  - Physics Demo
+ Rasmus
  - Scene Parser
  - Base Particle System
  - Scripts
  - Time Management
  - Input Management
  - Split Screen
  - Overall Engine Strucure
  - Asteroids Game
