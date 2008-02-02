language = { }
language_list = { }
default_language = nil
function language:new(lng,lng_short)
   newlng = { name = lng, short = lng_short, items = { } }
   setmetatable(newlng, { __index = language } )
   table.insert(language_list,newlng)
   if (default_language==nil) then
      default_language = newlng
   end
   return newlng
end
function language:get(lng_short)
   for i, type in pairs(language_list) do
      if (type.short == lng_short) then
         return type
      end
   end
   return default_language
end

-- First language will be set es default
language:new("English","en")
language:new("Deutsch","de")
