------------------------------------------------------------------------ 
-- MLinearEffect.lua 
------------------------------------------------------------------------ 
local MLinearEffect = class("MLinearEffect", MMovingEffect) 

function MLinearEffect:__init(bltType) 
    MMovingEffect.__init(self, bltType) 

    -- m_ObjectType = TYPE_EFFECT 
    -- m_EffectType = EFFECT_LINEAR 

    self.m_TargetX = 0 
    self.m_TargetY = 0 
    self.m_TargetZ = 0 

    -- 一次移动的像素量 
    self.m_StepX = 0 
    self.m_StepY = 0 
    self.m_StepZ = 0 
    self.m_StepPixel = 0 

    self.m_Len = 0 
end 

function MLinearEffect:__delete() 
end 

------------------------------------------------------------------------ 
-- 设置目标 
------------------------------------------------------------------------ 
-- 输入接收的目标位置 
-- 从当前位置移动到目标位置 
-- 按照 speed 移动。 
function MLinearEffect:SetTarget(x, y, z, stepPixel) 
    -- -------------------------------------------------- 
    -- 保存目标位置 
    -- -------------------------------------------------- 
    self.m_TargetX = x 
    self.m_TargetY = y 
    self.m_TargetZ = z 

    -- -------------------------------------------------- 
    -- 计算要移动的像素数 
    -- -------------------------------------------------- 
    local moveX = self.m_TargetX - self.m_PixelX 
    local moveY = self.m_TargetY - self.m_PixelY 
    local moveZ = self.m_TargetZ - self.m_PixelZ 

    -- 移动方向设置 
    self.m_Direction = MTopView:GetDirectionToPosition(self.m_PixelX, self.m_PixelY, self.m_TargetX, self.m_TargetY) 

    -- -------------------------------------------------- 
    -- 一次移动的像素数 
    -- -------------------------------------------------- 
    -- 要移动的距离 
    self.m_Len = math.sqrt(moveX * moveX + moveY * moveY + moveZ * moveZ) 

    if self.m_Len == 0 then 
        self.m_StepX = 0 
        self.m_StepY = 0 
        self.m_StepZ = 0 
    else 
        -- 转换为单位长度 
        self.m_StepX = moveX / self.m_Len * stepPixel 
        self.m_StepY = moveY / self.m_Len * stepPixel 
        self.m_StepZ = moveZ / self.m_Len * stepPixel 
    end 

    self.m_StepPixel = stepPixel 
end 

------------------------------------------------------------------------ 
-- 更新 
------------------------------------------------------------------------ 
-- m_Count 为 0 时，-1 直到改变帧。 
-- 也要移动像素坐标。 
-- 当然，Sector 坐标也要调整。 
-- 
-- 目标像素位置按一定像素移动。 
-- 
-- 返回 
-- true  - 继续移动... 
-- false - 这意味着这是最后一次移动 
function MLinearEffect:Update() 
    -- 是否可以继续更新？ 
    if g_CurrentFrame < self.m_EndFrame then 
        -- ------------------------------- 
        -- 改变像素坐标。 
        -- ------------------------------- 
        -- 每个方向移动一步。 
        self.m_PixelX = self.m_PixelX + self.m_StepX 
        self.m_PixelY = self.m_PixelY + self.m_StepY 
        self.m_PixelZ = self.m_PixelZ + self.m_StepZ 

        -- ------------------------------------------ 
        -- 考虑到完全移动的情况。 
        -- ------------------------------------------ 
        if math.abs(self.m_PixelX - self.m_TargetX) < self.m_StepPixel and 
           math.abs(self.m_PixelY - self.m_TargetY) < self.m_StepPixel and 
           math.abs(self.m_PixelZ - self.m_TargetZ) < self.m_StepPixel then 
            self.m_PixelX = self.m_TargetX 
            self.m_PixelY = self.m_TargetY 
            self.m_PixelZ = self.m_TargetZ 

            self.m_StepX = 0 
            self.m_StepY = 0 
            self.m_StepZ = 0 

            -- ------------------------------------------ 
            -- 不再需要移动的情况。 
            -- ------------------------------------------ 
            -- 2004, 12, 30, sobeit 添加开始 
            if self:GetActionInfo() == SKILL_HALO then -- 在最终位置等待 0.5 秒 
                if self.m_EndFrame > g_CurrentFrame + 8 then 
                    self.m_EndFrame = g_CurrentFrame + 8 
                end 
            else 
                -- 2004, 12, 30, sobeit 添加结束 
                self.m_EndFrame = 0 
                return false 
            end 
        end 

        -- ------------------------------- 
        -- 调整 Sector 坐标。 
        -- ------------------------------- 
        self:AffectPosition() 

        -- ------------------------------- 
        -- 改变帧。 
        -- ------------------------------- 
        self:NextFrame() 

        if self.m_BltType == BLT_EFFECT then 
            self.m_Light = g_pTopView.m_EffectAlphaFPK[self.m_FrameID][self.m_Direction][self.m_CurrentFrame]:GetLight() 
        end 

        -- ------------------------------- 
        -- 计数器减一。 
        -- ------------------------------- 
        -- self.m_Count = self.m_Count - 1 

        return true 
    end 

    -- 结束~ 
    return false 
end 

return MLinearEffect 


