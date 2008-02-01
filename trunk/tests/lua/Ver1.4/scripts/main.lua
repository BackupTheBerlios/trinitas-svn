function UseHatchetWithTree(User,SourceItem,TargetItem)
   print("Du schlägst mit der Axt heftig auf den Baum ein!");
   TargetItem.type="Chopped Tree";
   User:LooseEnergy(100)
   print("Du wirst leicht erschoepft (energy:"..User:data().energy..")")
end
