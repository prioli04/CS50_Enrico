SELECT p.name
  FROM people AS p
       JOIN stars AS s
       ON s.person_id = p.id
       JOIN movies AS m
       ON s.movie_id = m.id
 WHERE m.title = "Toy Story";