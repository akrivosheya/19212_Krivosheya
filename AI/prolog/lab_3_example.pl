rule("пингвин",[2,5,6]).
rule("волк",[1,7]).
rule("зебра",[6,8]).
rule("касатка",[3,5]).
property(1,"имеет шерсть").
property(2,"имеет перь€").
property(3,"имеет плавники").
property(4,"летает").
property(5,"плавает").
property(6,"имеет черно-белый цвет").
property(7,"имеет клыки").
property(8,"имеет копыта").

:-dynamic db_yes/1, db_no/1.

remember(да,X):-
    asserta(db_yes(X)).
remember(нет,X):-
    asserta(db_no(X)),

fail.

check_if(X):-
    write("ќно "),
    write(X),
    writeln(" ?"),
    read(Reply),
    remember(Reply, X).

yes(X):-
    db_yes(X),
    !.
yes(X):-
    not(no(X)),
    !,
    check_if(X).
no(X):-
    db_no(X),
    !.

check_property([]).
check_property([N|Property]):-
    property(N, A),
    yes(A),
    check_property(Property).

animal(X):-
    rule(X,Property),
    check_property(Property).

game:-
    retractall(db_yes(_)),
    retractall(db_no(_)),
    animal(X),
    write("«адуманное вами животное - "),
    write(X).







