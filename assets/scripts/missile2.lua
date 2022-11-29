local entity = ...

local missile = GetSprite(entity)
local health = GetHealth(entity)
local velocity = GetVelocity(entity)

--GetSprite(entity).scale = 0.02

if(missile.index < 2) then
  missile.index = missile.index + 1
else
  missile.index = 0
end

--[[


if(math.abs(missile.y) > 0.9) then
  DestroyEntity(entity)
end
--]]

--print(missile1.x, missile1.y)

GetSprite(entity).x = GetSprite(entity).x + (GetVelocity(entity).x + GetAcceleration(entity).x)
GetSprite(entity).y = GetSprite(entity).y + (GetVelocity(entity).y + GetAcceleration(entity).y)

if(GetAcceleration(entity).x > (GetVelocity(entity).x * 3)) then
  GetAcceleration(entity).x  = GetAcceleration(entity).x / 2
end

if(GetAcceleration(entity).y > (GetVelocity(entity).y * 3)) then
  GetAcceleration(entity).y = GetAcceleration(entity).y / 2
end
--missile.x = missile.x + veolcity.x
--missile.y = missile.y + velocity.y

--GetSprite(entity).x = missile.x
--GetSprite(entity).y = missile.y

if(health.percent == 0) then
  DestroyEntity(entity)

else

  if(missile.x > 0.9 or missile.y > 0.9) then
    DestroyEntity(entity)
  end

  if(missile.x < -0.9 or missile.y < -0.9) then
    DestroyEntity(entity)
  end

end
