`CToken.h` 文件定义了一个 `CToken` 类，用于处理字符串的分割和解析。以下是该类的主要功能和结构概述：

### 主要功能

1. **字符串分割**：
   - `CToken` 类能够根据指定的分隔符将字符串分割成多个标记（token）。

2. **空格处理**：
   - 提供方法来跳过多个连续的空格，从而简化标记的提取过程。

3. **动态内存管理**：
   - 类内部使用动态内存来存储字符串，并提供相应的内存释放机制。

### 主要成员函数

#### 构造与析构

- **构造函数**：
  ```cpp
  CToken(const char* str = NULL);
  ```
  - 初始化时可以传入一个字符串。

- **析构函数**：
  ```cpp
  ~CToken();
  ```
  - 负责释放动态分配的内存。

#### 字符串设置

- **设置字符串**：
  ```cpp
  void SetString(const char* str);
  ```
  - 设置需要解析的字符串。

#### 空格处理

- **跳过空格**：
  ```cpp
  void SkipSpace();
  ```
  - 跳过字符串中的空格，以便定位下一个标记。

#### 标记提取

- **获取下一个标记**：
  ```cpp
  const char* GetToken(const char* delimiter = " ");
  ```
  - 根据指定的分隔符提取当前的标记。

- **获取剩余字符串**：
  ```cpp
  const char* GetEnd();
  ```
  - 返回当前位置到字符串末尾的所有内容。

### 私有成员函数

- **内存释放**：
  ```cpp
  void Release();
  ```
  - 负责释放分配的内存以防止内存泄漏。

### 数据成员

- **字符串指针**：
  ```cpp
  char* m_pString;
  ```
  - 存储待解析的字符串。

- **当前指针**：
  ```cpp
  char* m_pCurrent;
  ```
  - 指向当前解析的位置。

### 示例代码片段

以下是 `CToken` 类的一部分实现示例，展示了如何获取下一个标记：

```cpp
const char* CToken::GetToken(const char* delimiter) {
    SkipSpace(); // 跳过空格
    // 获取当前标记的开始位置
    char* start = m_pCurrent;
    
    // 查找下一个分隔符
    while (*m_pCurrent && !strchr(delimiter, *m_pCurrent)) {
        m_pCurrent++;
    }
    
    // 如果找到了分隔符，替换为 '\0'，并移动到下一个字符
    if (*m_pCurrent) {
        *m_pCurrent++ = '\0';
    }
    
    return start; // 返回当前标记的起始位置
}
```

### 总结

`CToken` 类提供了一种简单而有效的方式来解析字符串，支持处理空格和自定义分隔符。通过动态内存管理和标记提取功能，该类适用于需要字符串处理的多种场景，如命令解析、文本分析等。