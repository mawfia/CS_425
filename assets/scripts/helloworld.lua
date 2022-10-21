
local entity = ...
--print("Entity ID is: ", entity)

s2 = Sprite.new("sally")


--GetSprite(1).rotate = 0.2 + GetSprite(1).rotate

--print(sprite1.name)

--print("hi!")


if(#Keys > 0)
then
    for k, v in pairs(Keys) do

      if(k == 262)
      then
        GetSprite(2).x = 0.1 + GetSprite(2).x
      end

      if(k == 263)
      then
        GetSprite(2).x = -0.1 + GetSprite(2).x
      end


    end
end

--end
