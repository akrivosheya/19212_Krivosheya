
cycle:-repeat,
    read(Name),
    write(Name),
    Name == 4,
    write(ok),
    !;
    true.
