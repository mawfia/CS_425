local entity = ...

spaceship = GetSprite(entity)
local health = GetHealth(entity)


if(health.percent <= 0) then

  if(spaceship.index < 31) then
    spaceship.index = spaceship.index + 1

  else
    DestroyEntity(entity)
    spaceship = nil
  end

end


if(#Keys > 0)
then

    for k, v in pairs(Keys) do

      if(k == 262)
      then
        --GetSprite(entity).x = 0.1 + GetSprite(entity).x
        --print(jerry.x, jerry.y)
        --PlaySound("blurp")
        spaceship.x = spaceship.x + .05
        --spaceship.rotate = spaceship.rotate + 2
      end

      if(k == 263)
      then
        --GetSprite(entity).x = -0.1 + GetSprite(entity).x
        --print(jerry.x, jerry.y)
        --PlaySound("blurp")
        spaceship.x = spaceship.x - .05
        --spaceship.rotate = spaceship.rotate - 2
      end

      if(k == 264)
      then
        spaceship.y = spaceship.y - 0.05
        --PlaySound("blurp")
        --print(jerry.x, jerry.y)
      end

      if(k == 265)
      then
        spaceship.y = spaceship.y + 0.05
        --PlaySound("blurp")
        --print(jerry.x, jerry.y)
      end
    end
end
