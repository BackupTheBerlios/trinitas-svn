itemtype = { }
itemtype_list = { }
function itemtype:new(typename, typeid)
   print("new itemtype: "..typename)
   newitemtype = { name = typename, id = typeid }
   setmetatable(newitemtype, { __index = itemtype } )
   table.insert(itemtype_list, newitemtype)
   return newitemtype
end
function itemtype:find(typename)
   for i, type in pairs(itemtype_list) do
      if (type.name == typename) then
         return type
      end
   end
end
function finditemtype(typename)
   return itemtype:find(typename)
end
