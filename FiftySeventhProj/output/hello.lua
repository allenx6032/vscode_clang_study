
-- local nk = require("moonnuklear")
-- local backend = require("backend")
--
local op = 'easy'
local value = 0.6
-- local window_flags = moonnuklear.WINDOW_BORDER|moonnuklear.WINDOW_MOVABLE|moonnuklear.WINDOW_CLOSABLE

-- local function hellogui(ctx)
--    if moonnuklear.window_begin(ctx, "Show", {50, 50, 220, 220}, window_flags) then
--       -- fixed widget pixel width
--       moonnuklear.layout_row_static(ctx, 30, 80, 1)
--
--       if moonnuklear.button(ctx, nil, "button") then
--          -- ... event handling ...
--          print("button pressed")
--       end
--
--       -- fixed widget window ratio width
--       moonnuklear.layout_row_dynamic(ctx, 30, 2)
--       if moonnuklear.option(ctx, 'easy', op == 'easy') then op = 'easy' end
--       if moonnuklear.option(ctx, 'hard', op == 'hard') then op = 'hard' end
--
--       -- custom widget pixel width
--       moonnuklear.layout_row_begin(ctx, 'static', 30, 2)
--       moonnuklear.layout_row_push(ctx, 50)
--       moonnuklear.label(ctx, "Volume:", moonnuklear.TEXT_LEFT)
--       moonnuklear.layout_row_push(ctx, 110)
--       value = moonnuklear.slider(ctx, 0, value, 1.0, 0.1)
--       moonnuklear.layout_row_end(ctx)
--    end
--    moonnuklear.window_end(ctx)
-- end

-- Init the backend and enter the event loop:
-- backend.init(640, 380, "Hello", true, nil)
-- backend.loop(hellogui, {.13, .29, .53, 1}, 30)


local value1 = 10
local value2 = 30
sum = Lua2C_Add( value1, value2 )

print("Lua2C file :" .. value1 .. " + " .. value2 .. " = " .. sum)