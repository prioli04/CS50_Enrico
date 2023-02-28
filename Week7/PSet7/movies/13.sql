SELECT DISTINCT p.name
  FROM people AS p
       JOIN stars AS s
       ON p.id = s.person_id
       JOIN movies AS m
       ON m.id = s.movie_id
 WHERE p.name != "Kevin Bacon"
       AND m.id IN (SELECT m.id
                      FROM people AS p
                           JOIN stars AS s
                           ON p.id = s.person_id
                           JOIN movies AS m
                           ON m.id = s.movie_id
                     WHERE p.name = "Kevin Bacon"
                           AND p.birth = 1958);