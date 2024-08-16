------------------------------------------------------------------------ 
--[[
//----------------------------------------------------------------------
// MItemTable.h
//----------------------------------------------------------------------
// 根据物品种类存储信息的类
//----------------------------------------------------------------------
//
// [ 按种类分类的信息 ] 
//
// - Tile中的 FrameID
// - Inventory中的 SpriteID
// - 名称... 等等...
// 
//
// (*g_pItemTable)[class][type] 可以访问一个物品的信息。
//
//----------------------------------------------------------------------
//
// Value1 ~ 4 是可变的..
// 根据物品的种类，特定的 value 可能代表某个值。
//
// MotorCycle				: 耐久性(1), 运输重量(2), Def(6)
// GearItem					: 耐久性(1), 保护(2), Def(6)
// Belt						: 耐久性(1), 保护(2), 口袋数(3), Def(6)
// HolyWater, 地雷, 炸弹	: MinDam(1)~MaxDam(2)
// Potion					: 恢复值(1)
// 剑,刀					: 耐久性(1), 保护(?), MinDam(3)~MaxDam(4), Speed(7)
// 十字架					: 耐久性(1), 保护(?), MinDam(3)~MaxDam(4), MP增加(5), Speed(7)
// 枪						: 耐久性(1), 保护(?), MinDam(3)~MaxDam(4), 射程(5), Speed(7)
// 弹夹						: 最大弹夹数(1)
//----------------------------------------------------------------------
]]
-- MItemTable.lua 
------------------------------------------------------------------------ 
local MItemTable = class("MItemTable") 

------------------------------------------------------------------------ 
-- Global 
------------------------------------------------------------------------ 
g_pItemTable = nil 
g_ELEMENTAL_COLOR = { 
    cc.c3b(255, 100, 100), 
    cc.c3b(100, 100, 255), 
    cc.c3b(255, 180, 100), 
    cc.c3b(100, 100, 255), 
    cc.c3b(192, 192, 255) 
} 
g_ELEMENTAL_STRING_ID = { 
    UI_STRING_MESSAGE_ELEMENTAL_FIRE, 
    UI_STRING_MESSAGE_ELEMENTAL_WATER, 
    UI_STRING_MESSAGE_ELEMENTAL_EARTH, 
    UI_STRING_MESSAGE_ELEMENTAL_WIND, 
    UI_STRING_MESSAGE_ELEMENTAL_SUM 
} 

------------------------------------------------------------------------ 
-- ITEMTABLE_INFO 
------------------------------------------------------------------------ 
ITEMTABLE_INFO = class("ITEMTABLE_INFO") 

function ITEMTABLE_INFO:__init() 
    -- Frame ID 
    self.TileFrameID = FRAMEID_NULL -- Tile中的FrameID 
    self.InventoryFrameID = FRAMEID_NULL -- Inventory中的Frame ID 
    self.GearFrameID = FRAMEID_NULL -- Gear中的Frame ID 
    self.AddonMaleFrameID = FRAMEID_NULL -- 装备时的动作FrameID - 男性 
    self.AddonFemaleFrameID = FRAMEID_NULL -- 装备时的动作FrameID - 女性 

    -- Sound ID 
    self.UseSoundID = SOUNDID_NULL -- Item使用SoundID 
    self.TileSoundID = SOUNDID_NULL -- Item拾取SoundID 
    self.InventorySoundID = SOUNDID_NULL -- Inventory中的Sound 
    self.GearSoundID = SOUNDID_NULL -- Gear中的Sound 

    self.bMaleOnly = false 
    self.bFemaleOnly = false 

    -- Inventory中的Grid大小 
    self.GridWidth = 1 
    self.GridHeight = 1 

    -- item自身的固定信息 
    self.Weight = 0 -- 重量 

    -- 值 --> 保护、攻击力、射程 
    self.Value1 = 0 
    self.Value2 = 0 
    self.Value3 = 0 
    self.Value4 = 0 
    self.Value5 = 0 
    self.Value6 = 0 
    self.Value7 = 0 

    -- 所需能力 
    self.RequireSTR = 0 
    self.RequireDEX = 0 
    self.RequireINT = 0 
    self.RequireSUM = 0 
    self.RequireAdvancementLevel = 0 
    self.RequireLevel = 0 

    -- 基本攻击 ActionInfo 
    self.UseActionInfo = ACTIONINFO_NULL 

    -- 银色涂层 
    self.SilverMax = 0 

    self.ToHit = 0 

    self.MaxNumber = 1 

    self.CriticalHit = 0 

    self.ItemStyle = 0 

    self.ElementalType = ELEMENTAL_TYPE_ANY 
    self.Elemental = 0 

    self.DescriptionFrameID = 0 
end 

function ITEMTABLE_INFO:__delete() 
end 

------------------------------------------------------------------------ 
-- 成员函数 
------------------------------------------------------------------------ 
------------------------------------------------------------------------ 
-- 设置 SoundID 
------------------------------------------------------------------------ 
function ITEMTABLE_INFO:SetSoundID(tile, inventory, gear, use) 
    self.TileSoundID = tile 
    self.InventorySoundID = inventory 
    self.GearSoundID = gear 
    self.UseSoundID = use 
end 

------------------------------------------------------------------------ 
-- 设置 FrameID 
------------------------------------------------------------------------ 
function ITEMTABLE_INFO:SetFrameID(tile, inventory, gear) 
    self.TileFrameID = tile 
    self.InventoryFrameID = inventory 
    self.GearFrameID = gear 
end 

------------------------------------------------------------------------ 
-- 设置 DropFrameID 
------------------------------------------------------------------------ 
function ITEMTABLE_INFO:SetDropFrameID(drop) 
    self.DropFrameID = drop 
end 

------------------------------------------------------------------------ 
-- 设置 Addon FrameID 
------------------------------------------------------------------------ 
function ITEMTABLE_INFO:SetAddonFrameID(male, female) 
    self.AddonMaleFrameID = male 
    self.AddonFemaleFrameID = female 
end 

------------------------------------------------------------------------ 
-- 设置 Grid 
------------------------------------------------------------------------ 
function ITEMTABLE_INFO:SetGrid(width, height) 
    self.GridWidth = width 
    self.GridHeight = height 
end 

------------------------------------------------------------------------ 
-- 设置值 
------------------------------------------------------------------------ 
function ITEMTABLE_INFO:SetValue(v1, v2, v3, v4, v5, v6, v7) 
    self.Value1 = v1 
    self.Value2 = v2 
    self.Value3 = v3 
    self.Value4 = v4 
    self.Value5 = v5 
    self.Value6 = v6 
    self.Value7 = v7 
end 

------------------------------------------------------------------------ 
-- 保存 
------------------------------------------------------------------------ 
function ITEMTABLE_INFO:SaveToFile(file) 
    -- 保存名称 
    self.EName:SaveToFile(file) 
    self.HName:SaveToFile(file) 
    self.Description:SaveToFile(file) 

    -- Frame ID 
    file:write(string.pack("I4", self.TileFrameID)) 
    file:write(string.pack("I4", self.InventoryFrameID)) 
    file:write(string.pack("I4", self.GearFrameID)) 
    file:write(string.pack("I4", self.DropFrameID)) 
    file:write(string.pack("I4", self.AddonMaleFrameID)) 
    file:write(string.pack("I4", self.AddonFemaleFrameID)) 

    -- Sound ID 
    file:write(string.pack("I4", self.UseSoundID)) 
    file:write(string.pack("I4", self.TileSoundID)) 
    file:write(string.pack("I4", self.InventorySoundID)) 
    file:write(string.pack("I4", self.GearSoundID)) 

    -- Inventory中的Grid大小 
    file:write(string.pack("B", self.GridWidth)) 
    file:write(string.pack("B", self.GridHeight)) 

    -- 价格 
    file:write(string.pack("I4", self.Price)) 

    -- 重量 
    file:write(string.pack("I4", self.Weight)) 

    -- 值 
    file:write(string.pack("I4", self.Value1)) 
    file:write(string.pack("I4", self.Value2)) 
    file:write(string.pack("I4", self.Value3)) 
    file:write(string.pack("I4", self.Value4)) 
    file:write(string.pack("I4", self.Value5)) 
    file:write(string.pack("I4", self.Value6)) 
    file:write(string.pack("I4", self.Value7)) 

    -- 所需能力 
    file:write(string.pack("B", self.RequireSTR)) 
    file:write(string.pack("B", self.RequireDEX)) 
    file:write(string.pack("B", self.RequireINT)) 
    file:write(string.pack("H", self.RequireSUM)) 
    file:write(string.pack("B", self.RequireLevel)) 
    file:write(string.pack("B", self.RequireAdvancementLevel)) 
    file:write(string.pack("B", self.bMaleOnly)) 
    file:write(string.pack("B", self.bFemaleOnly)) 

    -- UseActionInfo 
    file:write(string.pack("I4", self.UseActionInfo)) 

    file:write(string.pack("I4", self.SilverMax)) 
    file:write(string.pack("I4", self.ToHit)) 
    file:write(string.pack("I4", self.MaxNumber)) 
    file:write(string.pack("I4", self.CriticalHit)) 

    local DefaultOptionListSize = #self.DefaultOptionList 
    file:write(string.pack("B", DefaultOptionListSize)) 
    for _, Option in ipairs(self.DefaultOptionList) do 
        file:write(string.pack("I4", Option)) 
    end 

    file:write(string.pack("I4", self.ItemStyle)) 
    file:write(string.pack("I4", self.ElementalType)) 
    file:write(string.pack("H", self.Elemental)) 
    file:write(string.pack("B", self.Race)) 

    -- 2005, 1, 14, sobeit 添加开始 - ItemDescription.spk 中使用的 frameID 
    file:write(string.pack("I4", self.DescriptionFrameID)) 
    -- 2005, 1, 14, sobeit 添加结束 
end 

------------------------------------------------------------------------ 
-- 加载 
------------------------------------------------------------------------ 
function ITEMTABLE_INFO:LoadFromFile(file) 
    self.EName:LoadFromFile(file) 
    self.HName:LoadFromFile(file) 
    self.Description:LoadFromFile(file) 

    -- Frame ID 
    self.TileFrameID = string.unpack("I4", file:read(4)) 
    self.InventoryFrameID = string.unpack("I4", file:read(4)) 
    self.GearFrameID = string.unpack("I4", file:read(4)) 
    self.DropFrameID = string.unpack("I4", file:read(4)) 
    self.AddonMaleFrameID = string.unpack("I4", file:read(4)) 
    self.AddonFemaleFrameID = string.unpack("I4", file:read(4)) 

    -- Sound ID 
    self.UseSoundID = string.unpack("I4", file:read(4)) 
    self.TileSoundID = string.unpack("I4", file:read(4)) 
    self.InventorySoundID = string.unpack("I4", file:read(4)) 
    self.GearSoundID = string.unpack("I4", file:read(4)) 

    -- Grid大小 
    self.GridWidth = string.unpack("B", file:read(1)) 
    self.GridHeight = string.unpack("B", file:read(1)) 

    -- 价格 
    self.Price = string.unpack("I4", file:read(4)) 

    -- 重量 
    self.Weight = string.unpack("I4", file:read(4)) 

    -- 值 
    self.Value1 = string.unpack("I4", file:read(4)) 
    self.Value2 = string.unpack("I4", file:read(4)) 
    self.Value3 = string.unpack("I4", file:read(4)) 
    self.Value4 = string.unpack("I4", file:read(4)) 
    self.Value5 = string.unpack("I4", file:read(4)) 
    self.Value6 = string.unpack("I4", file:read(4)) 
    self.Value7 = string.unpack("I4", file:read(4)) 

    -- 所需能力 
    self.RequireSTR = string.unpack("B", file:read(1)) 
    self.RequireDEX = string.unpack("B", file:read(1)) 
    self.RequireINT = string.unpack("B", file:read(1)) 
    self.RequireSUM = string.unpack("H", file:read(2)) 
    self.RequireLevel = string.unpack("B", file:read(1)) 
    self.RequireAdvancementLevel = string.unpack("B", file:read(1)) 
    self.bMaleOnly = string.unpack("B", file:read(1)) 
    self.bFemaleOnly = string.unpack("B", file:read(1)) 

    -- UseActionInfo 
    self.UseActionInfo = string.unpack("I4", file:read(4)) 

    self.SilverMax = string.unpack("I4", file:read(4)) 
    self.ToHit = string.unpack("I4", file:read(4)) 
    self.MaxNumber = string.unpack("I4", file:read(4)) 
    self.CriticalHit = string.unpack("I4", file:read(4)) 

    local DefaultOptionListSize = string.unpack("B", file:read(1)) 
    for i = 1, DefaultOptionListSize do 
        local TempOptionType = string.unpack("I4", file:read(4)) 
        table.insert(self.DefaultOptionList, TempOptionType) 
    end 

    self.ItemStyle = string.unpack("I4", file:read(4)) 
    self.ElementalType = string.unpack("I4", file:read(4)) 
    self.Elemental = string.unpack("H", file:read(2)) 
    self.Race = string.unpack("B", file:read(1)) 

    -- 2005, 1, 14, sobeit 添加开始 - ItemDescription.spk 中使用的 frameID 
    self.DescriptionFrameID = string.unpack("I4", file:read(4)) 
    -- 2005, 1, 14, sobeit 添加结束 
end 

------------------------------------------------------------------------ 
-- ITEMTYPE_TABLE 
------------------------------------------------------------------------ 
ITEMTYPE_TABLE = class("ITEMTYPE_TABLE") 

function ITEMTYPE_TABLE:LoadFromFile(file) 
    CTypeTable[ITEMTABLE_INFO]:LoadFromFile(file) 

    self.m_AveragePrice = 0 

    local count = 0 
    for i = 1, self.m_Size do 
        if #self.m_pTypeInfo[i].DefaultOptionList == 0 then 
            self.m_AveragePrice = self.m_AveragePrice + self.m_pTypeInfo[i].Price 
            count = count + 1 
        end 
    end 
    if count > 0 then 
        self.m_AveragePrice = self.m_AveragePrice / count 
        self.m_AveragePrice = self.m_AveragePrice / 1000 
        self.m_AveragePrice = self.m_AveragePrice * 100 
    end 
end 

return MItemTable 
