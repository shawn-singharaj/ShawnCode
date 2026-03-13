DROP PROCEDURE IF EXISTS update_player;

DELIMITER //

CREATE PROCEDURE update_player (
  IN p_playerId INT,
  IN p_firstName VARCHAR(50),
  IN p_lastName VARCHAR(50),
  IN p_position VARCHAR(10),
  IN p_teamId INT
)
BEGIN
  UPDATE Players
  SET firstName = p_firstName,
      lastName = p_lastName,
      position = p_position,
      teamId = p_teamId
  WHERE playerId = p_playerId;
END //

DELIMITER ;