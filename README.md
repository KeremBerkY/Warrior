# Warrior

Developed with Unreal Engine 5

# ⚔️ Unreal Engine 5 C++ Combat RPG

> **Platform:** Unreal Engine 5.3.2
> **Language:** C++
> **Duration:** 2.5 - 3 Months
> **Developer:** Solo Project

---

## 🌟 Project Purpose

This project is an advanced action RPG system built with C++ in Unreal Engine 5. The goal is to create a modular, extensible, and multiplayer-ready combat infrastructure using the **Gameplay Ability System (GAS)**. The system integrates Lyra-based movement, AI, UI, DataAssets, and asynchronous loading systems.

---

## 🔧 Technical Details

### 🚀 Systems Used

#### Gameplay Ability System (GAS):

* Attribute modifications
* Ability grant/remove
* Gameplay Effect application
* Input-driven attack chains

#### Combat System:

* Light and heavy melee attacks
* Combo system with input buffering
* Directional hit reaction, rolling, blocking, and parrying
* Rage abilities with cooldown and cost systems

#### Lyra Movement:

* Root motion-based combat animations
* Layered movement architecture

#### AI and Behaviour Tree:

* Custom `BTTask`, `BTService`, `BTTDecorator`
* Positioning via EQS (Environment Query System)
* Decision-making supported by Blackboard and UI health bars

#### UI System:

* Dynamic attribute bars (health, mana, stamina) via GAS
* Cooldown indicators and input feedback

#### Data and Loading:

* Weapon and ability definitions via `UPrimaryDataAsset`
* Async loading for performant data management

#### Code Architecture:

* Component-based system (WeaponManager, Combo, Input)
* Clean architecture and event-driven systems (delegates, notifies)

---

## 📙 Learned and Applied Techniques

* GAS-based melee combat (light/heavy attacks)
* AI control via BTTask, BTService, BTTDecorator
* EQS-based positioning logic
* Custom ability tasks and latent actions in C++
* Melee defense mechanics: block, parry, roll
* Rage mechanics with cost and cooldown control
* Directional hit reaction and root motion usage
* Lock-on target system
* Wave-based enemy spawner (survival mode)
* Menu system: main, pause, win/lose, loading
* Async/sync load in both Blueprint and C++
* Modular, scalable, production-quality codebase

---

## 🌐 Multiplayer-Ready Architecture

While the project is designed for single-player gameplay, its **GAS architecture is replication-based**, making it naturally extensible to **co-op multiplayer** gameplay.

* Attributes (e.g., health, stamina) are replication-friendly
* Gameplay Effects and Abilities are replication-aware
* Combat, input, and movement systems are built with server-authority logic

As a result, combat, effects, and input synchronization can be easily transitioned into multiplayer gameplay.

---

## 🧠 Design Patterns Used

* **Component Pattern:** Modular separation for weapon, ability, and combat systems
* **Strategy Pattern:** Different ability classes for light/heavy attack logic
* **State Pattern:** Manages combo sequences and animation transitions
* **Factory-like Pattern:** Weapons and abilities instantiated via DataAssets

---

## 📊 Class Structure (FlowChart images will be added later)

* `WarriorBaseGameMode`: Controls the overall game flow
* `WarriorBaseCharacter`: Base character class with shared logic
* `WarriorHeroCharacter`: Player-controlled character
* `WarriorEnemyCharacter`: AI enemy character
* `WarriorHeroController`: Player controller class

---

## 🎥 Demo Video

Watch the gameplay demo here:  
👉 [Gameplay Ability System (GAS) RPG Combat | UE5 + C++ Project](https://youtu.be/Ufm-yTSwv-Y)

---

## 🔍 Installation & Usage

### Requirements:

* Unreal Engine 5.3.2
* Motion Warping (plugin)
* Enhanced Input (plugin)
* Gameplay Tasks (plugin)
* Environment Query System (EQS plugin)

### Setup Instructions:

1. Clone the repository:

```bash
git clone https://github.com/KeremBerkY/Warrior.git
```

2. Open the `.uproject` file
3. Use the "Generate Visual Studio project files" option
4. Compile and press `Play` in the editor

---

## 🚀 Ideal Use Cases

* Developers building a GAS-based action RPG system
* Projects aiming to integrate Lyra movement and root motion combat
* Unreal Engine developers designing multiplayer-ready systems

---

## ⚠️ License & Usage

This project is shared for portfolio purposes only. Not intended for commercial use.
