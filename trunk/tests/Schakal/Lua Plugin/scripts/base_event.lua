event = {}

function event:Start(...)
    nargs = select("#",unpack(arg))
    etype = arg[nargs]
    table.remove(arg)
    event[etype](unpack(arg))
end

EVENT_USEWITH = 1
event[EVENT_USEWITH] = function(User,Source,Target,difTime)
   StartEventUsewith(User,Source,Target,difTime)
end
