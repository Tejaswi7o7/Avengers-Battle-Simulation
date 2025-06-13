# Avengers Battle Simulation

## Project Overview
**Background Story**  
The Avengers are gearing up for another intergalactic battle. Tony Stark has developed Quantum Nanotech Suits (QNS) that dynamically adapt and upgrade based on battlefield conditions. These suits enable Avengers to maximize their chances of victory by:  
- Absorbing energy from attacks to upgrade their power.  
- Reinforcing armor dynamically to increase durability.  
- Overclocking power systems for high-damage attacks.

However, there are limitations: excessive upgrades can cause overheating, which may render the suit unusable. 
## Description
Developed a dynamic battle simulation system where Avengers equip and use Quantum Nanotech Suits (QNS), each having real-time attributes such as power level, durability, energy capacity, and thermal heat. The system manages battle interactions, overheating logic, and suit upgrades.  
## Key Features
- **OOP-Based Design**: Implemented core classes including `QuantumSuit`, `Avenger`, and `BattleSimulator` to model suit behavior and battle dynamics.
- **Suit Management**:  
  - Maintained a list of suits with mutable properties like power, durability, energy, and heat.
  - Incorporated dynamic upgrades and degradation of suits during battles.
- **Avenger Assignment**: Automatically or manually assigned suits to Avengers based on suitability and availability.
- **Battle Simulation Engine**:  
  - Simulated realistic combat events where Avengers engage enemies.  
  - Tracked and updated suit status in real time (e.g., power drain, energy usage, overheating).  
  - Prevented overheating by applying constraints and cooldown logic.  
- **Battle Logging**:  
  - Maintained an event log of all actions (e.g., attacks, suit upgrades, failures).  
  - Logged overheating events and recovery time.  
- **Edge Case Handling**:
  - Handled cases such as suit re-assignment on failure, maximum heat thresholds, energy depletion, and duplicate suit assignments.
## Class Definitions
1. **`QNS (Quantum Nanotech Suit)`**  
  Represents a dynamic battle suit that upgrades in real time. By default we will consider the suit format as (P,D,E,H).

**Attributes**:
- `powerLevel` (private, `int`): The suit’s attack strength. Default val:1000, represented as P
- `durability` (private, `int`): Armor strength against attacks. Default val: 500 , represented as D.
- `energyStorage` (private, `int`): Stores absorbed energy from enemy attacks. Default val:300, Represented as E
- `heatLevel` (private, `int`): Increases with overuse; if too high, the suit shuts down. Default val:0, Represented as H.
  
**Methods**:
  1. Constructors:
     - Parameterized Constructor: Initializes `powerLevel`, `durability`, `energyStorage`, and `heatLevel`.
     - Copy Constructor: Duplicates another QNS instance.
     - Default Constructor: Initializes all attributes with safe defaults .
  2. Operator Overloading:
     * `+` : Upgrades suit → (P1 + E2, D1 + D2, E1 + P2, H1)
     * `-` : Damage → (P, D - X, E + X, H + X)
     * `*` : Boost → (P + P\*X/100, D, E + 5X, H + X)
     * `/` : Cool down → (P, D + X, E, max(H - X, 0))
  3. Function Overloading:
     - `void boostPower(int factor)`: Boosts(add) power, but increases overheating risk i.e. increases heat  This method returns void.  
     - `void boostPower(QNS otherSuit)`: Transfers energy from another suit to boost durability. This method returns void. 
  4. Comparison Overloading:
     - bool Equality (==): Compares suits based on  `powerLevel` and `durability`. If both are the same returns true, else return false.
     - bool Less Than (<): Compares suit effectiveness in battles. If sum of suit1 power and durability is lesser than other return true else returns false.
         
**Constraints**:  
  - `heatLevel > 500` → Overheated
  - `durability <= 0` → Destroyed
  - `powerLevel > 5000` → Cap at 5000
---
2. **`Avenger`**  
   Represents an Avenger equipped with a Quantum Suit.
   
**Attributes**:
- `name` (private, `string`): The Avenger’s name (e.g., "Iron Man", "Thor").
- `suit` (private, `QNS`): The quantum suit they wear.By default suit will be assigned on First Come First Serve basis. 
- `attackStrength` (private, `int`): Determines (battle efficiency) the amount of damage this avenger can make to an opponent.
  
**Methods**:
  - `Avenger(string avName, QNS avSuit, int strength)`: For assigning the values to the attribute.  
  - `void attack(Avenger& enemy)`: Damages the enemy’s durability by a factor of <Avenger_attackStrength>.
  - `void upgradeSuit()`:If any extra suit is left out, transfer power to their suit in First come First serve order from the extra suit and it can't be further used.
  - `void repair(int x)`: Restores some durability to their suit by cooling down the suit by factor x.
  - `printStatus()`: Displays the Avenger’s suit details in the format `“<Avenger_Name> <P> <D> <E> <H>”`.

**Constraints:**
* Overheated → cannot fight
* Destroyed → out of battle
* No suit → print: `X is out of fight`
---
3. **`Battle`**
   Simulates battles between Avengers and enemies.

**Attributes**:  
* `heroes`: Vector of Avenger (size n)
* `enemies`: Vector of Avenger (size m)
* `battleLog`: Vector of strings

**Logged Events**:  
* `"A attacks B"`
* `"B suit destroyed"` if D <= 0
* `"B suit overheated"` if H > 500
* `"X boosted"` → `"X suit overheated"` if H > 500
* `"X upgraded"` or `"X upgrade Fail"`
* `"X repaired"`

**Methods**:  
- `startBattle()`: Runs the battle simulation. It is the flag to start the battle.  
- `printBattleLog()`: Shows battle history.    
- `int Result()`: sums the Power and durability of all heroes currently in battle and similarly sums the power and durability of all the enemies currently in battle and if the sum of avenger is > sum of enemies then return 1, if the enemies are winning return -1, otherwise return 0 incase of a tie.

## Input Format
1. The first line contains three integers: `k`, `n`, and `m`, where:
   - `k` is the number of Quantum Nanotech Suits,
   - `n` is the number of heroes (Avengers),
   - `m` is the number of enemies.
   - It is guaranteed that `k > 0`, `n > 0`, and `m > 0`
2. The next `k` lines each describe a suit in the format:
`P D E H`  
where:
- `P` is the power level,
- `D` is durability,
- `E` is energy storage,
- `H` is the heat level.
3. After initialization, a series of commands are input until the `"End"` command is encountered:
- `BattleBegin`: Starts the battle.
- `Attack <Avenger1> <Avenger2>`: Makes Avenger1 attack Avenger2.
- `Repair <AvengerName> x`: Repairs the suit’s durability by x units.
- `BoostPowerByFactor <AvengerName> y`: Multiplies the suit's power by a factor of y.
- `BoostPower <AvengerName> <P> <D> <E> <H>`: Transfers stats from a new temporary suit to the existing one.
- `AvengerStatus <AvengerName>`: Prints the current status of the Avenger's suit.
- `Upgrade <AvengerName>`: If extra suits are available, upgrades the Avenger’s current suit.
- `PrintBattleLog`: Displays the chronological log of all battle events.
- `BattleStatus`: Prints the outcome of the battle as:
  - `"heroes are winning"` if `Battle.Result() == 1`,
  - `"enemies are winning"` if `Battle.Result() == -1`,
  - `"tie"` if `Battle.Result() == 0`.

## Output Format
1. During initialization:  
If an Avenger cannot be assigned a suit, output:  
    `<Name> is out of fight`
2. For each command:
  - `AvengerStatus`: Outputs the current stats (power, durability, energy, heat) of the specified Avenger's suit.
  - `PrintBattleLog`: Outputs all logged battle events in the order they occurred.
  - `BattleStatus`: Outputs one of:
    - `heroes are winning`
    - `enemies are winning`
    - `tie`
