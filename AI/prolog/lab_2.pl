country("����������", "���������").
country("��������", "������").
country("���������", "����").
country("�������", "����").
country("������", "�������").
country("��������������", "������").
country("�������", "������").
country("������", "������").
country("������", "�����������").
country("������", "��������").
country("��������", "����").
country("�������", "�����").
writeCities(X):-
    country(X,Y),
    writeln(Y),
    fail.
writeRightMessageCities("*"):-
    writeln("���������� �����").
writeRightMessageCities(X):-
    country(X,_),
    !,
    writeCities(X).
writeRightMessageCities(_):-
    writeln("��� ����� ������"),
    fail.
startDialogCountry:-
    repeat,
    writeln("������� ������"),
    read(X),
    writeRightMessageCities(X),
    !.
writeCountries(X):-
    country(Y,X),
    writeln(Y),
    fail.
writeRightMessageCountries("*"):-
    writeln("���������� �����").
writeRightMessageCountries(X):-
    country(_,X),
    !,
    writeCountries(X).
writeRightMessageCountries(_):-
    writeln("��� ������ ������"),
    fail.
startDialogCity:-
    repeat,
    writeln("������� �����"),
    read(X),
    writeRightMessageCountries(X),
    !.


