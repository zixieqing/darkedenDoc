//------------------------------------------------ ----------------------
//MActionInfo.h
//------------------------------------------------ ----------------------
//
// = 表达具有相关效果的一种现象（特殊动作...）所需的信息
//
// = 动作信息节点
// - EffectGeneratorTableID
//-BltType
//-帧ID
// - 期间
//
// = ActionInfoNode 数组
//
//------------------------------------------------ ----------------------
/*

 [对于我（玩家）]

  当动作执行时
  向服务器发送使用技术包
  参考g_ActionInfoTable来表达使用技能的效果。

  使用该技术时，当结果数据包从服务器到达时，
  （如果玩家正在进行的技能ID相同）
  将结果转化为ActionResult
  设置为 Player 中 EffectTarget 的 ActionResult*。


  如果不，
  将结果放入ActionResult并立即应用结果。
  直接创建EffectTarget并使用EffectGenerator..
  效果创建......等等


 [对于其他人]

  开始操作、结果操作和结果...在一个数据包中传递。
  通过将结果 Actions 转化为 ActionResult
  执行start Action时，在EffectTarget中设置ActionResult*。


 (*) 来自 EffectGenerator 的 ActionResult


 [ 参考 ]

 - 如果将一项技术分成详细的步骤（ACTION_INFO_NODE）...
  下面是一个有代表性的案例。

 ==>施法动作+施法效果-->技巧开始效果-->技巧进度效果-->技巧结束效果

 ==> [变异] 施法操作 --> 技术进步效果 --> 技术进步效果 --> .... 当然等等。

 - 这里，施法动作+施法效果为MActionInfo，
 后续的操作步骤可以用单个ACTION_INFO_NODE来表示。

 - Casting Effect是AttachEffect，通过附加到角色上来表现。
 - 铸造ActionInfo可以表达更复杂的铸造。

 - 一项技术 (MActionInfo) 包含该技术独有的信息，并且
 它表示为 ACTION_INFO_NODE 数组。

 - 在一项技术的 ACTION_INFO_NODE 中，“基本操作”或“渐进操作”
 有些行为可以被称为意义。
  （如果是瞬间发动的技能，则可能不存在。）
  这个阶段称为MainNode。
 
 - MainNode 意味着技术的全面（-_-;）开始。
 比如‘光之科技’就看等级了。
  使用时间可能会有所不同。
  此时，可以将表达使用时间的步长设置为MainNode。
  如果需要立即应用该技术，则该技术从主节点开始。

 - 节点中的 bDelayNode 是
 这是指应用延迟的节点。
  可以说和MainNode类似，但是
  由于它是应用实际延迟的节点，因此含义略有不同。
  MainNode只有一个，但bDelayNode可以有多个。
 

 - 存在需要立即表达MainNode已经在进行中的状态的情况。
  （如果它在另一个屏幕上并且可见，服务器将发送信息。）
  这种情况下……立即不显示施法动作或技能启动效果。
  必须表达MainNode。

 - ResultTime 是处理结果的时间。
 在各个ACTION_INFO_NODE中，从服务器收到的result(!)是
  什么时候应用它...
  如果没有设置，可以在最后处理。

 - 开始铸造？
 技术的开始
  (1) 当角色开始施法时，
  (2)角色的铸造操作完成后(StartAfterCasting)
  有两种情况...

 - 选角？
 大多数情况下，只有 AttachEffect 表示为 EffectSpriteTypeID。
  然而，有些情况下需要将 CastingActionInfo 表示为特定的 ActionInfo。
  如果设置了 bCastingActionInfo，则假定 ResultActionInfo 不存在。

*/
//------------------------------------------------ ----------------------