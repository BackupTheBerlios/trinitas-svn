-- hatchet.lua

TYPE_HATCHET = itemtype:new("Hatchet")
TYPE_TREE = itemtype:new("Tree")
TYPE_CHOPPEDTREE = itemtype:new("Chopped Tree")
TYPE_CHOPPEDTREE_EXTREME = itemtype:new("extremly chopped tree")

language:get("de").items[TYPE_HATCHET.ID] = { }
language:get("de").items[TYPE_HATCHET.ID].name = "Axt"
language:get("de").items[TYPE_HATCHET.ID].choptree = "Du schlägst mit der Axt auf den Baum"
language:get("de").items[TYPE_HATCHET.ID].choppedtree = "Der Baum ist nun gefällt"

language:get("en").items[TYPE_HATCHET.ID] = { }
language:get("en").items[TYPE_HATCHET.ID].name = "hatchet"
language:get("en").items[TYPE_HATCHET.ID].choptree = "You chop a tree with your hatchet"
language:get("en").items[TYPE_HATCHET.ID].choppedtree = "There is now a chopped tree"

language:get("de").items[TYPE_TREE.ID] = { }
language:get("de").items[TYPE_TREE.ID].name = "Baum"
language:get("en").items[TYPE_TREE.ID] = { }
language:get("en").items[TYPE_TREE.ID].name = "tree"

language:get("de").items[TYPE_CHOPPEDTREE.ID] = { }
language:get("de").items[TYPE_CHOPPEDTREE.ID].name = "gefällter Baum"
language:get("en").items[TYPE_CHOPPEDTREE.ID] = { }
language:get("en").items[TYPE_CHOPPEDTREE.ID].name = "chopped tree"

language:get("de").items[TYPE_CHOPPEDTREE_EXTREME.ID] = { }
language:get("de").items[TYPE_CHOPPEDTREE_EXTREME.ID].name = "extrem gefällter Baum"
language:get("en").items[TYPE_CHOPPEDTREE_EXTREME.ID] = { }
language:get("en").items[TYPE_CHOPPEDTREE_EXTREME.ID].name = "extremly chopped tree"



TYPE_HATCHET.usewith[TYPE_TREE.ID] = function(User,SourceItem,TargetItem)
   User:LooseEnergy(100)
   print(User.language.items[TYPE_HATCHET.ID].choptree)
   TargetItem.type = itemtype:find(TYPE_CHOPPEDTREE.ID)
   print(User.language.items[TYPE_HATCHET.ID].choppedtree)
   event:Start(User,SourceItem,TargetItem,3500,EVENT_USEWITH)
end
TYPE_HATCHET.usewith[TYPE_CHOPPEDTREE.ID] = function(User,SourceItem,TargetItem)
   User:LooseEnergy(300)
   TargetItem.type = itemtype:find(TYPE_CHOPPEDTREE_EXTREME.ID)
   print(User.language.items[TYPE_CHOPPEDTREE_EXTREME.ID].name)
end
