local entity = ...

enemy = GetSprite(entity)
local health = GetHealth(entity)



if(health.percent == 0)
then
  DestroyEntity(entity)
  --spawn = true
end
