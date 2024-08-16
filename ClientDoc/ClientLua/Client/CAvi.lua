-- CAVI.lua
--[[
这段代码定义了一个名为 CAVI 的类，用于处理 AVI 和 MPG 视频文件的打开、播放和关闭。主要功能包括：

构造函数: 初始化成员变量。
打开视频: OpenMPG 和 OpenAVI 方法用于打开视频文件并设置窗口位置。
关闭视频: Close 方法用于停止和关闭视频。
播放视频: Play 方法用于播放视频。
停止视频: Stop 方法用于停止视频播放。
--]]
local CAVI = {}
CAVI.__index = CAVI

function CAVI:new()
    local obj = {
        bEndFlag = 0,
        dwID = nil,
        hwnd = nil
    }
    setmetatable(obj, self)
    return obj
end

-- 打开 MPG 视频
function CAVI:OpenMPG(hwnd, szName, w, h)
    self.hwnd = hwnd

    local MciDgvOpenParms = {
        lpstrDeviceType = "MPEGVideo",
        lpstrElementName = szName
    }

    local result = mciSendCommand(nil, MCI_OPEN, MCI_OPEN_ELEMENT | MCI_OPEN_TYPE | MCI_DGV_OPEN_WS, MciDgvOpenParms)

    if result ~= 0 then
        self.dwID = nil
        return false
    end
    
    self.dwID = MciDgvOpenParms.wDeviceID

    -- 位置设置
    local Rect = GetClientRect(hwnd)
    local x = (Rect.right - w) / 2
    local y = (Rect.bottom - h) / 2

    local MciDgvRectParms = {
        rc = {
            left = x,
            top = y,
            right = w,
            bottom = h
        }
    }

    mciSendCommand(self.dwID, MCI_PUT, MCI_ANIM_PUT_DESTINATION | MCI_DGV_RECT, MciDgvRectParms)

    local MciDgvWindowParms = {
        hWnd = hwnd
    }

    mciSendCommand(self.dwID, MCI_WINDOW, MCI_ANIM_WINDOW_HWND, MciDgvWindowParms)

    return true
end

-- 打开 AVI 视频
function CAVI:OpenAVI(hwnd, szName, w, h)
    self.hwnd = hwnd

    local MciDgvOpenParms = {
        lpstrDeviceType = "AVIVideo",
        lpstrElementName = szName
    }

    local result = mciSendCommand(nil, MCI_OPEN, MCI_OPEN_ELEMENT | MCI_OPEN_TYPE | MCI_DGV_OPEN_WS, MciDgvOpenParms)

    if result ~= 0 then
        self.dwID = nil
        return false
    end
    
    self.dwID = MciDgvOpenParms.wDeviceID

    -- 位置设置
    local Rect = GetClientRect(hwnd)
    local x = (Rect.right - w) / 2
    local y = (Rect.bottom - h) / 2

    local MciDgvRectParms = {
        rc = {
            left = x,
            top = y,
            right = w,
            bottom = h
        }
    }

    mciSendCommand(self.dwID, MCI_PUT, MCI_ANIM_PUT_DESTINATION | MCI_DGV_RECT, MciDgvRectParms)

    local MciDgvWindowParms = {
        hWnd = hwnd
    }

    mciSendCommand(self.dwID, MCI_WINDOW, MCI_ANIM_WINDOW_HWND, MciDgvWindowParms)

    return true
end

-- 关闭视频
function CAVI:Close()
    if self.dwID ~= nil then
        local MciPlayParms = {}
        mciSendCommand(self.dwID, MCI_STOP, MCI_NOTIFY, MciPlayParms)
        mciSendCommand(self.dwID, MCI_CLOSE, 0, nil)
        self.dwID = nil
    end
end

-- 播放视频
function CAVI:Play()
    if self.dwID == nil then return false end

    local MciPlayParms = {
        dwCallback = self.hwnd
    }
    mciSendCommand(self.dwID, MCI_PLAY, MCI_NOTIFY, MciPlayParms)

    return true
end

-- 停止视频
function CAVI:Stop()
    if self.dwID ~= nil then
        local MciPlayParms = {}
        mciSendCommand(self.dwID, MCI_STOP, MCI_WAIT, MciPlayParms)
    end
end

return CAVI
