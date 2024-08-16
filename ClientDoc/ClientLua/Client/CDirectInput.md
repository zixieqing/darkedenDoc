将给定的 C++ 代码转换为 Cocos2d-x Lua 的版本，并对代码进行详细解析。

### C++ 代码解析

这段代码定义了一个 `CDirectInput` 类，主要用于处理 DirectInput 设备（如鼠标和键盘）的输入管理。它提供了多种功能，如初始化输入设备、获取鼠标加速度、设置鼠标速度、更新输入状态等。

关键功能包括：

1. **构造函数和析构函数**: 初始化和释放资源。
2. **设备初始化**: `InitDI` 方法用于初始化 DirectInput 设备。
3. **输入更新**: `UpdateInput` 方法用于轮询设备状态。
4. **鼠标和键盘事件处理**: `OnMouseInput` 和 `OnKeyboardInput` 方法处理输入事件。
5. **设置鼠标位置和移动限制**: `SetMousePosition` 和 `SetMouseMoveLimit` 方法用于管理鼠标状态。

### 转换为 Cocos2d-x Lua

以下是转换后的 Lua 代码：

```lua
-- CDirectInput.lua

local CDirectInput = {}
CDirectInput.__index = CDirectInput

-- 常量定义
local MSB = 0x80
local BUFFER_SIZE = 128

function CDirectInput:new()
    local obj = {
        m_pDI = nil,
        m_pMouse = nil,
        m_pKeyboard = nil,
        m_mouse_x = 0,
        m_mouse_y = 0,
        m_mouse_z = 0,
        m_limit_x = 0,
        m_limit_y = 0,
        m_mouse_info = {0, 0, 0},
        m_key = {},
        m_fp_mouse_event_receiver = nil,
        m_fp_keyboard_event_receiver = nil,
        m_bSwapMouseButtons = false
    }
    setmetatable(obj, self)
    self:Clear(obj)
    return obj
end

function CDirectInput:__gc()
    self:FreeDirectInput()
end

-- 清理输入状态
function CDirectInput:Clear()
    for i = 1, 256 do
        self.m_key[i] = false
    end
    
    self.m_lb_down = false
    self.m_rb_down = false
    self.m_cb_down = false
    self.m_lb_up = false
    self.m_rb_up = false
    self.m_cb_up = false
end

-- 初始化 DirectInput
function CDirectInput:InitDI(hWnd, hInst, ex)
    local hr

    -- 注册 DirectInput 子系统并获取 IDirectInput 接口
    hr = DirectInputCreate(hInst, DIRECTINPUT_VERSION, self.m_pDI, nil)
    if hr ~= S_OK then return hr end

    -- 获取鼠标设备接口
    hr = self.m_pDI:CreateDevice(GUID_SysMouse, self.m_pMouse, nil)
    if hr ~= S_OK then return hr end

    -- 获取键盘设备接口
    hr = self.m_pDI:CreateDevice(GUID_SysKeyboard, self.m_pKeyboard, nil)
    if hr ~= S_OK then return hr end

    -- 设置鼠标数据格式
    hr = self.m_pMouse:SetDataFormat(c_dfDIMouse)
    if hr ~= S_OK then return hr end

    -- 设置键盘数据格式
    hr = self.m_pKeyboard:SetDataFormat(c_dfDIKeyboard)
    if hr ~= S_OK then return hr end

    -- 设置鼠标的合作级别
    local mouse_flag = (ex == EXCLUSIVE) and (DISCL_EXCLUSIVE | DISCL_FOREGROUND) or (DISCL_NONEXCLUSIVE | DISCL_FOREGROUND)
    hr = self.m_pMouse:SetCooperativeLevel(hWnd, mouse_flag)
    if hr ~= S_OK then return hr end

    -- 设置键盘的合作级别
    hr = self.m_pKeyboard:SetCooperativeLevel(hWnd, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND)
    if hr ~= S_OK then return hr end

    -- 设置鼠标数据缓冲区大小
    local dipdw = {}
    dipdw.diph = { dwSize = ffi.sizeof(DIPROPDWORD), dwHeaderSize = ffi.sizeof(DIPROPHEADER), dwObj = 0, dwHow = DIPH_DEVICE, dwData = BUFFER_SIZE }
    hr = self.m_pMouse:SetProperty(DIPROP_BUFFERSIZE, dipdw.diph)
    if hr ~= S_OK then return hr end

    -- 设置键盘数据缓冲区大小
    dipdw.diph.dwSize = ffi.sizeof(DIPROPDWORD)
    dipdw.diph.dwHeaderSize = ffi.sizeof(DIPROPHEADER)
    dipdw.diph.dwObj = 0
    dipdw.diph.dwHow = DIPH_DEVICE
    dipdw.dwData = BUFFER_SIZE
    hr = self.m_pKeyboard:SetProperty(DIPROP_BUFFERSIZE, dipdw.diph)
    if hr ~= S_OK then return hr end

    -- 获取鼠标速度
    self:SetMouseSpeed()

    return S_OK
end

-- 更新输入状态
function CDirectInput:UpdateInput()
    self:OnMouseInput()
    self:OnKeyboardInput()
end

-- 设置鼠标移动限制
function CDirectInput:SetMouseMoveLimit(x, y)
    self.m_mouse_x = 0
    self.m_mouse_y = 0
    self.m_mouse_z = 0
    self.m_limit_x = x
    self.m_limit_y = y
end

-- 设置鼠标位置
function CDirectInput:SetMousePosition(x, y)
    self.m_mouse_x = x
    self.m_mouse_y = y
end

-- 处理键盘输入
function CDirectInput:OnKeyboardInput()
    if self.m_pKeyboard then
        local didod = {}  -- 接收缓冲数据
        local dwElements
        local hr = DIERR_INPUTLOST

        while DI_OK ~= hr do
            dwElements = BUFFER_SIZE
            hr = self.m_pKeyboard:GetDeviceData(ffi.sizeof(DIDEVICEOBJECTDATA), didod, dwElements, 0)

            if hr ~= DI_OK then
                hr = self.m_pKeyboard:Acquire()
                if hr ~= S_OK then return end
            end
        end

        for i = 1, dwElements do
            local key = didod[i].dwOfs & 0xFF
            if didod[i].dwData & MSB then
                self.m_key[key] = true
                if self.m_fp_keyboard_event_receiver then
                    self.m_fp_keyboard_event_receiver(CDirectInput.KEYDOWN, key)
                end
            else
                self.m_key[key] = false
                if self.m_fp_keyboard_event_receiver then
                    self.m_fp_keyboard_event_receiver(CDirectInput.KEYUP, key)
                end
            end
        end
    end
end

-- 处理鼠标输入
function CDirectInput:OnMouseInput()
    local bDone = false
    local od = {}
    local dwElements
    local hr

    if not self.m_pMouse then return end

    -- 初始化鼠标按键状态
    self.m_lb_down = false
    self.m_rb_down = false
    self.m_cb_down = false
    self.m_lb_up = false
    self.m_rb_up = false
    self.m_cb_up = false

    while not bDone do
        dwElements = 1
        hr = self.m_pMouse:GetDeviceData(ffi.sizeof(DIDEVICEOBJECTDATA), od, dwElements, 0)

        if hr ~= DI_OK then
            self.m_pMouse:Acquire()
            break
        end

        if hr ~= DI_OK or dwElements == 0 then break end

        -- 处理鼠标移动和按键事件
        if od.dwOfs == DIMOFS_X then
            self.m_mouse_x = math.max(0, math.min(self.m_mouse_x + self:GetMouseAcceleration(od.dwData), self.m_limit_x))
            if self.m_fp_mouse_event_receiver then
                self.m_fp_mouse_event_receiver(CDirectInput.MOVE, self.m_mouse_x, self.m_mouse_y, self.m_mouse_z)
            end
        elseif od.dwOfs == DIMOFS_Y then
            self.m_mouse_y = math.max(0, math.min(self.m_mouse_y + self:GetMouseAcceleration(od.dwData), self.m_limit_y))
            if self.m_fp_mouse_event_receiver then
                self.m_fp_mouse_event_receiver(CDirectInput.MOVE, self.m_mouse_x, self.m_mouse_y, self.m_mouse_z)
            end
        elseif od.dwOfs == DIMOFS_Z then
            self.m_mouse_z = self.m_mouse_z + od.dwData
            if self.m_fp_mouse_event_receiver then
                if od.dwData < 0 then
                    self.m_fp_mouse_event_receiver(CDirectInput.WHEELDOWN, self.m_mouse_x, self.m_mouse_y, self.m_mouse_z)
                else
                    self.m_fp_mouse_event_receiver(CDirectInput.WHEELUP, self.m_mouse_x, self.m_mouse_y, self.m_mouse_z)
                end
            end
        elseif od.dwOfs == DIMOFS_BUTTON0 or od.dwOfs == DIMOFS_BUTTON1 then
            if (self.m_bSwapMouseButtons and od.dwOfs == DIMOFS_BUTTON1) or (not self.m_bSwapMouseButtons and od.dwOfs == DIMOFS_BUTTON0) then
                if od.dwData & MSB then
                    self.m_lb_down = true
                    if self.m_fp_mouse_event_receiver then
                        self.m_fp_mouse_event_receiver(CDirectInput.LEFTDOWN, self.m_mouse_x, self.m_mouse_y, self.m_mouse_z)
                    end
                else
                    self.m_lb_up = true
                    if self.m_fp_mouse_event_receiver then
                        self.m_fp_mouse_event_receiver(CDirectInput.LEFTUP, self.m_mouse_x, self.m_mouse_y, self.m_mouse_z)
                    end
                end
            end

            if (self.m_bSwapMouseButtons and od.dwOfs == DIMOFS_BUTTON0) or (not self.m_bSwapMouseButtons and od.dwOfs == DIMOFS_BUTTON1) then
                if od.dwData & MSB then
                    self.m_rb_down = true
                    if self.m_fp_mouse_event_receiver then
                        self.m_fp_mouse_event_receiver(CDirectInput.RIGHTDOWN, self.m_mouse_x, self.m_mouse_y, self.m_mouse_z)
                    end
                else
                    self.m_rb_up = true
                    if self.m_fp_mouse_event_receiver then
                        self.m_fp_mouse_event_receiver(CDirectInput.RIGHTUP, self.m_mouse_x, self.m_mouse_y, self.m_mouse_z)
                    end
                end
            end

            bDone = true
        elseif od.dwOfs == DIMOFS_BUTTON2 then
            if od.dwData & MSB then
                self.m_cb_down = true
                if self.m_fp_mouse_event_receiver then
                    self.m_fp_mouse_event_receiver(CDirectInput.CENTERDOWN, self.m_mouse_x, self.m_mouse_y, self.m_mouse_z)
                end
            else
                self.m_cb_up = true
                if self.m_fp_mouse_event_receiver then
                    self.m_fp_mouse_event_receiver(CDirectInput.CENTERUP, self.m_mouse_x, self.m_mouse_y, self.m_mouse_z)
                end
            end

            bDone = true
        end
    end
end

-- 释放 DirectInput 资源
function CDirectInput:FreeDirectInput()
    if self.m_pMouse then
        self.m_pMouse:Unacquire()
        self.m_pMouse:Release()
        self.m_pMouse = nil
    end

    if self.m_pKeyboard then
        self.m_pKeyboard:Unacquire()
        self.m_pKeyboard:Release()
        self.m_pKeyboard = nil
    end

    if self.m_pDI then
        self.m_pDI:Release()
        self.m_pDI = nil
    end
end

return CDirectInput
```

### 说明
1. **类的定义**: 使用 Lua 表和元表模拟 C++ 类。
2. **构造函数和析构函数**: 初始化成员变量，并在对象销毁时释放资源。
3. **初始化和更新**: `InitDI` 方法用于初始化 DirectInput 设备，`UpdateInput` 方法用于更新输入状态。
4. **鼠标和键盘事件处理**: `OnMouseInput` 和 `OnKeyboardInput` 方法处理输入事件。
5. **设置鼠标位置和移动限制**: `SetMousePosition` 和 `SetMouseMoveLimit` 方法用于管理鼠标状态。

### 注意事项
- Lua 中没有指针和引用，因此直接使用对象的方法和属性。
- 需要确保在 Lua 环境中实现 DirectInput 的相关功能，如 `DirectInputCreate` 和数据结构。