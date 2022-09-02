country("Нидерланды", "Амстердам").
country("Германия", "Берлин").
country("Швейцария", "Берн").
country("Австрия", "Вена").
country("Польша", "Варшава").
country("Великобритания", "Лондон").
country("Испания", "Мадрид").
country("Россия", "Москва").
country("Россия", "Новосибирск").
country("Россия", "Норильск").
country("Норвегия", "Осло").
country("Франция", "Париж").
writeCities(X):-
    country(X,Y),
    writeln(Y),
    fail.
writeRightMessageCities("*"):-
    writeln("Заканчиваю опрос").
writeRightMessageCities(X):-
    country(X,_),
    !,
    writeCities(X).
writeRightMessageCities(_):-
    writeln("Нет такой страны"),
    fail.
startDialogCountry:-
    repeat,
    writeln("Введите страну"),
    read(X),
    writeRightMessageCities(X),
    !.
writeCountries(X):-
    country(Y,X),
    writeln(Y),
    fail.
writeRightMessageCountries("*"):-
    writeln("Заканчиваю опрос").
writeRightMessageCountries(X):-
    country(_,X),
    !,
    writeCountries(X).
writeRightMessageCountries(_):-
    writeln("Нет такого города"),
    fail.
startDialogCity:-
    repeat,
    writeln("Введите город"),
    read(X),
    writeRightMessageCountries(X),
    !.


