character = { }
function character:new(race)
   newchar = { energy = 10000, health = 10000, type = race }
   setmetatable(newchar, { __index = character } )
   RegisterObject(newchar)
   return newchar
end
function character:LooseEnergy(energyloss)
   self.energy = self.energy - energyloss
   if(self.energy<0) then
      self.health = self.health + self.energy
      self.energy = 0
   end
end
