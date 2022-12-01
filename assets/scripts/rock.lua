local entity = ...

local velocity = GetVelocity(entity)

if(rock1 == 200) then
  velocity.x = (math.random() - math.random())*0.003
  velocity.y = (math.random() - math.random())*0.003
  rock1 = 0
else
  rock1 = rock1 + 1
end

if(rock2 == 20) then
  GetSprite(entity).x = GetSprite(entity).x + velocity.x
  GetSprite(entity).y = GetSprite(entity).y + velocity.y
  rock2 = 0
else
  rock2 = rock2 + 1
end
