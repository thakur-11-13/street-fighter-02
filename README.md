# Street Fighter II Recreation (C++ / SFML)

<p align="center">
  <b>A 2D fighting game built from scratch in C++ and SFML, with no game engine.</b>
</p>

<p align="center">
  <a href="https://drive.google.com/file/d/1vPtcj7CI7zcAfuPUd1NIYvbD8SOHr29r/view?usp=sharing">
    <img src="https://img.shields.io/badge/%E2%96%B6%20%20WATCH%20THE%20GAMEPLAY%20PREVIEW-E50914?style=for-the-badge&logo=googledrive&logoColor=white" alt="Watch the gameplay preview" height="48">
  </a>
</p>

<p align="center">
  <i>Running the project requires a local SFML setup, so the preview video above shows the game in action.</i>
</p>

<p align="center">
  <img src="https://img.shields.io/badge/C%2B%2B-00599C?style=flat-square&logo=cplusplus&logoColor=white" alt="C++">
  <img src="https://img.shields.io/badge/SFML-8CC445?style=flat-square" alt="SFML">
  <img src="https://img.shields.io/badge/Visual%20Studio%202022-5C2D91?style=flat-square&logo=visualstudio&logoColor=white" alt="Visual Studio 2022">
  <img src="https://img.shields.io/badge/Status-Active%20Development-orange?style=flat-square" alt="Status: Active Development">
</p>

---

## Table of Contents

- [Overview](#overview)
- [Project at a Glance](#project-at-a-glance)
- [Highlights](#highlights)
- [Implemented Features](#implemented-features)
- [Architecture](#architecture)
  - [Game Loop and Timing](#game-loop-and-timing)
  - [Input System](#input-system)
  - [Animation and Character State](#animation-and-character-state)
  - [Collision and Combat](#collision-and-combat)
  - [Character Balance](#character-balance)
- [In Development](#in-development)
- [Engineering Challenges](#engineering-challenges)
- [Tech Stack](#tech-stack)
- [Roadmap](#roadmap)
- [Disclaimer](#disclaimer)

---

## Overview

This project recreates the 1991 arcade classic *Street Fighter II* **entirely from scratch** in C++ with SFML, without Unity, Unreal, or any other game engine.

The goal is to understand how fighting games work internally. Every core system, including the game loop, input handling, animation, hitbox collision, combat resolution, and AI, is designed and implemented independently rather than taken from an engine. Fighting games are unforgiving: players notice a dropped input or a small timing error immediately. That makes them a demanding test of gameplay architecture, timing, and state management.

The game currently features two playable characters, **Chun-Li** and **Ryu**, who can fight each other using the full set of implemented moves.

## Project at a Glance

| | |
|---|---|
| **Language** | C++ |
| **Library** | SFML (no game engine) |
| **Codebase** | 31 classes, 2800+ lines of code |
| **Development history** | 155+ commits over 4+ months |
| **Playable characters** | 2 (Chun-Li and Ryu) |
| **Implemented actions** | 16 per character |
| **IDE** | Visual Studio 2022 |

## Highlights

| | |
|---|---|
| **No engine** | Every system is hand-written in C++ on top of SFML's windowing, rendering, and input layer |
| **Decoupled game loop** | Input is polled on every iteration of an uncapped loop, while animation advances at fixed intervals, so timing is identical on weak and strong PCs |
| **Input-responsive animation** | The animation timer resets on player input so actions appear on the first frame after the input, with no wait for the next tick |
| **Anti-spam input rule** | An attack key must be released before the next attack can be triggered, so attacks cannot be spammed by holding or mashing a key |
| **Hitbox-based combat** | Attack-to-character collision, hit detection between characters, and separate reactions for clean hits and blocked hits |
| **Balanced characters** | Attacks of equal strength take roughly the same time on both characters, so neither has a speed advantage |
| **Modular OOP design** | Input, animation, collision, combat, and game state are separate systems built across 31 classes |
| **Opponent AI (in progress)** | A Hierarchical Finite State Machine combined with Random Decision Trees |

---

## Implemented Features

Both characters can currently interact with each other, perform attacks, register hits through hitboxes, and trigger the matching hit animations.

### Movement

| Action | Status |
|---|---|
| Walk forward | Implemented |
| Walk backward | Implemented |
| Neutral jump | Implemented |
| Jump forward | Implemented |
| Jump backward | Implemented |

### Attacks

| Type | Light | Medium | Heavy |
|---|---|---|---|
| **Punch** | Implemented | Implemented | Implemented |
| **Kick** | Implemented | Implemented | Implemented |

### Defensive and Crouching Actions

| Action | Status |
|---|---|
| Standing block | Implemented |
| Crouch | Implemented |
| Crouching block | Implemented |
| Crouching punch | Implemented |
| Crouching kick | Implemented |

### Combat Systems

- Character hitbox registration
- Attack-to-character collision detection
- Hit detection between characters
- Hit animation triggering, with a separate animation for blocked hits
- Character-to-character interaction
- Attack state handling
- Animation state management

---

### Game Loop and Timing

The loop is built around one rule: **responsiveness and consistency are separate problems, so they run on separate clocks.**

- **Uncapped main loop.** The loop runs as fast as the machine allows, and input is polled on **every iteration**. Because polling is never tied to the animation rate, a player's input is not missed because it landed between two ticks.
- **Fixed-interval animation.** Animation advances at fixed time intervals that do not depend on hardware: **5 ms per update for Chun-Li and 7.5 ms per update for Ryu**. A fast PC and a slow PC produce the same animation speed and the same attack timing.
- **Input-triggered animation reset.** Between inputs, animation advances at its fixed pace. When a new input is detected, the animation clock is reset, so the character's response starts on the first frame after the input instead of waiting for the next scheduled tick. This hides the fixed update cadence from the player and keeps controls feeling immediate.

This design makes the game both **consistent** (the same on every machine) and **responsive** (no input is lost or delayed), the two properties a fighting game depends on most.

### Input System

- Input is read every loop iteration and is decoupled from the animation tick.
- **Attack spam is prevented at the input level.** After an attack key is pressed, it must be released before another attack can be triggered. Holding a key or mashing it cannot chain attacks faster than intended.

### Animation and Character State

- Each character is driven by an **animation state machine**. Idle, walking, jumping, crouching, blocking, attacking, and being hit are distinct states.
- Explicit state handling keeps animation, input, and combat logic in agreement and controls which animation plays at any moment.
- Each character has its own animation timing, which is tuned so that gameplay stays fair (see [Character Balance](#character-balance)).

### Collision and Combat

- Characters and attacks use **hitboxes** for collision detection.
- **Attack-to-character collision** checks whether an attack's hitbox overlaps the opposing character.
- On a successful hit, the defender is moved into a **hit state**, which triggers the matching hit animation.
- **Blocked hits are handled separately.** A blocked attack plays its own hit animation, distinct from the one for a clean hit, because blocked attacks are designed to cause less damage.
- Standing and crouching blocks are separate defensive states.

### Character Balance

Chun-Li and Ryu animate at different update intervals (5 ms and 7.5 ms), but attack timing is tuned so that **attacks of the same strength take roughly the same time on both characters**. A heavy punch from one character is not faster than a heavy punch from the other, so neither character has a built-in speed advantage. This was verified through hands-on testing, and the timings are tuned by feel rather than formally measured.

---

## In Development

The following systems are **currently being built**:

### Health and Damage System

A health and damage system **is being implemented** to connect successful hits to actual character damage and to drive match progression. Clean hits will deal full damage, while blocked hits, which already have their own animation, will deal reduced damage.

### Controller Support

Gamepad controller support **is coming soon**.

### Opponent AI

The opponent AI **is being developed** to make context-dependent combat decisions rather than replaying a fixed sequence of actions. It combines two techniques:

- **Hierarchical Finite State Machine (HFSM)** provides the high-level behavioural structure. Broad modes contain their own sub-states, which keeps behaviour organised and easy to extend as the opponent grows more complex.
- **Random Decision Trees** are being used inside those states to drive moment-to-moment combat decisions and action selection. Weighted randomness is intended to keep the opponent from becoming predictable while it still responds sensibly to the situation.

The aim is an opponent that reads the situation and varies its choices, built from structures that stay readable and tunable.

---

## Engineering Challenges

Problems this project has required me to work through:

- **Hardware-independent timing without losing responsiveness.** A plain fixed timestep delays input, and a plain variable timestep makes gameplay differ between machines. The decoupled loop with an input-triggered animation reset came out of this tension.
- **Cross-system interactions.** Input, movement, animation, collision, and state transitions all depend on each other. Many bugs appeared only when two systems interacted, so debugging meant tracing a problem across systems rather than inside one.
- **State correctness.** Fighting games have many overlapping states, such as attacking, crouching, blocking, and being hit. Defining and enforcing valid transitions is necessary to avoid contradictory character states.
- **Fair timing between characters.** Two characters with different animation intervals had to be tuned so equal-strength attacks take roughly the same time.
- **Maintainable architecture.** Keeping 31 classes modular so that new features (health, controller input, AI) can be added without destabilising what already works.

---

## Tech Stack

| Category | Tools |
|---|---|
| Language | C++ |
| Library | SFML (Simple and Fast Multimedia Library) |
| IDE | Visual Studio 2022 |
| Version control | Git / GitHub |

**Concepts applied:** object-oriented design, modular architecture, game loop design, fixed-interval animation timing, animation state machines, hitbox collision detection, finite state machines, hierarchical state machines, decision trees for game AI, and memory- and performance-conscious programming.

---

## Roadmap

- [x] Character movement (walk, jump variants)
- [x] Punch and kick attacks (light / medium / heavy)
- [x] Crouching and blocking
- [x] Hitbox registration and attack collision
- [x] Hit reactions, including blocked-hit animations
- [x] Animation state management
- [ ] Health and damage system *(in progress)*
- [ ] Opponent AI with HFSM and Random Decision Trees *(in progress)*
- [ ] Gamepad controller support *(coming soon)*

---

## Disclaimer

This project is a non-commercial educational recreation developed solely for learning, research, and portfolio purposes.

It is not affiliated with, endorsed by, or associated with Capcom in any way. All rights to the Street Fighter franchise, characters, artwork, music, and original game assets belong to Capcom.

Sprite assets and reference materials were obtained from publicly available online sources and are used exclusively for educational and demonstration purposes. No ownership of these assets is claimed.

This repository is not intended for commercial distribution, sale, monetization, or any form of commercial use.
