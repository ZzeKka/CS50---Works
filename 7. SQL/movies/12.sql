SELECT title from movies WHERE movies.id IN
(SELECT movie_id FROM stars where person_id IN (SELECT id FROM people WHERE name = 'Jennifer Lawrence'))
and movies.id IN (SELECT movie_id FROM stars where person_id IN (SELECT id FROM people WHERE name = 'Bradley Cooper'));



