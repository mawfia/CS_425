local entity = ...

chaser = GetSprite(entity)

spaceship = GetSprite(1)


PathFind(chaser,spaceship.position,chaser.position)  

DestroyEntity(entity)
