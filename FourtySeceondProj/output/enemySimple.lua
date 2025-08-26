---
--- Created by lenny.
--- DateTime: 30/10/2023 10:36
---

function move(
        posX, -- Position on the X axis
        posY -- Position on the Y axis
)
    -- put amplitude and frequency random
    
    local amplitude = 5.0 -- Amplitude of the wave
    local frequency = 0.03 -- Frequency of the wave
    posY = amplitude * math.sin(frequency * posX)
    return posX, posY
end
