-- ClientConfig.lua

local ClientConfig = {}
ClientConfig.__index = ClientConfig

-- 全局变量
g_pClientConfig = nil

-- 构造函数
function ClientConfig.new()
    local self = setmetatable({}, ClientConfig)

    -- 初始化配置参数
    self.FPS = 16  -- FPS - 应用不适用
    self.MAX_SCREENSHOT = 100  -- 截图数量
    self.DELAY_PLAYER_DEAD = 10 * 1000  -- 玩家死亡后延迟时间（10秒）
    self.DELAY_PLAYER_RESURRECT_TIMEOUT = 60 * 1000  -- 玩家复活超时（1分钟）
    self.MAX_CLIENT_MOVE = 6  -- 客户端可移动的 sector 数量
    self.MAX_CREATURE_MOVE_BUFFER = 2  -- 生物移动缓冲区
    self.MAX_LIGHT_DRAW = 50  -- 最大光源数量
    self.MAX_SOUNDPART = 100  -- 加载的音效数量
    self.MAX_REQUEST_SERVICE = 10  -- 最大请求服务数量
    self.MAX_UPDATE_ONETIME = 6  -- 一次更新的最大帧数
    self.MAX_UPDATE_ONETIME_COUNT = 10  -- 一次更新的最大次数
    self.DELAY_GLOBAL_SAY = 12 * 1000  -- 全局消息延迟（12秒）
    self.DELAY_SYSTEMMESSAGE = 5000  -- 系统消息延迟（5秒）
    self.DELAY_GAMEMESSAGE = 5000  -- 游戏消息延迟（5秒）
    self.MAX_DRAWITEMNAME = 20  -- 屏幕上显示的物品名称数量
    self.MAX_WAIT_PACKET = 15000  -- 等待数据包的最大时间（15秒）
    self.MAX_PROCESS_PACKET = 11  -- 每个循环处理的数据包最大数量
    self.MUSIC_THEME = "MUSIC_TREASURE"  -- 初始音乐
    self.MAX_CHATSTRING = 5  -- 聊天字符串行数
    self.MAX_CHATSTRING_MINUS_1 = 4  -- 聊天字符串最大行数减1
    self.MAX_CHATSTRING_LENGTH = 20  -- 聊天字符串最大长度
    self.MAX_CHATSTRINGLENGTH_PLUS1 = 21  -- 聊天字符串最大长度加1
    self.DELAY_CHATSTRING_KEEP = 1500  -- 聊天字符串保持时间（1.5秒）
    self.DELAY_CHATSTRING_FADE = 250  -- 聊天字符串淡出时间（0.25秒）
    self.VALUE_CHATSTRING_FADE = 8  -- 淡出值
    self.MIN_CHATSTRING_COLOR256 = 96  -- 最暗聊天字符串颜色
    self.MAX_TEXTUREPART_EFFECT = 25  -- 纹理部件数量
    self.MAX_TEXTUREPART_CREATURESHADOW = 100  -- 生物阴影数量
    self.MAX_TEXTUREPART_IMAGEOBJECTSHADOW = 100  -- 图像对象阴影数量
    self.MAX_TEXTUREPART_ADDON_SHADOW = 200  -- 附加阴影数量
    self.MAX_TEXTUREPART_IMAGEOBJECTSPK = 20  -- 图像对象包数量
    self.FONT_HEIGHT = 20  -- 字体高度
    self.FONT_ITEM_HEIGHT = 15  -- 物品字体高度
    self.MAX_HP_BAR_PIXEL = 120  -- HP条的大小
    self.POSITION_HP_BAR = -10  -- HP条位置
    self.PERCENTAGE_ITEM_SOMEWHAT_BROKEN = 25  -- 25%时显示为橙色
    self.PERCENTAGE_ITEM_ALMOST_BROKEN = 10  -- 10%时显示为红色
    self.FRAME_DRAW_ORIGINAL_SPRITE = 8  -- 每8帧显示一次原始精灵
    self.COLOR_OUTLINE_INTERACTIONOBJECT = (0 << 11) | (31 << 6) | 0  -- 交互对象轮廓颜色（绿色）
    
    -- 物品颜色
    self.COLOR_NAME_ITEM = {31, 31, 31}  -- 白色
    self.COLOR_NAME_ITEM_OPTION = {31, 31, 5}  -- 几乎蓝色
    self.COLOR_NAME_ITEM_RARE_OPTION = {19, 19, 31}  -- 几乎蓝色
    self.COLOR_OUTLINE_ITEM = (23 << 11) | (23 << 6) | 23  -- 物品轮廓颜色

    -- 种族颜色
    self.COLOR_NAME_VAMPIRE = {31, 10, 10}  -- 红色
    self.COLOR_NAME_SLAYER = {23, 23, 31}  -- 蓝色
    self.COLOR_NAME_NPC = {5, 27, 5}  -- 绿色
    self.COLOR_OUTLINE_NPC = (5 << 11) | (23 << 6) | 5  -- NPC轮廓颜色
    self.COLOR_OUTLINE_ATTACK_POSSIBLE = (23 << 11) | (5 << 6) | 5  -- 可攻击轮廓颜色
    self.COLOR_OUTLINE_ATTACK_IMPOSSIBLE = (5 << 11) | (5 << 6) | 18  -- 不可攻击轮廓颜色

    -- HP条颜色
    self.COLOR_HP_BAR_R = 15
    self.COLOR_HP_BAR_G = 16
    self.COLOR_HP_BAR_B = 15

    -- 新用户注册模式
    self.NEW_USER_REGISTERATION_MODE = "NUR_HOMEPAGE"  -- 新用户注册模式
    self.URL_HOMEPAGE = "http://www.darkeden.com"  -- 主页
    self.URL_HOMEPAGE_NEW_USER = "http://www.darkeden.com/pg/new_reg.html"  -- 新用户注册URL
    self.URL_HOMEPAGE_BILING = "http://www.darkeden.com/pg/buy_index.html"  -- 账单URL

    -- 性向颜色
    self.COLOR_NAME_GOOD_MORE = {50, 50, 200}  -- 更好的颜色
    self.COLOR_NAME_GOOD = {25, 210, 220}  -- 好的颜色
    self.COLOR_NAME_NEUTRAL = {128, 128, 128}  -- 中立的颜色
    self.COLOR_NAME_EVIL = {200, 50, 50}  -- 恶的颜色
    self.COLOR_NAME_EVIL_MORE = {110, 25, 25}  -- 更恶的颜色

    -- 血液掉落
    self.BLOOD_DROP_HP_PERCENT = 30  -- 血液掉落开始的HP百分比
    self.BLOOD_DROP_GAP_TIME = 3000  -- 下一次血液掉落的时间间隔
    self.BLOOD_DROP_RANDOM_TIME = 3000  -- 血液掉落时间 = 间隔 + 随机时间

    self.MAX_TEXTUREPART_EFFECTSHADOW = 3  -- 最大效果阴影数量
    self.AFTER_TRADE_ITEM_DROP_DELAY = 3000  -- 交易后物品掉落延迟
    self.AFTER_PARTY_KICK_DELAY = 60 * 60 * 1000  -- 组队后踢人延迟（1小时）

    -- 客户端通信使用的UDP端口
    self.CLIENT_COMMUNICATION_UDP_PORT = 9858  -- UDP端口
    self.CLIENT_COMMUNICATION_STATUS_DELAY = 5000  -- 状态延迟

    -- 交易取消后接受的延迟时间
    self.TRADE_ACCEPT_DELAY_TIME = 5000  -- 交易接受延迟

    -- 吸血鬼再生量
    self.REGEN_AMOUNT_BURROW = 4
    self.REGEN_AMOUNT_CASKET = 10
    self.REGEN_AMOUNT_VAMPIRE = 2

    -- 每秒的声音限制
    self.MAX_SOUND_PER_SECOND = 6

    -- 自动攻击和Caps Lock自动攻击限制时间
    self.REPEAT_TIME = 10 * 60 * 1000  -- 10分钟
    self.LOCK_TIME = 10 * 60 * 1000  -- 10分钟

    -- 唯一物品和任务物品颜色设置
    self.UniqueItemColorSet = 405
    self.QuestItemColorSet = 345

    -- HPModifyList数量限制及时间限制（毫秒）
    self.HPModifyListMax = 10
    self.HPModifyListTime = 10000
    self.TRACE_CHARACTER_LIMIT_TIME = 5 * 60 * 1000  -- 限制角色跟随时间（5分钟）

    return self
end

-- 保存到文件
function ClientConfig:SaveToFile(filename)
    local file = io.open(filename, "wb")

    if not file then return false end

    file:write(string.pack("I4", self.FPS))
    file:write(string.pack("I4", self.MAX_SCREENSHOT))
    file:write(string.pack("I4", self.DELAY_PLAYER_DEAD))
    file:write(string.pack("I4", self.MAX_CLIENT_MOVE))
    file:write(string.pack("I4", self.MAX_CREATURE_MOVE_BUFFER))
    file:write(string.pack("I4", self.MAX_LIGHT_DRAW))
    file:write(string.pack("I4", self.MAX_SOUNDPART))
    file:write(string.pack("I4", self.MAX_UPDATE_ONETIME))
    file:write(string.pack("I4", self.MAX_UPDATE_ONETIME_COUNT))
    file:write(string.pack("I4", self.DELAY_GLOBAL_SAY))
    file:write(string.pack("I4", self.DELAY_SYSTEMMESSAGE))
    file:write(string.pack("I4", self.DELAY_GAMEMESSAGE))
    file:write(string.pack("I4", self.MAX_DRAWITEMNAME))
    file:write(string.pack("I4", self.MAX_WAIT_PACKET))
    file:write(string.pack("I4", self.MAX_PROCESS_PACKET))
    file:write(string.pack("I4", self.MUSIC_THEME))
    file:write(string.pack("I4", self.MAX_CHATSTRING))
    file:write(string.pack("I4", self.MAX_CHATSTRING_MINUS_1))
    file:write(string.pack("I4", self.MAX_CHATSTRING_LENGTH))
    file:write(string.pack("I4", self.MAX_CHATSTRINGLENGTH_PLUS1))
    file:write(string.pack("I4", self.DELAY_CHATSTRING_KEEP))
    file:write(string.pack("I4", self.DELAY_CHATSTRING_FADE))
    file:write(string.pack("I4", self.VALUE_CHATSTRING_FADE))
    file:write(string.pack("I4", self.MIN_CHATSTRING_COLOR256))
    file:write(string.pack("I4", self.MAX_TEXTUREPART_EFFECT))
    file:write(string.pack("I4", self.MAX_TEXTUREPART_CREATURESHADOW))
    file:write(string.pack("I4", self.MAX_TEXTUREPART_IMAGEOBJECTSHADOW))
    file:write(string.pack("I4", self.MAX_TEXTUREPART_ADDON_SHADOW))
    file:write(string.pack("I4", self.MAX_TEXTUREPART_IMAGEOBJECTSPK))
    file:write(string.pack("I4", self.FONT_HEIGHT))
    file:write(string.pack("I4", self.FONT_ITEM_HEIGHT))
    file:write(string.pack("I4", self.MAX_HP_BAR_PIXEL))
    file:write(string.pack("I4", self.POSITION_HP_BAR))
    file:write(string.pack("I4", self.PERCENTAGE_ITEM_SOMEWHAT_BROKEN))
    file:write(string.pack("I4", self.PERCENTAGE_ITEM_ALMOST_BROKEN))
    file:write(string.pack("I4", self.FRAME_DRAW_ORIGINAL_SPRITE))
    file:write(string.pack("I4", self.COLOR_OUTLINE_INTERACTIONOBJECT))
    file:write(string.pack("I4", self.COLOR_NAME_ITEM))
    file:write(string.pack("I4", self.COLOR_NAME_ITEM_OPTION))
    file:write(string.pack("I4", self.COLOR_NAME_ITEM_RARE_OPTION))
    file:write(string.pack("I4", self.COLOR_OUTLINE_ITEM))
    file:write(string.pack("I4", self.COLOR_NAME_VAMPIRE))
    file:write(string.pack("I4", self.COLOR_NAME_SLAYER))
    file:write(string.pack("I4", self.COLOR_NAME_NPC))
    file:write(string.pack("I4", self.COLOR_OUTLINE_NPC))
    file:write(string.pack("I4", self.COLOR_OUTLINE_ATTACK_POSSIBLE))
    file:write(string.pack("I4", self.COLOR_OUTLINE_ATTACK_IMPOSSIBLE))
    file:write(string.pack("I1", self.COLOR_HP_BAR_R))
    file:write(string.pack("I1", self.COLOR_HP_BAR_G))
    file:write(string.pack("I1", self.COLOR_HP_BAR_B))
    file:write(string.pack("I4", self.NEW_USER_REGISTERATION_MODE))
    file:write(string.pack("I4", self.URL_HOMEPAGE))
    file:write(string.pack("I4", self.URL_HOMEPAGE_NEW_USER))
    file:write(string.pack("I4", self.URL_HOMEPAGE_BILING))
    file:write(string.pack("I4", self.COLOR_NAME_GOOD_MORE))
    file:write(string.pack("I4", self.COLOR_NAME_GOOD))
    file:write(string.pack("I4", self.COLOR_NAME_NEUTRAL))
    file:write(string.pack("I4", self.COLOR_NAME_EVIL))
    file:write(string.pack("I4", self.COLOR_NAME_EVIL_MORE))
    file:write(string.pack("I4", self.BLOOD_DROP_HP_PERCENT))
    file:write(string.pack("I4", self.BLOOD_DROP_GAP_TIME))
    file:write(string.pack("I4", self.BLOOD_DROP_RANDOM_TIME))
    file:write(string.pack("I4", self.MAX_TEXTUREPART_EFFECTSHADOW))
    file:write(string.pack("I4", self.MAX_TEXTUREPART_SCREENEFFECT))
    file:write(string.pack("I4", self.MAX_REQUEST_SERVICE))
    file:write(string.pack("I4", self.AFTER_TRADE_ITEM_DROP_DELAY))
    file:write(string.pack("I4", self.DELAY_PLAYER_RESURRECT_TIMEOUT))
    file:write(string.pack("I4", self.AFTER_PARTY_KICK_DELAY))
    file:write(string.pack("I4", self.CLIENT_COMMUNICATION_UDP_PORT))
    file:write(string.pack("I4", self.CLIENT_COMMUNICATION_STATUS_DELAY))
    file:write(string.pack("I4", self.TRADE_ACCEPT_DELAY_TIME))
    file:write(string.pack("I1", self.REGEN_AMOUNT_BURROW))
    file:write(string.pack("I1", self.REGEN_AMOUNT_CASKET))
    file:write(string.pack("I1", self.REGEN_AMOUNT_VAMPIRE))
    file:write(string.pack("I1", self.MAX_SOUND_PER_SECOND))
    file:write(string.pack("I4", self.REPEAT_TIME))
    file:write(string.pack("I4", self.LOCK_TIME))
    file:write(string.pack("I4", self.UniqueItemColorSet))
    file:write(string.pack("I4", self.QuestItemColorSet))
    file:write(string.pack("I1", self.HPModifyListMax))
    file:write(string.pack("I4", self.HPModifyListTime))
    file:write(string.pack("I4", self.TRACE_CHARACTER_LIMIT_TIME))

    file:close()
    return true
end

-- 从文件加载
function ClientConfig:LoadFromFile(filename)
    local file = io.open(filename, "rb")

    if not file then return false end

    self.FPS = string.unpack("I4", file:read(4))
    self.MAX_SCREENSHOT = string.unpack("I4", file:read(4))
    self.DELAY_PLAYER_DEAD = string.unpack("I4", file:read(4))
    self.MAX_CLIENT_MOVE = string.unpack("I4", file:read(4))
    self.MAX_CREATURE_MOVE_BUFFER = string.unpack("I4", file:read(4))
    self.MAX_LIGHT_DRAW = string.unpack("I4", file:read(4))
    self.MAX_SOUNDPART = string.unpack("I4", file:read(4))
    self.MAX_UPDATE_ONETIME = string.unpack("I4", file:read(4))
    self.MAX_UPDATE_ONETIME_COUNT = string.unpack("I4", file:read(4))
    self.DELAY_GLOBAL_SAY = string.unpack("I4", file:read(4))
    self.DELAY_SYSTEMMESSAGE = string.unpack("I4", file:read(4))
    self.DELAY_GAMEMESSAGE = string.unpack("I4", file:read(4))
    self.MAX_DRAWITEMNAME = string.unpack("I4", file:read(4))
    self.MAX_WAIT_PACKET = string.unpack("I4", file:read(4))
    self.MAX_PROCESS_PACKET = string.unpack("I4", file:read(4))
    self.MUSIC_THEME = string.unpack("I4", file:read(4))
    self.MAX_CHATSTRING = string.unpack("I4", file:read(4))
    self.MAX_CHATSTRING_MINUS_1 = string.unpack("I4", file:read(4))
    self.MAX_CHATSTRING_LENGTH = string.unpack("I4", file:read(4))
    self.MAX_CHATSTRINGLENGTH_PLUS1 = string.unpack("I4", file:read(4))
    self.DELAY_CHATSTRING_KEEP = string.unpack("I4", file:read(4))
    self.DELAY_CHATSTRING_FADE = string.unpack("I4", file:read(4))
    self.VALUE_CHATSTRING_FADE = string.unpack("I4", file:read(4))
    self.MIN_CHATSTRING_COLOR256 = string.unpack("I4", file:read(4))
    self.MAX_TEXTUREPART_EFFECT = string.unpack("I4", file:read(4))
    self.MAX_TEXTUREPART_CREATURESHADOW = string.unpack("I4", file:read(4))
    self.MAX_TEXTUREPART_IMAGEOBJECTSHADOW = string.unpack("I4", file:read(4))
    self.MAX_TEXTUREPART_ADDON_SHADOW = string.unpack("I4", file:read(4))
    self.MAX_TEXTUREPART_IMAGEOBJECTSPK = string.unpack("I4", file:read(4))
    self.FONT_HEIGHT = string.unpack("I4", file:read(4))
    self.FONT_ITEM_HEIGHT = string
end