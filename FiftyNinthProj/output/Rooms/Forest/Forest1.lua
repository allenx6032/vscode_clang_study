-- script.lua
-- Receives a table, returns the sum of its components.

Room = 
{
	_roomName = "Entrance";
	_exitCount = 3
}

Room["_exits"] = {"FOREST", "DESERT", "BEACH"}

function Room:main()
	print("In desert")
end
