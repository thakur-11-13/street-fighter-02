# Street Fighter II Recreation (C++ / SFML)

###  [PREVIEW VIDEO](https://drive.google.com/file/d/1vPtcj7CI7zcAfuPUd1NIYvbD8SOHr29r/view?usp=sharing)

## Overview

This project is a recreation of the classic 1991 arcade fighting game Street Fighter II, developed from scratch using C++ and SFML.

The primary goal of the project is to understand how fighting games work internally by designing and implementing core gameplay systems without relying on a game engine. The project focuses on gameplay programming, object-oriented design, animation systems, input handling, collision detection, combat systems, AI architecture, and performance-conscious programming.

Rather than simply reproducing the visual aspects of a fighting game, the project is being developed as a systems-oriented programming exercise, with each gameplay component designed and implemented independently.

## Current Progress

The core character animation, movement, input, hitbox, and combat foundations have been implemented.

Both characters can currently interact with each other, perform attacks, register hits through hitboxes, and trigger the corresponding hit animations.

### Implemented Character Movement

- Walk forward
- Walk backward
- Jump forward
- Jump backward
- Neutral jump

### Implemented Attacks

#### Punches
- Light Punch
- Medium Punch
- Heavy Punch

#### Kicks
- Light Kick
- Medium Kick
- Heavy Kick

### Implemented Defensive and Crouching Actions

- Standing Block
- Crouching
- Crouching Block
- Crouching Punch
- Crouching Kick

### Implemented Combat Systems

- Character hitbox registration
- Attack-to-character collision detection
- Hit detection between characters
- Hit animation triggering
- Character-to-character interaction
- Attack state handling
- Animation state management

## Systems Currently Being Developed

The following systems are currently under active development:

### Health System

A character health and damage system is being implemented to connect successful attacks with character damage and match progression.

### Controller Support

Controller input support is currently being designed to allow gameplay using gamepad controls in addition to keyboard input.

### Opponent AI

The opponent AI is being developed using a combination of:

- Hierarchical Finite State Machines (HFSM)
- Random Decision Trees

The Hierarchical FSM provides the overall behavioural structure, while Random Decision Trees are being used to drive combat decision-making and action selection.

The goal is to create an opponent capable of making context-dependent combat decisions rather than relying on a simple sequence of predefined actions.

## Technical Objectives

This project is being used to explore and strengthen understanding of:

- Object-Oriented Programming (OOP)
- Game architecture and system design
- Gameplay programming
- Animation systems
- Input handling
- Collision detection
- Hitbox-based combat systems
- State-driven gameplay
- Finite State Machines
- Hierarchical Finite State Machines
- Decision-making systems for game AI
- Memory and performance optimization
- Debugging and software engineering practices

## Technologies Used

- C++
- SFML (Simple and Fast Multimedia Library)
- Git
- GitHub
- Visual Studio

## Project Status

**Active Development**

Core movement, animation, input, hitbox registration, and combat interactions are implemented.

Development is currently focused on expanding the combat system with health and damage mechanics, controller support, and an AI-controlled opponent using Hierarchical Finite State Machines and Random Decision Trees.

## Learning Outcomes

Through this project, I am developing practical experience in:

- Gameplay programming
- Object-oriented C++ development
- Modular game architecture
- Character animation systems
- Input and control systems
- Collision and hitbox systems
- Combat mechanics
- Finite State Machine design
- Hierarchical AI architecture
- Decision-making systems
- Debugging complex gameplay interactions
- Performance-conscious programming
- Building maintainable and scalable game systems

## Disclaimer

This project is a non-commercial educational recreation developed solely for learning, research, and portfolio purposes.

The project is not affiliated with, endorsed by, or associated with Capcom in any way. All rights to the Street Fighter franchise, characters, artwork, music, and original game assets belong to Capcom.

Sprite assets and reference materials used in this project were obtained from publicly available online sources and are being used exclusively for educational and demonstration purposes. No ownership of these assets is claimed.

This repository is not intended for commercial distribution, sale, monetization, or any form of commercial use.
