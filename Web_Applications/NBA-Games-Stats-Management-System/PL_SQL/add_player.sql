DROP PROCEDURE IF EXISTS add_player;

DELIMITER //
CREATE PROCEDURE add_player(
    IN p_firstName VARCHAR(50),
    IN p_lastName VARCHAR(50),
    IN p_position VARCHAR(50),
    IN p_teamId INT
)

BEGIN
INSERT INTO Players (firstName, lastName, position, teamId)
VALUES (p_firstName, p_lastName, p_position, p_teamId);
END //

DELIMITER ;