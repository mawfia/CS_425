local entity = ...

enemies = {}

maxSpeed = 0.02
maxForce = 0.05
desiredSeparation = .3
neighbordist = 1.5

if(spawn)
then
  spawn = false

  local enemy1 = Sprite.new("enemy", 0.1, 180, 0.5, 0.5, 0)
  local id1 = CreateSprite(enemy1)
  GetScript(id1).name = "assets/scripts/enemy.lua"
  GetHealth(id1).percent = 100
  local velocity1 = GetVelocity(id1)
  velocity1.x = (math.random() - math.random())*0.01
  velocity1.y = (math.random() - math.random())*0.01
  local acceleration1 = GetAcceleration(id1)
  acceleration1.x = 0
  acceleration1.y = 0

  enemies[0] = id1
  --print(id1)

  local enemy2 = Sprite.new("enemy", 0.1, 180, -0.5, 0.5, 0)
  local id2 = CreateSprite(enemy2)
  GetScript(id2).name = "assets/scripts/enemy.lua"
  GetHealth(id2).percent = 100
  local velocity2 = GetVelocity(id2)
  velocity2.x = (math.random() - math.random())*0.01
  velocity2.y = (math.random() - math.random())*0.01
  local acceleration2 = GetAcceleration(id2)
  acceleration2.x = 0
  acceleration2.y = 0

  enemies[0] = id2
  --print(id2)

end

  --enemy.x = math.random() - math.random()
  --tom.y = math.random()*-1 + math.random()
  --print(math.random())
  --enemy.y = 0.5
  --enemy.x = 0.5
