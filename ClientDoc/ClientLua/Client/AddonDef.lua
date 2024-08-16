--[[ 
---------------------------------------------------------------------- 
AddonDef.lua 
---------------------------------------------------------------------- 
表示 Addon.cfpk 中的顺序。 
---------------------------------------------------------------------- 
]]

-- Addon种类
--[[
ADDONID = {
	HAIR1 = 0,		-- 头发1
	HAIR2 = 1,		-- 头发2
	HAIR3 = 2,		-- 头发3
	HELM1 = 3,		-- 帽子1
	HELM2 = 4,		-- 帽子2	
	COAT1 = 5,		-- 上衣1
	COAT2 = 6,		-- 上衣2		
	TROUSER1 = 7,	-- 裤子1
	TROUSER2 = 8,	-- 裤子2	
	SWORD = 9,		-- 剑	
	BLADE = 10,		-- 刀	
	GUN_TR = 11,	-- 枪1 - 狙击枪(TR)
	GUN_SG = 12,	-- 枪2 - 猎枪(SG)	
	GUN_AR = 13,	-- 枪3 - 步枪(AR)
	GUN_SMG = 14,	-- 枪4 - 冲锋枪(SMG)	
	SHIELD = 15,	-- 盾牌	
	CROSS = 16,		-- 十字架
	MOTORCYCLE = 17,-- 摩托车	
	MAX_ADDONID = 18
}
]]

-- 男性 Slayer
ADDONID_MALE = {
	HELM1 = 0,			-- 帽子1
	COAT1 = 1,			-- 上衣1
	TROUSER1 = 2,		-- 裤子1
	GUN_SMG = 3,		-- 枪4 - 冲锋枪(SMG)	
	BLADE = 4,			-- 刀
	SHIELD1 = 5,		-- 盾牌
	GUN_SG = 6,		-- 枪2 - 猎枪(SG)
	SWORD = 7,			-- 剑	
	GUN_AR = 8,		-- 枪3 - 步枪(AR)
	HAIR1 = 9,			-- 头发1
	HAIR2 = 10,		-- 头发2
	HAIR3 = 11,		-- 头发3
	HELM2 = 12,		-- 帽子2
	COAT2 = 13,		-- 上衣2
	TROUSER2 = 14,	-- 裤子2
	CROSS = 15,		-- 十字架
	GUN_TR = 16,		-- 枪1 - 狙击枪(TR)		
	MOTORCYCLE = 17,	-- 摩托车
	MAX_ADDONID_MALE = 18
}

-- 女性 Slayer
ADDONID_FEMALE = {
	HELM1 = 0,			-- 帽子1
	COAT1 = 1,			-- 上衣1
	TROUSER1 = 2,		-- 裤子1
	GUN_SMG = 3,		-- 枪4 - 冲锋枪(SMG)	
	BLADE = 4,			-- 刀
	SHIELD = 5,		-- 盾牌
	GUN_SG = 6,		-- 枪2 - 猎枪(SG)
	SWORD = 7,			-- 剑	
	GUN_AR = 8,		-- 枪3 - 步枪(AR)
	HAIR1 = 9,			-- 头发1
	HAIR2 = 10,		-- 头发2
	HAIR3 = 11,		-- 头发3
	HELM2 = 12,		-- 帽子2
	COAT2 = 13,		-- 上衣2
	TROUSER2 = 14,	-- 裤子2
	CROSS = 15,		-- 十字架
	GUN_TR = 16,		-- 枪1 - 狙击枪(TR)		
	MOTORCYCLE = 17,	-- 摩托车
	MAX_ADDONID_FEMALE = 18
}

-- 其他定义（可根据需要添加）
