del(Head, [Head|L], L).
del(H, [H1|L], [H1|L1]):-
    del(H,L,L1).
