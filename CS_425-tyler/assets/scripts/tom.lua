local entity = ...

tom = GetSprite(entity)

if(spawn)
then
  tom.x = math.random()*-1 + math.random()
  tom.y = math.random()*-1 + math.random()
  spawn = false
end

if(tom.x < math.abs(jerry.y) - 0.1)
then

  if(jerry.x > 0)
  then
    tom.x = tom.x + 0.01
  end


  if(jerry.x < 0)
  then
    tom.x = tom.x - 0.01
  end
end
