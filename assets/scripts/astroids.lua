local entity = ...

local astroids = GetSprite(entity)
local velocity = GetVelocity(entity)

if(astroid1 == 300) then
  velocity.x = (math.random() - math.random())*0.002
  velocity.y = (math.random() - math.random())*0.002
  astroid1 = 0
else
  astroid1 = astroid1 + 1
end

if(astroid2 == 20) then
  GetSprite(entity).x = GetSprite(entity).x + velocity.x
  GetSprite(entity).y = GetSprite(entity).y + velocity.y
  astroid2 = 0
else
  astroid2 = astroid2 + 1
end
