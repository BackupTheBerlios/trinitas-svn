item = { }
function item:new(typename)
   itemtype = itemtype:find(typename)
   newitem = { type = itemtype, name = itemtype.name}
   setmetatable(newitem, { __index = item } )
   RegisterObject(newitem)
   return newitem
end

