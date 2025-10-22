--DO NOT ALTER

--[[
If you want to use external definitions located in a different file you can use the require keyword:
require("FILEPATH/FILENAME.lua")
]]--

package.path = package.path .. ";Rooms/Items/?.lua"
require("TestItem")

--[[
	All room files must have 3  things
	1. the Room definition
	2. a list of exits
	3. a function Room:main()
	Please keep the naming conventions.
--]]

--This is the room definition, for now it only needs a _roomName and an _exitCount
Room = 
{
	_roomName = "Entrance";
	_exitCount = 3
}

--This is the list of exits, number must match the number in _exitCount
Room["_exits"] = {"FOREST", "DESERT", "BEACH"}

--This is the main function. It is the first thing called when your room is loaded
function Room:main()
	--You use print to print sentences
	print("You wake up on the floor of a dark room")
	print("As your vision adjusts to the darkness, you see 3 passages")
	print("1. Through the first passage you can make out what looks like a cactus")
	print("2. You can hear waves from the second passage")
	print("3. The final passage has the scent of wet bark")
	--Below is how to get input. You simply call "room.GetInput(room.__object, MESSAGE_TO_DISPALY)" the message must be in quotes but is optional. 
	--In the example below, the value of the input is stored in selection as a word
	local selection = room.GetInput(room.__object, "Which door do you choose?: ")
	--Using input you cna create puzzle and branches and so forth
	--Here we call 3 different function based on input, these function can be named anythign you want and do anything you want I dont care
	local test = TestItem.create()
	test:use()
	if(selection == "1") then
		room.SelectionDesert();
	elseif(selection == "2") then
		room.SelectionBeach();
	elseif(selection == "3") then
		room.SelectionForest();
	else
		print(selection)
	end
end

--Here is a function definition
--The signature must be "function Room:FUNCTION_NAME(Arguement 1, Arguement 2...)"
--The function here takes no arguements
function Room:SelectionDesert()
	print("As you enter the passage, you are met with a door")
	--using tonumber("something") we can convert the number that is a word to an actual number
	--Here it is used to check a basic question
	local answer = tonumber(room.GetInput(room.__object, "What is 2+2: "))
	if(answer == 4) then
		print("The door open and you walk towards the sand")
		--If you wish to chnage the room call "room.ChangeRoom(room.__object, "CATEGORY_OF_ROOM")"
		--You can check available room categories in the RoomDirectory.lua file located in the root folder
		room.ChangeRoom(room.__object,"Desert")
	else
		print("You die")
	end
end

--This is an example of a function with arguements
function exampleWithArgs(x,y)
	print(x*y);
end

function Room:SelectionBeach()
	print("As you enter the passage, you are met with a door")
	local answer = tonumber(room.GetInput(room.__object, "What is 2+2: "))
	if(answer == 4) then
		print("The door open and you walk towards the beach")
		room.ChangeRoom(room.__object,"Beach")
	else
		print("You die")
	end
end

function Room:SelectionForest()
	print("As you enter the passage, you are met with a door")
	local answer = tonumber(room.GetInput(room.__object, "What is 2+2: "))
	if(answer == 4) then
		print("The door open and you walk towards the Forest")
		room.ChangeRoom(room.__object,"Forest")
	else
		print("You die")
	end
end