-- BitReserve.lua
--[[
这段代码实现了一个位流处理类 Bit_Reserve，用于在位级别上读取和写入数据。主要功能包括：

构造函数和析构函数: 初始化和释放资源。
读取位: 从位流中读取指定数量的位。
写入字节: 将字节写入位流。
回退位和字节: 支持在位流中回退。
]]

local BitReserve = {}
BitReserve.__index = BitReserve

local BUFSIZE = 4096

function BitReserve:new()
    local obj = {
        offset = 0,
        totbit = 0,
        buf_byte_idx = 0,
        buf = {},
        buf_bit_idx = 8,
        putmask = {}
    }
    
    -- 初始化 buf
    for i = 1, BUFSIZE do
        obj.buf[i] = 0
    end
    
    -- 初始化 putmask
    for i = 0, 9 do
        obj.putmask[i] = 2^i - 1
    end
    
    setmetatable(obj, self)
    return obj
end

function BitReserve:__gc()
    -- Lua 会自动管理内存，不需要显式释放
end

-- 从位流中读取 N 位
function BitReserve:hgetbits(N)
    local val = 0
    local j = N

    self.totbit = self.totbit + N
    while j > 0 do
        if self.buf_bit_idx == 0 then
            self.buf_bit_idx = 8
            self.buf_byte_idx = self.buf_byte_idx + 1
        end

        local k = math.min(j, self.buf_bit_idx)
        local tmp = self.buf[self.buf_byte_idx % BUFSIZE + 1] -- Lua 索引从 1 开始
        tmp = bit.band(tmp, self.putmask[self.buf_bit_idx])
        self.buf_bit_idx = self.buf_bit_idx - k
        tmp = bit.rshift(tmp, self.buf_bit_idx)
        j = j - k
        val = bit.bor(val, bit.lshift(tmp, j))
    end
    return val
end

-- 将 8 位写入位流
function BitReserve:hputbuf(val)
    self.buf[self.offset % BUFSIZE + 1] = val
    self.offset = self.offset + 1
end

-- 回退 N 位
function BitReserve:rewindNbits(N)
    self.totbit = self.totbit - N
    self.buf_bit_idx = self.buf_bit_idx + N
    while self.buf_bit_idx >= 8 do
        self.buf_bit_idx = self.buf_bit_idx - 8
        self.buf_byte_idx = self.buf_byte_idx - 1
    end
end

-- 回退 N 字节
function BitReserve:rewindNbytes(N)
    self.totbit = self.totbit - (N * 8)
    self.buf_byte_idx = self.buf_byte_idx - N
end

return BitReserve
