local entity = ...

--print(entity)

--GetSprite(entity).scale = 0.15

--GetSprite(entity).rotate = 0.2 + GetSprite(entity).rotate

jerry = GetSprite(entity)

if(#Keys > 0)
then
    for k, v in pairs(Keys) do

      if(k == 262)
      then
        GetSprite(entity).x = 0.1 + GetSprite(entity).x
        --print(jerry.x, jerry.y)
      end

      if(k == 263)
      then
        GetSprite(entity).x = -0.1 + GetSprite(entity).x
        --print(jerry.x, jerry.y)
      end

      if(k == 264)
      then
        jerry.y = jerry.y - 0.1
        PlaySound("blurp")
        --print(jerry.x, jerry.y)
      end

      if(k == 265)
      then
        jerry.y = jerry.y + 0.1
        --print(jerry.x, jerry.y)
      end
    end
end
