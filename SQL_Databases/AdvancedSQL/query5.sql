-- Find the film_title of all films which feature both UMA WOOD and FRED COSTNER
-- Order the results by film_title in descending order.
--  Warning: this is a tricky one and while the syntax is all things you know, you have to think a bit oustide the box 
--  to figure out how to get a table that shows pairs of actors in movies.

-- Put your query for Q5 here.
SELECT
    film.title AS film_title
FROM film
    JOIN film_actor AS fa1 ON fa1.film_id = film.film_id
    JOIN actor AS a1 ON a1.actor_id = fa1.actor_id AND a1.first_name = "UMA" AND a1.last_name = "WOOD"
    
    JOIN film_actor AS fa2 ON fa2.film_id = film.film_id
    JOIN actor AS a2 ON a2.actor_id = fa2.actor_id AND a2.first_name = "FRED" AND a2.last_name = "COSTNER"
GROUP BY film.title
ORDER BY film.title DESC;