book(tolstoy, "War and piece").
book(tolstoy, "Anna Karenina").
book(dostoevskiy, "Idiot").
book(dostoevskiy, "Karamazov brothers").
print_book:-book(X,Y),write(X),
    write(". "), writeln(Y),fail;
    true.
