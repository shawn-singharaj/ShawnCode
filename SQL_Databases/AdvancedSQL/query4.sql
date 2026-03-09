-- Find the actor_id, first_name, and last_name of all actors who have never been in a Sports film.
-- Order your results by actor_id in descending order.

-- Put query for Q4 here
SELECT
    actor.actor_id,
    actor.first_name,
    actor.last_name
FROM actor
WHERE actor.actor_id NOT IN (
    SELECT DISTINCT film_actor.actor_id
    FROM film_actor
    JOIN film_category ON film_category.film_id = film_actor.film_id
    JOIN category ON category.category_id = film_category.category_id
    WHERE category.name = 'Sports'
)
ORDER BY actor.actor_id DESC;