SELECT DISTINCT p.name
  FROM people AS p
       JOIN stars AS s
       ON p.id = s.person_id
       JOIN movies AS m
       ON m.id = s.movie_id
 WHERE year = 2004
 ORDER BY p.birth;