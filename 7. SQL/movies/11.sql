SELECT title from movies JOIN ratings ON movies.id = ratings.movie_id WHERE movies.title IN
(SELECT title from movies WHERE movies.id IN
(SELECT movies.id FROM movies JOIN stars ON
movies.id=stars.movie_id WHERE stars.person_id =
(SELECT people.id from people WHERE name='Chadwick Boseman'))) ORDER BY rating DESC LIMIT 5;
