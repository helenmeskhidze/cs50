SELECT AVG(rating) FROM(SELECT rating, year FROM ratings JOIN movies on movies.id = ratings.movie_id) WHERE year = "2012"; 
