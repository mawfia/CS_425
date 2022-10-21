local entity = ...

cheese = GetSprite(entity)

--cheese.scale = 0.1

cheese.rotate = cheese.rotate + 0.2


if(jerry.x > (cheese.x - 0.1 ) and jerry.x < (cheese.x + 0.1) and jerry.y > (cheese.y - 0.1)  and jerry.y < (cheese.y + 0.1))
then
  cheese.x = math.random()*-1 + math.random()
  cheese.y = math.random()*-1 + math.random()
  jerry.scale = jerry.scale + 0.02
  PlaySound("win")
end
