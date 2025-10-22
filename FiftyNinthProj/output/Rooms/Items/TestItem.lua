require "BaseItem"

TestItem = 
{
	_name = "Test Item",
	_quantity = 1,
	_description = "This is a test Item"
}

TestItem.__index = TestItem

function TestItem:create()
	local b = {}
    setmetatable(b, TestItem)
	setmetatable(TestItem,  { __index = BaseItem })
    return b
end

function TestItem:use()
	print(self._description)
end
