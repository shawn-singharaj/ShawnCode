DROP PROCEDURE IF EXISTS delete_player;

DELIMITER //

CREATE PROCEDURE delete_player (
  IN p_playerId INT
)
BEGIN
  DELETE FROM Players
  WHERE playerId = p_playerId;
END //

DELIMITER ;