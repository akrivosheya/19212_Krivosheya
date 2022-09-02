definition games;
// #begin# Machine generated header. Do not alter or delete this line.

include ".\\games.vdm_dm"
// #end# Do not alter or delete this line.

class game;

class game
	title: string;
	genre: set of string;
	theme: set of string;  
	players_count: set of string;    
	device: set of string;
	mark: integer := 0;
end;

end.
