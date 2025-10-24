print("Core Mod loaded!")

DEBUG = true

-- local function import(moduleName, tbl)
--     tbl = tbl or _G
--     local mod = require(moduleName)
--     for k, v in pairs(mod) do
--         tbl[k] = v
--     end
-- end
--
-- import("main_menu")
-- import("settings_menu")

require("mods/core-mod/main_menu")
require("mods/core-mod/settings_menu")
