country("Америка", "Вашингтон").
country("Америка","Нью-Йорк").
country("Россия", "Москва").
country("Россия", "Новосибирск").
country("Россия", "Норильск").
print(X):-
    findall(X, country(X,_), List),
    list_to_set(List,Set),
    write(Set).
