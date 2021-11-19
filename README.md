# Coin Collector
Use the WASD keys to move. Collect all of the coins to win!

# Project Requirements
SDL2
SDL2 image
An installer for Coin Collector is in the Setup/Release folder.

# Code Structure Overview
This project falls under Capstone Option 1: a video game.

Game.cpp/.h runs all of the code necessary to initialize SDL components and assets,
accept inputs from the player and render and update the images to the screen. It also
checks for our win condition and clears the game upon closing.

Texture.h handles loading textures into SDL and drawing the texture to the screen.

Entity.h / Components.h are the base classes for the game's Entity Component System,
which was developed with the assistance of Carl Birch and his SDL tutorial series.

MovementComponent.h handles the entity's position and size on the screen.
ImageComponent.h handles the entity's texture and animations.
MapComponent.h handles loading the game's tilesets and arranging them in a specific grid.
InputComponent.h handles the player's input and how it affects player-controlled entities.

# Rubric Completion
- The project demonstrates an understand of C++ functions and control structures by
ensuring each function completes only a specific task.
- The project reads data from a text file and processes the data in MapComponent.h
by designing the game's grid and drawing a tileset to it.
- The project accepts user input in InputComponent.h and Game.cpp and processes the
input.
- The project uses Object Oriented Programming techniques by organizing each component
into its own class with its own set of variables and methods.
- Classes use appropriate access specifiers for class members by explicitly specifying
them as public or private.
- The MovementComponent.h class constructor utilizes member initialization lists.
- Component classes abstract their implementation details from the Entity.h interface.
- Classes encapsulate behavior through the use of getters and setters and the utilization
of asserts to ensure code is handled properly at any given time.
- Component classes follow an appropriate inheritance hierarchy with the use of pure virtual
functions and proper usage of override functions.
- Derived component class functions (Init, Draw, and Update) override virtual base class
functions.
- The project uses scope / RAII where appropriate.

# Copyright
Entity.h's original design by Carl Birch.
