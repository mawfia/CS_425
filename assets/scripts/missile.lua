local entity = ...

local missile = GetSprite(entity)
local health = GetHealth(entity)

missile.y = missile.y + 0.05

if(spawn == false)
then

  if(missile.x > enemy.x)
  then
    missile.x = missile.x - 0.01
    end

    if(missile.x < enemy.x)
    then
      missile.x = missile.x + 0.01
    end

    if(missile.y < .5)
    then
      local rotate = math.atan(enemy.y - missile.y, enemy.x - missile.x)

      missile.rotate = (math.deg(rotate) - 90) % 360
    end
end


if(missile.y > 0.9 or health.percent == 0)
then
  DestroyEntity(entity)
end
