SELECT s.id, s.student_name, h.house_name, h.head_name
  FROM students AS s
       JOIN assingments AS a
       ON s.id = a.student_id
       JOIN houses AS h
       ON a.house_id = h.id;

