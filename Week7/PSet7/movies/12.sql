SELECT J.title
  FROM (SELECT m.title
          FROM movies AS m
               JOIN stars AS s
               ON m.id = s.movie_id
               JOIN people AS p
               ON p.id = s.person_id
         WHERE p.name = "Johnny Depp") AS J
         JOIN ( SELECT m.title
                  FROM movies AS m
                       JOIN stars AS s
                       ON m.id = s.movie_id
                       JOIN people AS p
                       ON p.id = s.person_id
                 WHERE p.name = "Helena Bonham Carter") AS H
         ON J.title = H.title;