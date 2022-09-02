factorial(N,N,FactN,FactN):-!.
factorial(I,N,P,FactN):-
    NewI is I+1,
    NewP is P*NewI,
    factorial(NewI,N,NewP,FactN).
fact(N,FactN):-
    factorial(0,N,1,FactN).
