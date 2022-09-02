module games;
// #begin# Machine generated header. Do not alter or delete this line.
// #end# Do not alter or delete this line.
var $mode : integer;
var $choosengame : integer;
var $choosengametitle : string;
var $w : integer;
var $win : integer;
var $exp : integer;
var $tmp : integer;
var $x,$y:integer := 25;
var $gamesCount : integer := 0;
var $explaination : tuple of string := string[];
var $allGames : tuple of string := string[];
var $allGenres : tuple of string := string[];
var $allThemes : tuple of string := string[];
var $allPlayersCount : tuple of string := string[];
var $allDevices : tuple of string := string[];
var $choosenGenres : tuple of string := string[];
var $choosenThemes : tuple of string := string[];
var $choosenPlayersCount : tuple of string := string[];
var $choosenDevices : tuple of string := string[];
var $io : integer := 1;
var $yo : integer := 10;
var $y1:integer := 10;

function Title()
begin
	var $lx, $ly, $rx, $ry : integer; 
	$lx := 0;
	$ly := 0;
	$rx := 1010;
	$ry := 640;
	$w := MakeWindow("Консультация по выбору игры", $lx, $ly, $rx, $ry);
	BrushColor($w, 1, 0, 1);
	BkColor($w, 1);
	Rectangle($w, 0, 0, 1010,640);
end;

function TupleSelect( $str : string; $tmp : tuple of string ) : tuple of string
begin
var $ret_tuple: tuple of string := string[];
var $r : tuple of integer := Select( 390, 160, $str, $tmp );

 for $i in $r loop
      $ret_tuple:=$ret_tuple+string[$tmp[$i]];
 end;
return $ret_tuple;
end;

function PrintGames()
begin
var $y : integer := 5;

	BrushColor($win, 0, 0, 0); 
	TextColor($win, 1); 
	BkColor($win, 0);
	Rectangle($win,-1,-1, 350,420);
	TextColor($win, 15);
	for $g in $allGames loop
		OutText($win, 5, $y, $g); $y:=$y+16;
	end;
end;

function PrintNoGames()
begin
var $y : integer := 5;

	BrushColor($win, 0, 0, 0); 
	TextColor($win, 1); 
	BkColor($win, 0);
	Rectangle($win,-1,-1, 350,420);
	TextColor($win, 15);
	OutText($win, 5, $y, "Нет подходящих игр");
end;

function RemoveGame($title : string)
begin
var $tmp: tuple of string := string[];

  for $g in $allGames loop
   if $g != $title then $tmp := $tmp + string[$g]; end;
  end;
  $allGames := $tmp;
  $gamesCount := $gamesCount - 1;
end;

rule Stop
=>
	 activate group();
end;

rule ListOfGames
	 forall $currentGame: game(title: $title,  genre: $genre)
=>

	 $allGames := $allGames + string[$title];
	 $gamesCount := $gamesCount + 1;

	 for $g in $genre loop
	 	 if $g in $allGenres then 
		 else
 		 	$allGenres := $allGenres + string[$g];
		end;
	end;
end;

rule TakeGamesWithChoosenGenres
   forall $currentGame: game(title: $title,  genre: $genre)
=>
 RemoveGame($title);

  for $g in $choosenGenres loop
    if $g in $genre then    
      if $currentGame.mark!=1 then
        $allGames := $allGames + string[$title];
        $gamesCount := $gamesCount + 1;
      end;
      edit $currentGame:game(mark : 1);
    end;
  end;
end;

rule ListOfThemes
   forall $currentGame: game(title: $title, theme: $themes)
   when $currentGame.mark = 1
=>
 var $j:integer:=0;
  for $t in $themes loop
   if #$allThemes !=0 then
    for $i in 1..#$allThemes loop
      if $allThemes[$i] = $t then $j:=1; end;
    end;
   end;
    if $j = 0 then $allThemes := $allThemes + string[$t]; end;
    $j:=0;
  end;
end;

rule TakeGamesWithChoosenThemes
   forall $currentGame: game(title: $title,  theme: $theme)
   when $currentGame.mark=1
=>
 RemoveGame($title);
 edit $currentGame:game(mark : 0);
  for $t in $choosenThemes loop
    if $t in $theme then    
      if $currentGame.mark!=1 then
        $allGames := $allGames + string[$title];
        $gamesCount := $gamesCount + 1;
      end;
      edit $currentGame:game(mark : 1);
    end;
  end;
end;

rule ListOfPlayersCount
   forall $currentGame: game(title: $title, players_count: $players)
   when $currentGame.mark = 1
=>
 var $j:integer:=0;
  for $p in $players loop
   if #$allPlayersCount !=0 then
    for $i in 1..#$allPlayersCount loop
      if $allPlayersCount[$i] = $p then $j:=1; end;
   end;
   end;
    if $j = 0 then $allPlayersCount := $allPlayersCount + string[$p]; end;
    $j:=0;
  end;
end;

rule TakeGamesWithChoosenPlayersCount
   forall $currentGame: game(title: $title, players_count: $players)
   when $currentGame.mark=1
=>
 RemoveGame($title);
 edit $currentGame:game(mark : 0);
  for $p in $choosenPlayersCount loop
    if $p in $players then    
      if $currentGame.mark!=1 then
        $allGames := $allGames + string[$title];
        $gamesCount := $gamesCount + 1;
      end;
      edit $currentGame:game(mark : 1);
    end;
  end;
end;

rule ListOfDevices
   forall $currentGame: game(title: $title, device: $device)
   when $currentGame.mark = 1
=>
 var $j:integer:=0;
  for $d in $device loop
   if #$allDevices !=0 then
    for $i in 1..#$allDevices loop
      if $allDevices[$i] = $d then $j:=1; end;
   end;
   end;
    if $j = 0 then $allDevices := $allDevices + string[$d]; end;
    $j:=0;
  end;
end;

rule TakeGamesWithChoosenDevices
   forall $currentGame: game(title: $title, device: $device)
   when $currentGame.mark=1
=>
 RemoveGame($title);
 edit $currentGame:game(mark : 0);
  for $d in $choosenDevices loop
    if $d in $device then    
      if $currentGame.mark!=1 then
        $allGames := $allGames + string[$title];
        $gamesCount := $gamesCount + 1;
      end;
      edit $currentGame:game(mark : 1);
    end;
  end;
end;

rule RightGames
   forall $currentGame: game(title: $title,  genre: $genre, theme: $theme, players_count: $players, device: $device)
   when $currentGame.mark = 1
=>
OutText($tmp, 10,$y1, $title); $y1:=$y1+20;
 OutText($tmp, 10,$y1, " .   Жанры:"); $y1:=$y1+20;
  for $g in $genre loop
    OutText($tmp, 10,$y1, $g); $y1:=$y1+20;
  end;
 OutText($tmp, 10,$y1, " .   Темы:"); $y1:=$y1+20;
  for $t in $theme loop
    OutText($tmp, 10,$y1, $t); $y1:=$y1+20;
  end;
 OutText($tmp, 10,$y1, " .   Количество игроков:"); $y1:=$y1+20;
  for $p in $players loop
    OutText($tmp, 10,$y1, $p); $y1:=$y1+20;
  end;
 OutText($tmp, 10,$y1, " .   Поддерживаемые усттройства:"); $y1:=$y1+20;
  for $d in $device loop
    OutText($tmp, 10,$y1, $d); $y1:=$y1+20;
  end;
  OutText($tmp, 10,$y1, ""); $y1:=$y1+20;


end;

rule ChoosenGame
   forall $currentGame: game(title: $title,  genre: $genre, theme: $theme, players_count: $players, device: $device)
   when $title = $choosengametitle
=>
OutText($tmp, 10,$y1, $title); $y1:=$y1+20;
 OutText($tmp, 10,$y1, " .   Жанры:"); $y1:=$y1+20;
  for $g in $genre loop
    OutText($tmp, 10,$y1, $g); $y1:=$y1+20;
  end;
 OutText($tmp, 10,$y1, " .   Темы:"); $y1:=$y1+20;
  for $t in $theme loop
    OutText($tmp, 10,$y1, $t); $y1:=$y1+20;
  end;
 OutText($tmp, 10,$y1, " .   Количество игроков:"); $y1:=$y1+20;
  for $p in $players loop
    OutText($tmp, 10,$y1, $p); $y1:=$y1+20;
  end;
 OutText($tmp, 10,$y1, " .   Поддерживаемые усттройства:"); $y1:=$y1+20;
  for $d in $device loop
    OutText($tmp, 10,$y1, $d); $y1:=$y1+20;
  end;

end;

begin
	new
	game(title: "Stardew valley",
		genre: {
			"cимулятор",
			"с видом сверху",
			"инди",
			"ролевая",
			"фермерство",
			"песочница"
		},
		theme: {
			"открытый мир",
			"пиксельная",
			"расслабляющая"
		},
		players_count: {
			"для одного игрока",
			"кооператив"
		},
		device: {
			"поддерживающая контроллер",
			"для пк"
		}
	),
	game(title: "Five Nights at Freddy's",
		genre: {
			"point & click",
			"с видом от первого лица",
			"инди",
			"симулятор"
		},
		theme: {
			"хоррор",
			"выживание",
			"тактика",
			"тайна",
			"сложная"
		},
		players_count: {
			"для одного игрока"
		},
		device: {
			"для пк"
		}
	),
	game(title: "The Binding of Isaac",
		genre: {
			"инди",
			"экшен",
			"рогалик",
			"bullet hell",
			"с видом сверху"
		},
		theme: {
			"пиксельная",
			"сложная",
			"хоррор"
		},
		players_count: {
			"для одного игрока",
			"кооператив"
		},
		device: {
			"поддерживающая контроллер",
			"для пк"
		}
	),
	game(title: "Job Simulator",
		genre: {
			"инди",
			"симулятор",
			"песочница",
			"с видом от первого лица"
		},
		theme: {
			"расслабляющая",
			"смешная"
		},
		players_count: {
			"для одного игрока"
		},
		device: {
			"VR"
		}
	),
	game(title: "Assassin's Creed",
		genre: {
			"экшен",
			"приключение",
			"стэлс",
			"с видом от третьего лица"
		},
		theme: {
			"открытый мир",
			"историчиская"
		},
		players_count: {
			"для одного игрока"
		},
		device: {
			"поддерживающая контроллер",
			"для пк"
		}
	),
	game(title: "Mass Effect",
		genre: {
			"экшен",
			"ролевая",
			"шутер",
			"приключение",
			"с видом от третьего лица"
		},
		theme: {
			"открытый мир",
			"фантастика"
		},
		players_count: {
			"для одного игрока"
		},
		device: {
			"для пк"
		}
	),
	game(title: "Counter-Strike: Global Offensive",
		genre: {
			"экшен",
			"шутер",
			"с видом от первого лица"
		},
		theme: {
			"тактика",
			"командная"
		},
		players_count: {
			"онлайн"
		},
		device: {
			"для пк"
		}
	),
	game(title: "Terraria",
		genre: {
			"экшен",
			"ролевая",
			"инди",
			"приключение",
			"песочница",
			"ролевая",
			"платформер",
			"с видом с боку"
		},
		theme: {
			"открытый мир",
			"пиксельная",
			"выживание"
		},
		players_count: {
			"для одного игрока",
			"кооператив"
		},
		device: {
			"поддерживающая контроллер",
			"для пк"
		}
	),
	game(title: "Just Shapes & Beats",
		genre: {
			"экшен",
			"инди",
			"ритмушка",
			"bullet hell"
		},
		theme: {
			"минимализм",
			"смешная"
		},
		players_count: {
			"для одного игрока",
			"кооператив"
		},
		device: {
			"поддерживающая контроллер",
			"для пк"
		}
	),
	game(title: "Beat Saber",
		genre: {
			"экшен",
			"инди",
			"ритмушка",
			"с видом от первого лица"
		},
		theme: {
			"минимализм",
			"сложная"
		},
		players_count: {
			"для одного игрока",
			"кооператив"
		},
		device: {
			"VR"
		}
	);
	Title();
	$mode := Menu(390, 160, "Выберите режим", string["Найти подходящую игру", "Получить информацию об игре"], 3);
if($mode = 1) then
	$win := MakeWindow( "Доступные игры", 15, 25, 350, 420 );
	
	call group(ListOfGames, Stop);
	PrintGames();
	$choosenGenres := TupleSelect("Выберите интересующий вас жанр", $allGenres);
	if #$choosenGenres = 0 then
       BrushColor($win, 0, 0, 0); Rectangle($win,-1,-1, 350,420);
       TextColor($win, 0);
       OutText($win, 20,50, "");
       Message("", "Выход");
	else
       $explaination := $explaination + string["  Выбранные жанры : "];  
       $explaination := $explaination + $choosenGenres;
       call group(TakeGamesWithChoosenGenres, Stop);
       $explaination := $explaination + string["    Игры с подходящим жанром: "];
       $explaination := $explaination + $allGames;
       PrintGames();
	   if $gamesCount>1 then
	   	  call group(ListOfThemes, Stop);
		  $choosenThemes := TupleSelect("Выберите интересующую вас тему", $allThemes);
		  if #$choosenThemes != 0 then
             $explaination := $explaination + string["  Выбранные темы: "];  
             $explaination := $explaination + $choosenThemes;
             call group(TakeGamesWithChoosenThemes, Stop);
             $explaination := $explaination + string["    Игры с подходящей темой: "];
             $explaination := $explaination + $allGames;
             PrintGames();
	      end;
	   end;
	   if $gamesCount>1 then
	   	  call group(ListOfPlayersCount, Stop);
		  $choosenPlayersCount := TupleSelect("Выберите интересующую вас тему", $allPlayersCount);
		  if #$choosenPlayersCount != 0 then
             $explaination := $explaination + string["  Выбранное количество игроков: "];  
             $explaination := $explaination + $choosenPlayersCount;
             call group(TakeGamesWithChoosenPlayersCount, Stop);
             $explaination := $explaination + string["    Игры с подходящим количеством игроков: "];
             $explaination := $explaination + $allGames;
             PrintGames();
          end;
	   end;
	   if $gamesCount>1 then
	   	  call group(ListOfDevices, Stop);
		  $choosenDevices := TupleSelect("Выберите интересующую вас тему", $allDevices);
		  if #$choosenDevices != 0 then
             $explaination := $explaination + string["  Выбранная поддержка устройств: "];  
             $explaination := $explaination + $choosenDevices;
             call group(TakeGamesWithChoosenDevices, Stop);
             $explaination := $explaination + string["    Игры с подходящей поддержкой устройств: "];
             $explaination := $explaination + $allGames;
             PrintGames();
          end;
	   end;
	   if $gamesCount>0 then
  	      $tmp := MakeWindow( " .   Подходящие игры: ", 600, $y, 400, 615); $x:=$x+30; $y:=$y+30;
  	      BrushColor($tmp, 0, 0, 0); 
  	      TextColor($tmp, 0);
 	      call group(RightGames,Stop);
	   else
	      PrintNoGames();
	   end;

       if Ask("Подсистема объяснений", "Объяснить?") then
          var $s : string;
          $exp := MakeWindow( "Подсистема объяснений :", 320, 0, 420, 640 );
          for $io in 1..#$explaination loop
	         $s := $explaination[$io];
	         if $s[1] = ' ' then TextColor($exp, 4);
	         else TextColor($exp, 0);
	         end;
             OutText($exp, 10, $yo, $explaination[$io]);
             $yo := $yo + 20;
          end;
       end;
	end;
elsif $mode = 2 then
	call group(ListOfGames, Stop);
	$choosengame := Menu(390, 160, "Выберите игру", $allGames, $gamesCount + 1);
	if($choosengame <= $gamesCount) then
	   $choosengametitle := $allGames[$choosengame];
  	      $tmp := MakeWindow( " .   Описание игры: ", 600, $y, 400, 615); $x:=$x+30; $y:=$y+30;
  	      BrushColor($tmp, 0, 0, 0); 
  	      TextColor($tmp, 0);
	   call group(ChoosenGame, Stop);
	else
       Message("", "Выход");
	end;
else
       Message("", "Выход");
end;
end.

