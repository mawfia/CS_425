local entity = ...

local missile = GetSprite(entity)
local health = GetHealth(entity)
local velocity = GetVelocity(entity)

missile.y = missile.y + velocity.y
missile.x = missile.x + velocity.x


if(missile.y > 0.9 or health.percent <= 0)
then
  DestroyEntity(entity)
  missile = nil
  health = nil
  velocity = nil

else

  if(#enemies > 2) then
    local enemy = nil
    local stats = {}
    stats["min"] = 100

    for k, v in ipairs(enemies) do
      enemy = GetSprite(v)
      local dx = missile.x - enemy.x
      local dy = missile.y - enemy.y
      local dist = math.sqrt(dx * dx + dy * dy)

      if(dist < stats["min"]) then
        stats["min"] = dist
        stats["id"] = v
      end
    end
    enemy = GetSprite(stats["id"])
    if(missile.x > enemy.x)
    then
      velocity.x = - 0.02
    end

    if(missile.x < enemy.x)
    then
      velocity.x = 0.02
    end

    if(missile.y < enemy.y)
    then
      local rotate = math.atan(enemy.y - missile.y, enemy.x - missile.x)

      missile.rotate = (math.deg(rotate) - 90) % 360
    end
  end


end
