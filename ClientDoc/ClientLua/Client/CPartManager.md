将 `CPartManager` 类转换为 Cocos2d-x Lua 代码，保留中文注释如下：

```lua
-- CPartManager.lua

local CPartManager = {}
CPartManager.__index = CPartManager

function CPartManager:new()
    local instance = {
        m_nIndex = 0,                   -- 整体 index 个数
        m_pPartIndex = {},              -- Part 相关的 index

        m_nPart = 0,                    -- Part 的个数
        m_nPartUsed = 0,                -- 已使用的 Part 的个数
        m_pData = {},                   -- 实际数据
        m_pParentIndex = {},            -- 原始 index
        m_pLastTime = {},               -- 最终使用时间

        m_listLRU = {},                 -- LRU 列表
        m_IndexNULL = 0xFFFFFFFF,       -- index NULL 值
        m_PartIndexNULL = 0xFFFFFFFF,   -- part index NULL 值

        m_Counter = 0                   -- 计数器
    }
    setmetatable(instance, CPartManager)
    return instance
end

function CPartManager:Init(maxIndex, maxPart)
    self:Release()

    -- 部分不能大于整体
    if maxPart > maxIndex then
        maxPart = maxIndex
    end

    self.m_nIndex = maxIndex
    self.m_pPartIndex = {}
    for i = 1, self.m_nIndex do
        self.m_pPartIndex[i] = self.m_PartIndexNULL
    end

    self.m_nPart = maxPart
    self.m_nPartUsed = 0
    self.m_pData = {}
    self.m_pParentIndex = {}
    self.m_pLastTime = {}

    for i = 1, self.m_nPart do
        self.m_pData[i] = nil
        self.m_pParentIndex[i] = self.IndexNULL
        self.m_pLastTime[i] = 0
    end

    self.m_Counter = 0
end

function CPartManager:Release()
    self.m_pPartIndex = nil
    self.m_nIndex = 0

    self.m_pData = nil
    self.m_nPart = 0
    self.m_nPartUsed = 0

    self.m_pParentIndex = nil
    self.m_pLastTime = nil

    self.m_listLRU = {}
end

function CPartManager:IsDataNULL(index)
    return self.m_pPartIndex[index] == self.m_PartIndexNULL
end

function CPartManager:IsDataNotNULL(index)
    return self.m_pPartIndex[index] ~= self.m_PartIndexNULL
end

function CPartManager:SetData(index, data)
    local newPartIndex = self:GetLRU()

    -- 原来的数据移除
    local oldIndex = self.m_pParentIndex[newPartIndex]
    if oldIndex ~= self.IndexNULL then
        self.m_pPartIndex[oldIndex] = self.m_PartIndexNULL
        self.m_pParentIndex[newPartIndex] = self.IndexNULL
    end

    -- 新数据生成
    self.m_pPartIndex[index] = newPartIndex
    self.m_pParentIndex[newPartIndex] = index
    self.m_pData[newPartIndex] = data
    self.m_pLastTime[newPartIndex] = self.m_Counter

    -- 更新 LRU 列表
    table.insert(self.m_listLRU, 1, newPartIndex)

    -- 使用的个数增加
    if self.m_nPartUsed < self.m_nPart then 
        self.m_nPartUsed = self.m_nPartUsed + 1
    end
end

function CPartManager:GetData(index)
    local partIndex = self.m_pPartIndex[index]

    -- 如果没有使用中的数据，返回 nil
    if partIndex == self.m_PartIndexNULL then
        return nil
    end

    -- 更新使用时间
    self.m_pLastTime[partIndex] = self.m_Counter
    self.m_Counter = self.m_Counter + 1

    -- 更新 LRU 列表
    for i, v in ipairs(self.m_listLRU) do
        if v == partIndex then
            table.remove(self.m_listLRU, i)
            break
        end
    end
    table.insert(self.m_listLRU, 1, partIndex)

    return self.m_pData[partIndex]
end

function CPartManager:GetLRU()
    if self.m_nPartUsed < self.m_nPart then
        return self.m_nPartUsed + 1
    end

    return self.m_listLRU[#self.m_listLRU]
end

return CPartManager
```

### 说明：
1. **类结构**：使用 Lua 的表和元表模拟类的结构。
2. **内存管理**：Lua 自动管理内存，因此不需要手动释放内存。
3. **LRU 列表**：用 Lua 的表实现 LRU 列表，使用 `table.insert` 和 `table.remove` 来管理。
4. **方法实现**：尽量保留原有的逻辑和功能，同时适应 Lua 的语法和特性。

请根据需要进行调整和测试。




好的，下面是对 `CPartManager` 类的详细解析：

### 1. 类的目的
`CPartManager` 类用于管理部分数据的内存使用，采用了部分索引（PartIndex）来优化内存分配，主要用于在内存有限的情况下有效管理大量数据。

### 2. 数据结构
- **IndexType**: 表示整体索引的类型。
- **PartIndexType**: 表示部分索引的类型。
- **DataType**: 表示实际数据的类型。

### 3. 成员变量
- `m_nIndex`: 整体索引的数量。
- `m_pPartIndex`: 存储每个整体索引对应的部分索引。
- `m_nPart`: 部分的数量。
- `m_nPartUsed`: 已使用的部分数量。
- `m_pData`: 存储实际数据的数组。
- `m_pParentIndex`: 存储原始索引的数组。
- `m_pLastTime`: 存储最后使用时间的数组。
- `m_listLRU`: 用于管理最近最少使用（LRU）部分的列表。
- `m_IndexNULL` 和 `m_PartIndexNULL`: 用于表示无效索引的常量。
- `m_Counter`: 用于计数的变量。

### 4. 主要方法
- **构造与析构**:
  - `CPartManager()`: 初始化成员变量。
  - `~CPartManager()`: 释放资源。

- **初始化与释放**:
  - `Init(maxIndex, maxPart)`: 初始化管理器，分配内存。
  - `Release()`: 释放分配的内存。

- **数据检查**:
  - `IsDataNULL(index)`: 检查指定索引的数据是否为空。
  - `IsDataNotNULL(index)`: 检查指定索引的数据是否存在。

- **数据设置与获取**:
  - `SetData(index, data)`: 设置指定索引的数据，如果已有数据则替换。
  - `GetData(index)`: 获取指定索引的数据，如果没有则返回 `nil`。

- **LRU管理**:
  - `GetLRU()`: 获取最近最少使用的部分索引。

### 5. LRU策略
- 使用一个双向链表（`m_listLRU`）来维护使用顺序。
- 每次访问或设置数据时，更新该数据的使用时间，并在 LRU 列表中调整其位置。
- 当需要替换数据时，使用 LRU 策略移除最久未使用的数据。

### 6. 代码示例
下面是一些具体的代码片段和解析：

```cpp
// 初始化
void CPartManager::Init(IndexType maxIndex, PartIndexType maxPart) {
    // 释放之前的资源
    Release();

    // 确保部分数量不超过整体数量
    if (maxPart > maxIndex) {
        maxPart = maxIndex;
    }

    // 分配内存
    m_nIndex = maxIndex;
    m_pPartIndex = new PartIndexType[m_nIndex];
    for (int i = 0; i < m_nIndex; i++) {
        m_pPartIndex[i] = m_PartIndexNULL; // 初始化为无效值
    }

    // 初始化部分相关的变量
    m_nPart = maxPart;
    m_nPartUsed = 0;
    m_pData = new DataType[m_nPart];
    m_pParentIndex = new IndexType[m_nPart];
    m_pLastTime = new DWORD[m_nPart];
}
```

### 7. 总结
`CPartManager` 类通过部分索引管理大量数据，采用 LRU 策略有效利用内存。它的设计适合在内存有限的环境中使用，提供了高效的数据访问和管理方式。

如果还有其他具体问题或者需要更深入的解析，请告诉我！