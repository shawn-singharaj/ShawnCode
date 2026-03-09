-- Note: Only use single-line comments in this file.

-- Citation for the following code:
-- Date: 
-- Copied from /OR/ Adapted from /OR/ Based on 
-- (Explain degree of originality)
-- Source URL: 
-- If AI tools were used:
-- (Explain the use of tools and include a summary of the prompts submitted to the AI tool)


-- Leave the following query code untouched
DROP PROCEDURE IF EXISTS sp_add_person_certification;
DELIMITER //

-- ------- Write your code below this line -----------
CREATE PROCEDURE sp_add_person_certification (
    IN person_id INT,
    IN cert_id INT
)
BEGIN
    DECLARE cert_exists INT;
    DECLARE relationship_exists INT;

    DECLARE EXIT HANDLER FOR SQLEXCEPTION
    BEGIN
        -- Rollback the transaction in case of an error
        ROLLBACK;
        -- Return -99 to indicate an error
        SELECT -99 AS cert_count;
    END;

    -- Start a transaction
    START TRANSACTION;

    -- Check if the certification exists
    SELECT COUNT(*) INTO cert_exists FROM bsg_cert WHERE id = cert_id;
    IF cert_exists = 0 THEN
        ROLLBACK;
        SELECT -99 AS cert_count;
    ELSE
        -- If the certification exists, insert the new certification for the person
        SELECT COUNT(*) INTO relationship_exists 
        FROM bsg_cert_people WHERE pid = person_id AND cid = cert_id;
        IF relationship_exists > 0 THEN
            SELECT -99 AS cert_count;
            COMMIT;
        ELSE
            INSERT INTO bsg_cert_people (cid, pid)
            VALUES (cert_id, person_id);

            -- Commit the transaction
            COMMIT;

            -- Return the count of people with the new certification
            SELECT func_cert_count((SELECT title FROM bsg_cert WHERE id = cert_id)) AS cert_count;
        END IF;
    END IF;
END //


-- ------- Do not alter query code below this line -----------
DELIMITER ;