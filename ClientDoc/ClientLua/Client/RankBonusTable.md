`RankBonusTable.cpp` 文件是一个用于管理游戏中排名奖励的实现。以下是该文件的主要功能和结构概述：

### 主要功能

1. **排名奖励信息**：
   - `RankBonusInfo` 类用于存储每个排名奖励的相关信息，包括类型、级别、种族、技能图标 ID、状态和点数。

2. **从文件加载和保存**：
   - `LoadFromFile` 和 `SaveToFile` 方法用于从文件中加载和保存排名奖励信息。

3. **全局实例**：
   - `g_pRankBonusTable` 是一个全局指针，指向 `RankBonusTable` 的实例，方便在其他地方访问。

4. **初始化排名奖励**：
   - `RankBonusTable` 类在构造函数中初始化多个排名奖励的技能图标 ID，分别针对不同的种族（如 Slayer 和 Vampire）。

### 主要类和方法

#### RankBonusInfo

- **构造函数**：
  ```cpp
  RankBonusInfo::RankBonusInfo()
  ```

- **加载和保存方法**：
  ```cpp
  void LoadFromFile(class ifstream& file);
  void SaveToFile(class ofstream& file);
  ```

#### RankBonusTable

- **构造函数**：
  ```cpp
  RankBonusTable::RankBonusTable()
  ```

- **初始化技能图标**：
  - 在构造函数中，通过 `Get` 方法为每个排名奖励设置技能图标 ID。

### 示例代码片段

以下是一些设置技能图标的示例代码：

```cpp
// Slayer Rank Bonus Skill
Get(RANK_BONUS_DEADLY_SPEAR).SetSkillIconID(177);
Get(RANK_BONUS_BEHEMOTH_ARMOR).SetSkillIconID(178);
```

### 总结

`RankBonusTable.cpp` 文件负责管理游戏中排名奖励的逻辑，包括加载、保存和初始化奖励信息。通过定义 `RankBonusInfo` 和 `RankBonusTable` 类，开发者可以方便地处理不同种族的排名奖励，确保游戏的平衡性和可玩性。