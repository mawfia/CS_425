local entity = ...

local enemy = GetSprite(entity)
local health = GetHealth(entity)
local velocity = GetVelocity(entity)


if(health.percent < 100) then

  if(enemy.index < 10) then
    enemy.index = enemy.index + 1
  end

  if(enemy.index == 10) then
    DestroyEntity(entity)
    PlaySound("explosion2")
    for k, v in ipairs(enemies) do
      if(v == entity) then
        table.remove(enemies, k)
        spawn = #enemies
      end
    end
  end

else

  if(not (spaceship == nil)) then
    local rotate = math.atan(spaceship.y - enemy.y, spaceship.x - enemy.x)
    rotate = (math.deg(rotate) - 90) % 360

    local diff = (360 - math.abs(enemy.rotate)) - rotate

    if( diff < 2 and diff > -2 ) then


      rate2 = rate2 + 1

      if(rate2 == 3) then
        local id = CreateSprite(Sprite.new("missile2", 0.02, enemy.rotate, enemy.x, enemy.y, 0))
        GetScript(id).name = "assets/scripts/missile2.lua"
        GetHealth(id).percent = 100
        local velocity_m = Velocity.new(velocity.x, velocity.y)

        GetVelocity(id).x = velocity_m.x
        GetVelocity(id).y = velocity_m.y
        GetAcceleration(id).x = velocity_m.x * 5
        GetAcceleration(id).y = velocity_m.y * 5

        PlaySound("missile2")
        rate2 = 0
      end
    end
  end
end
