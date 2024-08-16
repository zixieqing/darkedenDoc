-- AppendPatchInfo.lua
--[[
这段代码主要实现了一个补丁管理系统，允许将补丁文件附加到原始文件上。代码中定义了两个类：APPEND_PATCH_NODE 和 AppendPatch。

主要功能
Append: 将补丁文件内容追加到原始文件。
SaveToFile / LoadFromFile: 保存和加载补丁信息。
ExecutePatch: 执行所有补丁。
CheckFinalInfo / CalculateFinalInfo: 校验最终文件信息的正确性。
]]
local AppendPatchNode = {}
AppendPatchNode.__index = AppendPatchNode

function AppendPatchNode:new()
    local obj = {
        appendFilename = "",
        appendFilesize = 0,
        appSpkSize = 0,
        writePosition = 0,
        afterFilesize = 0,
        afterSpkSize = 0
    }
    setmetatable(obj, self)
    return obj
end

function AppendPatchNode:Append(orgFilename)
    local appendFile = io.open(self.appendFilename, "rb")
    if not appendFile then return false end

    local orgFile = io.open(orgFilename, "r+b")
    if not orgFile then return false end

    local orgSpkSize = orgFile:read(2) -- 读取 Sprite 的个数
    appendFile:seek("set", 2) -- 跳过 size 部分
    orgFile:seek("set", self.writePosition)

    local buffer = ""
    while true do
        buffer = appendFile:read(4096)
        if not buffer then break end
        orgFile:write(buffer)
    end

    appendFile:close()

    -- 更新 Sprite 数量
    orgFile:seek("set", 0)
    local afterNum = math.max(self.afterSpkSize, orgSpkSize)
    orgFile:write(string.char(afterNum:byte(1), afterNum:byte(2)))
    orgFile:close()

    os.remove(self.appendFilename) -- 删除补丁文件
    return true
end

function AppendPatchNode:SaveToFile(file)
    file:write(self.appendFilename .. "\n")
    file:write(string.pack("I4", self.appendFilesize))
    file:write(string.pack("H", self.appSpkSize))
    file:write(string.pack("I4", self.writePosition))
    file:write(string.pack("I4", self.afterFilesize))
    file:write(string.pack("H", self.afterSpkSize))
end

function AppendPatchNode:LoadFromFile(file)
    self.appendFilename = file:read("*l")
    self.appendFilesize = string.unpack("I4", file:read(4))
    self.appSpkSize = string.unpack("H", file:read(2))
    self.writePosition = string.unpack("I4", file:read(4))
    self.afterFilesize = string.unpack("I4", file:read(4))
    self.afterSpkSize = string.unpack("H", file:read(2))
end

-- AppendPatch 类
local AppendPatch = {}
AppendPatch.__index = AppendPatch

function AppendPatch:new()
    local obj = {
        m_orgFilename = "",
        m_orgFilesize = 0,
        m_orgSpkSize = 0,
        m_finalFilesize = 0,
        m_finalSpkSize = 0,
        m_AppendPatch = {}
    }
    setmetatable(obj, self)
    return obj
end

function AppendPatch:Release()
    for _, node in ipairs(self.m_AppendPatch) do
        node = nil -- Lua 会自动垃圾回收
    end
    self.m_AppendPatch = {}
    self.m_orgFilename = ""
    self.m_orgFilesize = 0
    self.m_orgSpkSize = 0
    self.m_finalFilesize = 0
    self.m_finalSpkSize = 0
end

function AppendPatch:SetOriginalInfo(orgFilename, orgFilesize, orgSpkSize)
    self.m_orgFilename = orgFilename
    self.m_orgFilesize = orgFilesize
    self.m_orgSpkSize = orgSpkSize
end

function AppendPatch:SetFinalInfo(finalFilesize, finalSpkSize)
    self.m_finalFilesize = finalFilesize
    self.m_finalSpkSize = finalSpkSize
end

function AppendPatch:SetFinalInfoFromFile(currentFilename)
    local file = io.open(currentFilename, "rb")
    if not file then return false end

    self.m_finalSpkSize = string.unpack("H", file:read(2))
    file:seek("end")
    self.m_finalFilesize = file:seek()
    file:close()

    return true
end

function AppendPatch:AddAppendInfo(appendFilename, appendFilesize, appSpkSize)
    local previousFilesize = #self.m_AppendPatch > 0 and self.m_AppendPatch[#self.m_AppendPatch].afterFilesize or self.m_orgFilesize
    local previousSpkSize = #self.m_AppendPatch > 0 and self.m_AppendPatch[#self.m_AppendPatch].afterSpkSize or self.m_orgSpkSize

    local node = AppendPatchNode:new()
    node.appendFilename = appendFilename
    node.appendFilesize = appendFilesize
    node.appSpkSize = appSpkSize
    node.writePosition = previousFilesize
    node.afterFilesize = previousFilesize + appendFilesize - 2
    node.afterSpkSize = previousSpkSize + appSpkSize

    table.insert(self.m_AppendPatch, node)
end

function AppendPatch:ExecutePatch()
    for _, node in ipairs(self.m_AppendPatch) do
        if not node:Append(self.m_orgFilename) then
            return false
        end
    end
    return true
end

function AppendPatch:CheckFinalInfo()
    local orgFile = io.open(self.m_orgFilename, "rb")
    if not orgFile then return false end

    local spkSize = string.unpack("H", orgFile:read(2))
    if spkSize ~= self.m_finalSpkSize then
        orgFile:close()
        return false
    end

    orgFile:seek("end")
    local fpEnd = orgFile:seek()
    orgFile:close()

    return fpEnd == self.m_finalFilesize
end

function AppendPatch:CalculateFinalInfo()
    local totalFilesize = self.m_orgFilesize
    local totalSpkSize = self.m_orgSpkSize

    for _, node in ipairs(self.m_AppendPatch) do
        totalFilesize = totalFilesize + node.appendFilesize - 2
        totalSpkSize = totalSpkSize + node.appSpkSize
    end

    return self.m_finalFilesize == totalFilesize and self.m_finalSpkSize == totalSpkSize
end

function AppendPatch:SaveToFile(file)
    file:write(self.m_orgFilename .. "\n")
    file:write(string.pack("I4", self.m_orgFilesize))
    file:write(string.pack("H", self.m_orgSpkSize))
    file:write(string.pack("I4", self.m_finalFilesize))
    file:write(string.pack("H", self.m_finalSpkSize))

    local num = #self.m_AppendPatch
    file:write(string.pack("I4", num))

    for _, node in ipairs(self.m_AppendPatch) do
        node:SaveToFile(file)
    end
end

function AppendPatch:LoadFromFile(file)
    self:Release()

    self.m_orgFilename = file:read("*l")
    self.m_orgFilesize = string.unpack("I4", file:read(4))
    self.m_orgSpkSize = string.unpack("H", file:read(2))
    self.m_finalFilesize = string.unpack("I4", file:read(4))
    self.m_finalSpkSize = string.unpack("H", file:read(2))

    local num = string.unpack("I4", file:read(4))
    for i = 1, num do
        local node = AppendPatchNode:new()
        node:LoadFromFile(file)
        table.insert(self.m_AppendPatch, node)
    end
end

return {
    AppendPatchNode = AppendPatchNode,
    AppendPatch = AppendPatch
}
