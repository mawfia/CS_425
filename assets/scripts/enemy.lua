local entity = ...

enemy = GetSprite(entity)
local health = GetHealth(entity)

if(spawn)
then
  enemy.x = math.random() - math.random()
  --tom.y = math.random()*-1 + math.random()
  --print(math.random())
  enemy.y = 0.5
  --enemy.x = 0.5
  spawn = false
end

if(health.percent == 0)
then
  DestroyEntity(entity)
  spawn = true
end
