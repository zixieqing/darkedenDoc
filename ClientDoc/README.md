## 天之炼狱框架解析
.
|-- Client 客户端代码
|-- DARKEDEN 工具库
|-- VS_UI UI
|-- basic  基础宏
|-- lib 第三方库
`-- standalone_version.md 文档教程


## 详细目录树
参考：目录树


## 重点文件记录：

CWaitPacketUpdate：等待服务器数据到来


### 工具层
CSpriteTexturePartManager
等精灵加载工具


### 架构层
Client:程序的主要逻辑，包括初始化、事件处理、窗口消息处理、以及网络连接等
GameInit: 游戏初始化：
GameMain:


### 技能释放相关：
MActionResult：


MAroundZoneEffectGenerator :地面区域特效生成器
MAttachCreatureEffectGenerator:指定生物特效生成器


### 服务器数据解析
ServerInfoFileParser:服务器数据解析
Packet 目录：
在游戏开发中，`CPackets`、`GPackets`、`LPackets`、`RPackets` 和 `UPackets` 通常指的是不同类型的网络数据包（packet）。它们的含义通常如下：
1. **CPackets**：通常指客户端数据包，处理客户端发送给服务器的请求或信息。

2. **GPackets**：可能指游戏相关的数据包，涉及游戏逻辑或状态更新的消息。

3. **LPackets**：可能指登录数据包，用于处理用户登录相关的信息和验证。

4. **RPackets**：通常指响应数据包，服务器对客户端请求的响应消息。

5. **UPackets**：可能指更新数据包，用于发送游戏状态或数据的更新信息。

这些数据包的具体实现和用途可能会根据游戏的架构和设计而有所不同。


### 一些其他effect:
带有EffectGenerator 都是一些特效类
MMeteorDropEffectGenerator  生成流星落下的效果
MParabolaEffect 抛物线效果

### 物品
MItemTable 物品表


MSlotItemManager 物品槽位管理
MSortedItemManager 物品排序管理


###  穿戴类
MPlayerGear 玩家穿戴装备类 【父类】
|
继承
MVampireGear 吸血鬼穿戴
MSlayerGear 杀戮者（人类） 穿戴
MOustersGear 驱逐者  穿戴

### 技能
MSkillInfoTable 技能表，从服务器接收

#### 技能信息
PCSkillInfo【父类】
| 继承
SlayerSkillInfo 杀戮者（人类）技能信息
VampireSkillInfo 吸血鬼技能信息
OustersSkillInfo 驱逐者

SkillDef 技能定义表


### 职业本身属性:123区分：区分3个info.md
PCInfo
| 继承
PCSlayerInfo PCSlayerInfo2 PCSlayerInfo3
VampireInfo VampireInfo2 VampireInfo3
OustersInfo  OustersInfo2  OustersInfo3



### 背包
 MStorage.cpp