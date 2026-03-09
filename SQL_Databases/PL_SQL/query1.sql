-- Note: Only use single-line comments in this file.

-- Citation for the following code:
-- Date: 
-- Copied from /OR/ Adapted from /OR/ Based on 
-- (Explain degree of originality)
-- Source URL: 
-- If AI tools were used:
-- (Explain the use of tools and include a summary of the prompts submitted to the AI tool)


-- Leave the following query code untouched
DROP PROCEDURE IF EXISTS sp_query1;
DELIMITER //

-- ------- Write your code below this line -----------
CREATE PROCEDURE sp_query1 (IN timeNow VARCHAR(4), OUT greeting VARCHAR(50))
BEGIN
    DECLARE current_hour INT;
    DECLARE formatted_time TIME;
    
    -- Validate input format
    IF LENGTH(timeNow) != 4 OR timeNow NOT REGEXP '^[0-2][0-9][0-5][0-9]$' THEN
        SET greeting = 'Invalid time format. Please use HHMM.';
    ELSE

        -- Convert the input timeNow to TIME format
        SET current_hour = CAST(LEFT(timeNow, 2) AS UNSIGNED);

        -- Check for valid time range
        CASE
            WHEN current_hour BETWEEN 06 AND 11 THEN SET greeting = 'Good morning';
            WHEN current_hour BETWEEN 12 AND 16 THEN SET greeting = 'Good afternoon';
            WHEN current_hour BETWEEN 17 AND 23 THEN SET greeting = 'Good evening';
            WHEN current_hour BETWEEN 00 AND 05 THEN SET greeting = "My it's late, shouldn't you be in bed?";
            ELSE SET greeting = 'Invalid time format. Please use HHMM.';
        END CASE;

    END IF;
END //
-- ------- Do not alter query code below this line -----------
DELIMITER ;