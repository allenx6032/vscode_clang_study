BaseItem = 
{
	_name = "NULL",
	_quantity = -1,
	_description = "INVALID_ITEM"
}

function BaseItem:create()
	local b = {}
    setmetatable(b, self)
	b.__index = self
    return b
end

function BaseItem:use()
	print("Item has no use")
end