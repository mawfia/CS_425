local entity = ...

--missile = GetSprite(entity)

--spaceship.rotate = 45

if(Keys[32])
then

  rate1 = rate1 + 1

  --local test = math.atan(enemy.y - spaceship.y, enemy.x - spaceship.x)

  --test = (math.deg(test) - 90) % 360


  if(rate1 == 3)
  then
    local id = CreateSprite(Sprite.new("missile", 0.03, 0, spaceship.x, spaceship.y + 0.05, 0))
    GetScript(id).name = "assets/scripts/missile.lua"
    GetHealth(id).percent = 100
    rate1 = 0
  end


  --if(#enemies > 0) then
  --local enemy = GetSprite(enemies[1])
  --print(enemy.rotate)
  --local rotate = math.atan(spaceship.y - enemy.y, spaceship.x - enemy.x)
  --print(enemy.rotate, (math.deg(rotate) - 90) % 360)

  --rotate = (math.deg(rotate) - 90) % 360

  --rotate = rotate * (180 / 3.14159265359)
  --local calc = (360 - math.abs(enemy.rotate))
  --print(enemy.rotate, rotate, calc)
  --end
  --print(calc)

end
