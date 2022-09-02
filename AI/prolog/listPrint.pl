printList([]):-
    writeln("end").
printList([H|T]):-
    writeln(H),
    printList(T).
