

function UseHatchetWithTree(User,SourceItem,TargetItem)
   print("Du schlägst mit der Axt heftig auf den Baum ein!");
   TargetItem.type="Chopped Tree";
   LooseEnergy(User, 100)
   print("Du wirst leicht erschoepft (energy:"..User:data().energy..")")
end

function CreateCharacter(CharT)
   CharT.energy = 1000
end

function LooseEnergy(Char, EnergyLoss)
   Char:data().energy = Char:data().energy - EnergyLoss
end
