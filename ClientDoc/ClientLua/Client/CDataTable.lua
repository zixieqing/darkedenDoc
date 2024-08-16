--[[
这段代码定义了一个模板类 CDataTable，用于管理一组数据的动态数组。它提供了初始化、释放、文件读写等功能。主要功能包括：

1.构造函数和析构函数: 初始化和清理资源。
2.初始化和释放: Init 方法用于分配内存，Release 方法用于释放内存。
3.获取大小: GetSize 方法返回当前元素的数量。
4.访问元素: 使用下标运算符和 Get 方法访问元素。
5.文件 I/O: SaveToFile 和 LoadFromFile 方法用于将数据保存到文件或从文件加载数据。
]]

-- CDataTable.lua

local CDataTable = {}
CDataTable.__index = CDataTable

-- 构造函数
function CDataTable:new()
    local obj = {
        m_Size = 0,
        m_pTypeInfo = {}
    }
    setmetatable(obj, self)
    return obj
end

-- 初始化
function CDataTable:Init(size)
    -- 如果个数为0，直接返回
    if size == 0 then
        return
    end

    -- 先释放已有的内存
    self:Release()

    -- 分配内存
    self.m_Size = size
    self.m_pTypeInfo = {}
    for i = 1, size do
        self.m_pTypeInfo[i] = {}  -- 假设 Type 是一个表
    end
end

-- 释放内存
function CDataTable:Release()
    if self.m_Size > 0 then
        -- 清空类型信息
        self.m_pTypeInfo = {}
        self.m_Size = 0
    end
end

-- 获取大小
function CDataTable:GetSize()
    return self.m_Size
end

-- 访问元素
function CDataTable:__index(index)
    return self.m_pTypeInfo[index]
end

function CDataTable:Get(index)
    return self.m_pTypeInfo[index]
end

-- 保存到文件
function CDataTable:SaveToFile(file)
    -- 保存大小
    file:write(string.pack("i4", self.m_Size))

    -- 如果没有数据，直接返回
    if self.m_Size == 0 then
        return
    end

    -- 保存每个信息
    for i = 1, self.m_Size do
        file:write(string.pack("s", self.m_pTypeInfo[i]))  -- 假设 Type 可以用字符串表示
    end
end

-- 从文件加载
function CDataTable:LoadFromFile(file)
    -- 读取大小
    local numSize = file:read("*n")

    -- 如果当前大小与读取的大小不同，重新分配内存
    if self.m_Size ~= numSize then
        self:Release()
        self:Init(numSize)
    end

    -- 从文件中读取每个信息
    for i = 1, self.m_Size do
        self.m_pTypeInfo[i] = file:read("*s")  -- 假设 Type 可以用字符串表示
    end
end

return CDataTable
