print("The game has begun!");

local board = {};

function makeMove(cell, player)
	if not board[cell] then
		board[cell] = player
	end
end