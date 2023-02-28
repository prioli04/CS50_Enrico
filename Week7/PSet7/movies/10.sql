SELECT DISTINCT p.name
  FROM people AS p
       JOIN directors AS d
       ON p.id = d.person_id
       JOIN movies AS m
       ON m.id = d.movie_id
       JOIN ratings AS r
       ON r.movie_id = m.id
 WHERE r.rating >= 9.0;