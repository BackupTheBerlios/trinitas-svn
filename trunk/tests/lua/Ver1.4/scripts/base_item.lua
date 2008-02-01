item = { }
function item:new(typename)
   type = itemtype:find(typename)
   newitem = { type = type, name = type.name }
   setmetatable(newitem, { __index = item } )
   RegisterObject(newitem)
   return newitem
end

function UseHatchetWithTree(User,SourceItem,TargetItem)
   User:LooseEnergy(100)
   TargetItem.type = itemtype:find("ChoppedTree")
end
