<h1 align="center"> 🏷️ Tags</h1>
<p align="center">

  <img src="https://img.shields.io/badge/Custom%20Engine-8A2BE2?logo=gear&logoColor=white" alt="Custom Engine" />
  <img src="https://img.shields.io/badge/3D%20Graphics-1E90FF?logo=three.js&logoColor=white" alt="3D Graphics" />
  <img src="https://img.shields.io/badge/Gaming%20Campus-1E90FF?logo=google-earth&logoColor=white" alt="Gaming Campus" />
  <img src="https://img.shields.io/badge/Computer%20Science%20Student-808080?logo=academia&logoColor=white" alt="Student" />
  <img src="https://img.shields.io/badge/Roguelike-FF4500?logo=dungeons-and-dragons&logoColor=white" alt="Roguelike" />
  <img src="https://img.shields.io/badge/Turn--Based%20Game-2E8B57?logo=chess&logoColor=white" alt="Turn-Based Game" />

</p>

# 🎮 Endless Rogue

**Endless Rogue** est un **Roguelike RPG tour par tour** où le joueur compose une équipe de héros et tente de survivre le plus longtemps possible dans un niveau infini rempli de monstres.

---

# 📌 Game Overview

|                     |                                                                                                                                          |
| ------------------- | ---------------------------------------------------------------------------------------------------------------------------------------- |
| **Title**           | Endless Rogue                                                                                                                            |
| **Genre**           | Roguelike / RPG                                                                                                                          |
| **Platform**        | PC                                                                                                                                       |
| **Target Audience** | 12 – 50 years                                                                                                                            |
| **Pitch**           | The player chooses **4 heroes among 8 available** and upgrades them through gameplay to survive increasingly difficult waves of enemies. |

---

# 🔄 Gameplay

## Player Objectives

* Survive as long as possible in the **infinite dungeon**
* Kill monsters to gather **upgrade materials**
* Upgrade characters to **unlock abilities and improve stats**

---

## Gameplay Loop

1. Start a run
2. Fight monsters
3. Collect resources and artefacts
4. Upgrade and manage characters
5. Start a new run and go further

---

## Controls

| Input          | Action         |
| -------------- | -------------- |
| **Left Click** | Select actions |

---

# 🧙 Characters

The player chooses **4 heroes from 8 available characters**.

---

## ⚔️ Alex — DPS Fighter

### Abilities

| Level | Ability           | Cooldown | Description                               |
| ----- | ----------------- | -------- | ----------------------------------------- |
| 1     | Sword Slash       | 1 turn   | Basic melee attack                        |
| 5     | Parade            | 2 turns  | Defensive ability                         |
| 15    | Heavy Sword Slash | 2 turns  | Powerful attack                           |
| 30    | Passive           | -        | The lower Alex's HP, the higher his stats |

### Statistics

| Stat          | Base | Max |
| ------------- | ---- | --- |
| HP            | 50   | 600 |
| Attack Power  | 0    | 0   |
| Attack Damage | 10   | 400 |
| Armor         | 3    | 30  |
| Resist        | 0.5  | 10  |
| Speed         | 90   | -   |

---

## 🛡 Diane — Tank

### Abilities

| Level | Ability       | CD | Description                               |
| ----- | ------------- | -- | ----------------------------------------- |
| 1     | Shield Charge | 1  | Charge and attack                         |
| 10    | Taunt         | 2  | Forces enemies to attack Diane            |
| 25    | Shield Buff   | 3  | Shield Diane and an ally (scales with AP) |
| 40    | Passive       | -  | +20% Armor team / +30% for Diane          |

### Statistics

| Stat          | Base | Max  |
| ------------- | ---- | ---- |
| HP            | 100  | 1000 |
| Attack Power  | 20   | 200  |
| Attack Damage | 2.5  | 250  |
| Armor         | 5    | 50   |
| Resist        | 4    | 30   |
| Speed         | 100  | -    |

---

## 💚 Marcus — Support (Healer)

### Abilities

| Level | Ability      | CD | Description                   |
| ----- | ------------ | -- | ----------------------------- |
| 1     | Heal         | 1  | Medium heal to one ally       |
| 8     | Multi Heal   | 3  | Small heal to all allies      |
| 20    | Cleanse      | 2  | Removes debuffs from one ally |
| 35    | Resurrection | 8  | Revive one ally               |

### Statistics

| Stat          | Base | Max |
| ------------- | ---- | --- |
| HP            | 30   | 300 |
| Attack Power  | 30   | 300 |
| Attack Damage | 0    | 0   |
| Armor         | 0.5  | 15  |
| Resist        | 0.5  | 15  |
| Speed         | 85   | -   |

---

## 🔥 Edward — Ranged DPS Mage

### Abilities

| Level | Ability      | CD | Description                    |
| ----- | ------------ | -- | ------------------------------ |
| 1     | Ember        | 1  | Basic fire attack              |
| 10    | Fireball     | 2  | Heavy single target damage     |
| 20    | Stun Spell   | 4  | Stun target for 2 turns        |
| 36    | Magic Meteor | 6  | Huge damage + burn for 3 turns |

### Statistics

| Stat          | Base | Max |
| ------------- | ---- | --- |
| HP            | 20   | 250 |
| Attack Power  | 20   | 500 |
| Attack Damage | 0    | 0   |
| Armor         | 0.25 | 10  |
| Resist        | 0.25 | 10  |
| Speed         | 75   | -   |

---

## 🗡 Pénélope — Assassin DPS

### Abilities

| Level | Ability      | CD | Description                           |
| ----- | ------------ | -- | ------------------------------------- |
| 1     | Cut          | 1  | Basic attack                          |
| 8     | Poison       | 2  | Poison for 5 turns                    |
| 20    | Vampiric Cut | 3  | Drain 80% damage as HP                |
| 45    | Passive      | -  | Cannot be targeted if a tank is alive |

### Statistics

| Stat          | Base | Max |
| ------------- | ---- | --- |
| HP            | 25   | 300 |
| Attack Power  | 0    |  0  |
| Attack Damage | 15   | 450 |
| Armor         | 0.5  | 15  |
| Resist        | 0.1  | 20  |
| Speed         | 62.5 | -   |

---

## ✨ Claire — Support Buffer

### Abilities

| Level | Ability     | CD | Description                       |
| ----- | ----------- | -- | --------------------------------- |
| 1     | Wand Hit    | 1  | 15% chance to apply random debuff |
| 8     | Resist Buff | 3  | +5% armor/resist (stack x2)       |
| 16    | Slow        | 5  | Slow enemy for 2 turns            |
| 25    | Mega Buff   | 10 | Buff AP, AD, Speed                |

### Statistics

| Stat          | Base | Max |
| ------------- | ---- | --- |
| HP            | 30   | 400 |
| Attack Power  | 10   | 20  |
| Attack Damage | 3    | 100 |
| Armor         | 0.2  | 10  |
| Resist        | 0.4  | 10  |
| Speed         | 80   | -   |

---

## 🏹 Brutus — Ranged Archer

### Abilities

| Level | Ability         | CD | Description          |
| ----- | --------------- | -- | -------------------- |
| 1     | Triple Shot     | 1  | Shoot 3 arrows       |
| 5     | Arrow Storm     | 4  | 5–10 arrows          |
| 18    | Piercing Arrow  | 5  | Ignore 80% armor     |
| 37    | Explosive Arrow | 10 | Huge damage + splash |

### Statistics

| Stat          | Base | Max |
| ------------- | ---- | --- |
| HP            | 40   | 500 |
| Attack Power  | 8    | 325 |
| Attack Damage | 5    | 300 |
| Armor         | 0.4  | 15  |
| Resist        | 0.2  | 10  |
| Speed         | 80   | -   |

---

## 🪨 Emilie — Tank

### Abilities

| Level | Ability    | CD | Description                      |
| ----- | ---------- | -- | -------------------------------- |
| 1     | Earthquake | 1  | Low AoE damage                   |
| 6     | Share      | 4  | Share 50% resist with ally       |
| 20    | Barrier    | 2  | Reduce enemy resist              |
| 45    | Passive    | -  | Ignore first hit from each enemy |

### Statistics

| Stat          | Base | Max |
| ------------- | ---- | --- |
| HP            | 90   | 900 |
| Attack Power  | 5    | 150 |
| Attack Damage | 5    | 300 |
| Armor         | 2    | 20  |
| Resist        | 5    | 50  |
| Speed         | 85   | -   |

---

# 👾 Enemies

## Rat

**Class:** Assassin

### Abilities

| Ability                 | Cooldown | Description                                                                         |
| ----------------------- | -------- | ----------------------------------------------------------------------------------- |
| Crunch                  | 1 turn   | Low chance (10%) to debuff armor of the target                                      |
| Poisonous Bite          | 2 turns  | Poison the target                                                                   |
| Passive – Living Poison | Passive  | If the rat attacks a poisoned target, trigger the poison without reducing the timer |
| Rat Wave                | 4 turns  | Call a rat wave that bites and poisons everyone                                     |

### Statistics

| Stat          | Value |
| ------------- | ----- |
| HP            |       |
| Attack Power  |       |
| Attack Damage |       |
| Armor         |       |
| Resist        |       |
| Speed         | 95    |

### Drops

| Drop Rate | Item             | Rarity | Effect                          |
| --------- | ---------------- | ------ | ------------------------------- |
| 10%       | Tail             | C      | Heal 1% of max HP every turn    |
| 5%        | Rat Tooth        | R      | Boost poison damage by x1.2     |
| 2%        | Rattata Crane    | E      | Boost XP by 10%                 |
| 0.5%      | Rat Eye Talisman | L      | Add 1 turn to inflicted debuffs |

---

# Wolf

**Class:** DPS

### Abilities

| Ability             | Cooldown | Description                                                  |
| ------------------- | -------- | ------------------------------------------------------------ |
| Claw                | 1 turn   | Basic attack                                                 |
| Violent Bite        | 2 turns  | Strong bite attack                                           |
| Passive – Wolf Pack | Passive  | While another wolf is in the fight, improve speed and attack |
| Coordinate Attack   | 3 turns  | Every wolf attacks a target with Claw                        |

### Statistics

| Stat          | Value |
| ------------- | ----- |
| HP            |       |
| Attack Power  |       |
| Attack Damage |       |
| Armor         |       |
| Resist        |       |
| Speed         |       |

### Drops

| Drop Rate | Item        | Rarity | Effect                                                                           |
| --------- | ----------- | ------ | -------------------------------------------------------------------------------- |
| 10%       | Wolf Fur    | C      | Boost armor + resist by 1%                                                       |
| 5%        | Wolf Tooth  | R      | Improve attack by 2%                                                             |
| 2%        | Pack Aura   | E      | Boost attack and speed by 2% for every character of the same class as the wearer |
| 0.5%      | Alpha Medal | L      | Boost wearer stats by 10% for every dead ally                                    |

---

# Bear

**Class:** Tank

### Abilities

| Ability                    | Cooldown | Description                                    |
| -------------------------- | -------- | ---------------------------------------------- |
| Claw                       | 1 turn   | Basic attack                                   |
| Surprise Salmon            | 2 turns  | Heal himself by eating a salmon                |
| Passive – Territory Battle | Passive  | Attacks tank units in priority                 |
| I Am the King              | 6 turns  | Boost armor and resist by 5% and taunt 1 enemy |

### Statistics

| Stat          | Value |
| ------------- | ----- |
| HP            |       |
| Attack Power  |       |
| Attack Damage |       |
| Armor         |       |
| Resist        |       |
| Speed         |       |

### Drops

| Drop Rate | Item             | Rarity | Effect                                                     |
| --------- | ---------------- | ------ | ---------------------------------------------------------- |
| 10%       | Bear’s Foot      | C      | Heal 2% of every damage taken                              |
| 5%        | Honey            | R      | 10% chance at start of level to taunt enemies individually |
| 2%        | Bear’s Salmon    | E      | Improve healing received by 10%                            |
| 0.5%      | Great Bear Medal | L      | Fatal attack heals 20% max HP instead (5 turn CD)          |

---

# Adept of the Chaos

**Class:** DPS Mage

### Abilities

| Ability            | Cooldown | Description                                                |
| ------------------ | -------- | ---------------------------------------------------------- |
| Black Thunder      | 1 turn   | Magic attack                                               |
| Dark Orb           | 2 turns  | Attack a random enemy                                      |
| Magic Coward Coat  | 3 turns  | Lose 15% max HP to boost AP (max 3 stacks)                 |
| Rise of the Demons | 6 turns  | Charge for 1 turn then summon a demon damaging all enemies |

### Statistics

| Stat          | Value |
| ------------- | ----- |
| HP            |       |
| Attack Power  |       |
| Attack Damage |       |
| Armor         |       |
| Resist        |       |
| Speed         |       |

### Drops

| Drop Rate | Item          | Rarity | Effect                                            |
| --------- | ------------- | ------ | ------------------------------------------------- |
| 10%       | Smoke Bomb    | C      | Improve speed by 2%                               |
| 5%        | Chaotic Armor | R      | Increase critical chance by 3% (crit damage +50%) |
| 2%        | Malicious Eye | E      | 5% chance each turn to reduce all cooldowns by 1  |
| 0.5%      | Chaos Scepter | L      | 10% chance to cast an ability twice               |

---

# Ghost

**Class:** Support (Debuff)

### Abilities

| Ability                | Cooldown | Description                         |
| ---------------------- | -------- | ----------------------------------- |
| Poltergeist            | 1 turn   | Throw an object at the target       |
| Haunting               | 2 turns  | Haunt an enemy and apply a debuff   |
| Passive – Bony Spirits | Passive  | Cannot be hit by basic attacks      |
| Ghost Parade           | 6 turns  | Curse enemies and inflict 2 debuffs |

### Statistics

| Stat          | Value |
| ------------- | ----- |
| HP            |       |
| Attack Power  |       |
| Attack Damage |       |
| Armor         |       |
| Resist        |       |
| Speed         |       |

### Drops

| Drop Rate | Item                  | Rarity | Effect                                         |
| --------- | --------------------- | ------ | ---------------------------------------------- |
| 10%       | Ouija                 | C      | Increase debuff timer by 1 turn                |
| 5%        | Burning Bone          | R      | Boost burn damage x1.2                         |
| 2%        | Casper’s Encyclopedia | E      | Increase AP by 0.5% per turn (max 15%)         |
| 0.5%      | Ectoplasm             | L      | When HP < 50%, give 20% stats to allies (once) |

---

# Dark Knight

**Class:** Tank

### Abilities

| Ability                    | Cooldown | Description                                      |
| -------------------------- | -------- | ------------------------------------------------ |
| Sword Slash                | 1 turn   | Attack an enemy                                  |
| Shield Bash                | 2 turns  | Dash and smash target, grant shield to caster    |
| Passive – Last Resort Rage | Passive  | Under 25% HP: decrease defense, increase offense |
| Shadow Rush                | 6 turns  | Heavy single-target attack                       |

### Statistics

| Stat          | Value |
| ------------- | ----- |
| HP            |       |
| Attack Power  |       |
| Attack Damage |       |
| Armor         |       |
| Resist        |       |
| Speed         |       |

### Drops

| Drop Rate | Item            | Rarity | Effect                                                       |
| --------- | --------------- | ------ | ------------------------------------------------------------ |
| 10%       | Knight’s Badge  | C      | Improve generated shield by 5%                               |
| 5%        | Knight’s Helmet | R      | Increase offensive stats under 30% HP (+3%)                  |
| 2%        | Cursed Shield   | E      | Lose 2% HP per turn but deal 2% max HP damage to enemies hit |
| 0.5%      | Dark Sword      | L      | Each enemy slain increases AD by 5% (max 15%)                |

---

# Bosses

---

# Runic Deer

**Class:** Boss

### Abilities

| Ability                    | Cooldown | Description                                        |
| -------------------------- | -------- | -------------------------------------------------- |
| Horn Leech                 | 1 turn   | Attack with antlers                                |
| Savage Root                | 2 turns  | Hit target and random enemy, apply slow            |
| Passive – Forest King Aura | Passive  | Each turn increase defensive stats by 5% (max 15%) |
| Green Ruler’s Wrath        | 6 turns  | Hit every enemy                                    |

### Statistics

| Stat          | Value |
| ------------- | ----- |
| HP            |       |
| Attack Power  |       |
| Attack Damage |       |
| Armor         |       |
| Resist        |       |
| Speed         |       |

### Drops

| Drop Rate | Item            | Rarity | Effect                                                       |
| --------- | --------------- | ------ | ------------------------------------------------------------ |
| 0.5%      | Forest Rune     | L      | When an ally receives healing, heal the lowest HP ally (15%) |
| 0.1%      | Ruler’s Antlers | L      | Each turn increase stats by 3% (max 18%)                     |

---

# Red Dragon

**Class:** Boss

### Abilities

| Ability        | Cooldown | Description                                                 |
| -------------- | -------- | ----------------------------------------------------------- |
| Tail Smash     | 1 turn   | Hit an enemy and apply slow                                 |
| Hate Flame     | 2 turns  | Damage an enemy, increased if caster has a debuff           |
| Hell Territory | Passive  | At start of each turn deal damage to characters for 3 turns |
| Grand Fire     | 6 turns  | Hit all enemies and decrease offensive stats                |

### Statistics

| Stat          | Value |
| ------------- | ----- |
| HP            |       |
| Attack Power  |       |
| Attack Damage |       |
| Armor         |       |
| Resist        |       |
| Speed         |       |

### Drops

| Drop Rate | Item                  | Rarity | Effect                                                 |
| --------- | --------------------- | ------ | ------------------------------------------------------ |
| 0.5%      | Scale of the Red King | L      | When damaged, reflect 5–10% damage to enemy team       |
| 0.5%      | Eternal Flame         | L      | 20% chance to burn target on single-target contact hit |

---

# 🌍 Universe / Level Design

### Environments

* Volcano

---

# 🎨 Artistic Direction

|           |          |
| --------- | -------- |
| **Style** | Low Poly |

### Inspirations

* Raid Shadow Legends
* Clair Obscur Expedition 33
* Pokémon
* Summoners War
* Rogue
* Archero
* Orna

---

# 🖥 Interface (UI)

### HUD

* Character & Enemy **HP Bars**
* **Turn Order**
* **Level Number**
* **Ability Selection**
* **Fight Log**

### Screens

* Menu
* Lobby
* Death Screen

---

# 🔊 Audio

### Music

* Dynamic combat music
* Epic boss music

### SFX

* Metal sounds
* Magic spells
* Button clicks
* Buff sounds
* Enemy ambient sounds
* Death sounds
* Lava sounds
* Level-up sound

---

# 🎲 Roguelike System

When the **XP bar is full**, the player chooses **1 bonus among 3**.

### Rarity System

* Common
* Rare
* Epic
* Legendary

---

## Examples of Common Bonuses

* Heal **10% HP** for all characters
* Heal **20% HP** for one character
* **+10% Max HP**
* **+10% AP or AD**
* **+10% Armor / Resist**
* **+10% Speed**
* **+7% stats for one class**
* **+10% gear drop chance**

---

## Legendary Bonuses (Examples)

* **Life Reaper** → Heal 50% HP on kill
* **Battle Start Heal** → Heal 10% at start of fight
* **Counter Attack** → 30% chance (50% damage)
* **Second Chance** → Survive first death with 1 HP
* **Extra Turn** → 15% chance
* **Collateral Damage** → 20% chance to hit another enemy

---
