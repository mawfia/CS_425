local entity = ...

local enemy = GetSprite(entity)
local health = GetHealth(entity)



if(health.percent == 0)
then
  DestroyEntity(entity)

  for k, v in ipairs(enemies) do
    if(v == entity) then
      table.remove(enemies, k)
    end
  end

  spawn = #enemies
  print(#enemies)
end

--if(math.atan(spaceship.y - enemy.y, spaceship.x - enemy.x) == 0) then
--
  --print("spotted")
--end
