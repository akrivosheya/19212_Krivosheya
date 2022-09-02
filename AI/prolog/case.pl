case(1):-!,write(jump).
case(2):-!,write(throw).
case(3):-!,write(sleep).
case(_):-write(die).
do:-read(X),
    case(X).
