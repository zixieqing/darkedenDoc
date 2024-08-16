-- BloodBibleSignInfo.lua
--[[
这段代码定义了一个名为 BloodBibleSignInfo 的类，用于处理与“血之圣经”相关的签名信息。主要功能包括：

构造函数和析构函数: 初始化和清理资源。
读取数据: 从输入流中读取数据并初始化类成员。
写入数据: 将类成员的数据写入输出流。
]]

local BloodBibleSignInfo = {}
BloodBibleSignInfo.__index = BloodBibleSignInfo

function BloodBibleSignInfo:new()
    local obj = {
        m_OpenNum = 0,
        m_ListSize = 0,
        m_SignList = {}
    }
    setmetatable(obj, self)
    return obj
end

-- 从输入流（缓冲区）读取数据来初始化数据包。
function BloodBibleSignInfo:read(iStream)
    local success, err = pcall(function()
        self.m_OpenNum = iStream:read() -- 假设 iStream:read() 返回一个值
        self.m_ListSize = iStream:read() -- 假设 iStream:read() 返回一个值

        for i = 1, self.m_ListSize do
            local itemType = iStream:read() -- 假设 iStream:read() 返回 ItemType_t
            table.insert(self.m_SignList, itemType)
        end
    end)

    if not success then
        error("ProtocolException: " .. err)
    end
end

-- 将类成员的数据写入输出流
function BloodBibleSignInfo:write(oStream)
    local success, err = pcall(function()
        oStream:write(self.m_OpenNum) -- 假设 oStream:write() 接受一个值
        oStream:write(self.m_ListSize) -- 假设 oStream:write() 接受一个值

        for i = 1, self.m_ListSize do
            oStream:write(self.m_SignList[i]) -- 写入每个签名
        end
    end)

    if not success then
        error("ProtocolException: " .. err)
    end
end

return BloodBibleSignInfo
