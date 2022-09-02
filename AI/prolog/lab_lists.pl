genListRecurs(0,[]).
genListRecurs(N,[X|L]):-
    Nnext is N-1,
    random_between(0,1000,X),
    genListRecurs(Nnext,L).
genList(N,L):-
    genListRecurs(N,L),
    !.

findLastRecurs(H,[],H).
findLastRecurs(_,[H1|L],X):-
    findLastRecurs(H1,L,X).
findLast([H|L],X):-
    findLastRecurs(H,L,X),
    !.

reverseListRecurs([],H,L,[H|L]).
reverseListRecurs([H1|L],H2,LAcc,LR):-
    reverseListRecurs(L,H1,[H2|LAcc],LR).
reverseList([H|L],LR):-
    reverseListRecurs(L,H,[],LR).

lessMore(E,H,LLess,LMore,[H|LLess],LMore):-
    E>H,
    !.
lessMore(_,H,LLess,LMore,LLess,[H|LMore]).
createLessMoreListsRecurs(_,[],LLess,LMore,LLess,LMore).
createLessMoreListsRecurs(E,[H|L],LLessAcc,LMoreAcc,LLess,LMore):-
    lessMore(E,H,LLessAcc,LMoreAcc,NewLLessAcc,NewLMoreAcc),
    createLessMoreListsRecurs(E,L,NewLLessAcc,NewLMoreAcc,LLess,LMore).
createLessMoreLists(E,L,LMin,LMax):-
    createLessMoreListsRecurs(E,L,[],[],LMin,LMax).
sortListRecurs([],[]).
sortListRecurs([H|L],LSorted):-
    createLessMoreLists(H,L,LLess,LMore),
    sortListRecurs(LLess,LLessSorted),
    sortListRecurs(LMore,LMoreSorted),
    append(LLessSorted,[H|LMoreSorted],LSorted).
sortList(L,LSorted):-
    sortListRecurs(L,LSorted),
    !.

g:-genList(100,L),
    sortList(L,SL),
    writeln(SL),
    !.
