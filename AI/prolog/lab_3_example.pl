rule("�������",[2,5,6]).
rule("����",[1,7]).
rule("�����",[6,8]).
rule("�������",[3,5]).
property(1,"����� ������").
property(2,"����� �����").
property(3,"����� ��������").
property(4,"������").
property(5,"�������").
property(6,"����� �����-����� ����").
property(7,"����� �����").
property(8,"����� ������").

:-dynamic db_yes/1, db_no/1.

remember(��,X):-
    asserta(db_yes(X)).
remember(���,X):-
    asserta(db_no(X)),

fail.

check_if(X):-
    write("��� "),
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
    write("���������� ���� �������� - "),
    write(X).







