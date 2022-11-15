local entity = ...

--missile = GetSprite(entity)

--spaceship.rotate = 45

if(Keys[32])
then
  --missile.scale = 0.1

  count = count + 1

  --local test = math.atan(enemy.y - spaceship.y, enemy.x - spaceship.x)

  --test = (math.deg(test) - 90) % 360

  --spaceship.rotate = test
  --print(test)

  if(count == 2)
  then
    local id = CreateSprite(Sprite.new("missile", 0.1, 0, spaceship.x, spaceship.y + 0.05, 0))
    GetScript(id).name = "assets/scripts/missile.lua"
    GetHealth(id).percent = 100
    count = 0
  end
end
