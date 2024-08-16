`TempInformation.h` 文件定义了一个用于管理临时信息的类 `TempInformation`，包括多种状态模式（`TEMP_MODE`）和相关的成员变量。以下是该文件的主要功能和结构概述：

### 主要功能

1. **状态模式管理**：
   - `TempInformation` 类使用枚举类型 `TEMP_MODE` 定义了多种模式，用于表示不同的操作状态（如技能学习、商店购买、交易等）。

2. **全局实例**：
   - 提供一个全局指针 `g_pTempInformation`，方便在其他文件中访问 `TempInformation` 的实例。

### 主要类和方法

#### TempInformation

- **构造函数和析构函数**：
  ```cpp
  TempInformation();
  ~TempInformation();
  ```

- **设置模式**：
  ```cpp
  void SetMode(TEMP_MODE mode);
  ```

- **获取模式**：
  ```cpp
  const TEMP_MODE GetMode() const;
  ```

- **成员变量**：
  - `TEMP_MODE Mode`：当前模式。
  - `int Value1, Value2, Value3, Value4`：用于存储附加的整数值。
  - `int PartyInviter`：用于处理派对邀请的标识符。
  - `void* pValue`：指向其他数据的指针。

### TEMP_MODE 枚举

`TEMP_MODE` 枚举定义了多种模式，涵盖了游戏中的不同操作，例如：

- **技能学习**：
  ```cpp
  MODE_SKILL_LEARN, // (domainType, maxLevel, skillType)
  ```

- **商店操作**：
  ```cpp
  MODE_SHOP_BUY, // (shelfType, index, x, y, MShop*)
  MODE_SHOP_SELL, // (MItem*)
  ```

- **交易相关**：
  ```cpp
  MODE_TRADE_REQUEST, // (ID)
  ```

- **其他操作**：
  ```cpp
  MODE_NICKNAME_CHANGE_CUSTOM, // 自定义昵称修改
  ```

### 示例代码片段

以下是 `SetMode` 方法的实现，展示了如何设置当前模式：

```cpp
void TempInformation::SetMode(TempInformation::TEMP_MODE mode) {
#ifdef OUTPUT_DEBUG
	// DEBUG_ADD_FORMAT("[TempInformation] Setmode : %d", mode);
#endif

	Mode = mode;
}
```

### 总结

`TempInformation.h` 文件定义了一个用于管理临时信息的类，提供了多种操作模式和相关的状态管理功能。该类的设计使得在游戏或应用程序中能够轻松管理和跟踪不同的操作状态，便于实现复杂的游戏逻辑和用户交互。