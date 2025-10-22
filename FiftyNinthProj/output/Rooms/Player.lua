Player =
{
	_HP = 100,
	_inventory = {};
}

function Player:displayHP()
	print(self._HP);
end

function Player:addItem(value)
	self._inventory[table.getn(self._inventory) + 1] = value
end

function Player:displayInventory()
	 for key,value in pairs(self._inventory) do 
		print(key,value) 
	 end
end

function Player:useItem(key, room)
	self._inventory[key]:use(key, room)
end