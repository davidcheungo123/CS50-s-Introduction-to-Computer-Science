SELECT name FROM PEOPLE WHERE id IN (SELECT person_id FROM stars WHERE movie_id IN (SELECT id FROM movies WHERE title= "Toy Story"));