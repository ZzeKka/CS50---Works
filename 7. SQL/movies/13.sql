SELECT name FROM people JOIN stars ON stars.person_id=people.id WHERE movie_id IN
(SELECT movies.id from movies JOIN stars ON movies.id=stars.movie_id JOIN people ON stars.person_id=people.id WHERE people.name='Kevin Bacon')
and name!='Kevin Bacon';

