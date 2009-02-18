itemtype = { }
itemtype_list = { }
function itemtype:new(typename)
   newitemtype = { name = typename, usewith = { } }
   setmetatable(newitemtype, { __index = itemtype } )
   table.insert(itemtype_list, newitemtype)
   newitemtype.ID = table.maxn(itemtype_list)
   return newitemtype
end
function itemtype:find(typename)
   if (type(typename)=="string") then -- search by type name
      for i, itemtype in pairs(itemtype_list) do
         if (itemtype.name == typename) then
            return itemtype
         end
      end
   elseif (type(typename)=="number") then -- search by type id
      for i, itemtype in pairs(itemtype_list) do
         if(itemtype.ID == typename) then
            return itemtype
         end
      end
   end
end
function finditemtype(typename)
   return itemtype:find(typename)
end
