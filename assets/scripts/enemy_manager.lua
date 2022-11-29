local entity = ...


maxSpeed = 0.02
maxForce = 0.06
desiredSeparation = .2
neighbordist = 1.5



if(spawn == 0)
then

  enemies = {}

  local index = 1
  while(index < 4) do
    local enemy = Sprite.new("enemy", 0.1, 0, math.random() - math.random(), 0.5, 0)
    local id = CreateSprite(enemy)
    GetScript(id).name = "assets/scripts/enemy.lua"
    GetHealth(id).percent = 100
    local velocity = GetVelocity(id)
    velocity.x = (math.random() - math.random())*0.01
    velocity.y = (math.random() - math.random())*0.01
    local acceleration = GetAcceleration(id)
    acceleration.x = 0
    acceleration.y = 0

    enemies[index] = id
    index = index + 1
    spawn = #enemies

  end
end
