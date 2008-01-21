function UseHatchetWithTree(SourceItem,TargetItem)
   print("Du schlägst mit der Axt heftig auf den Baum ein!");
   TargetItem.type="Chopped Tree";
end
function TestIt(String1,String2,String3)
   print("-----------------------")
   for variable = 0, -15, -1 do
      CheckStack(variable);
   end
end
function TestIt2(String1,String2)
   print("-----------------------")
   for variable = 0, -15, -1 do
      CheckStack(variable);
   end
end
