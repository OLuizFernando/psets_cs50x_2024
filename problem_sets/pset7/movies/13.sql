SELECT DISTINCT people.name
FROM stars, people
WHERE stars.person_id = people.id
AND movie_id IN (
    SELECT movies.id
    FROM movies, people, stars
    WHERE movies.id = stars.movie_id
    AND people.id = stars.person_id
    AND name = 'Kevin Bacon'
)
AND people.name != 'Kevin Bacon';
