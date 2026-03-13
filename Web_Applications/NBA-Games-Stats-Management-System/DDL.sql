-- Golden Fellows - Shawn Singharaj and Andy Bui
-- DDL for NBA DBMS

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
SET FOREIGN_KEY_CHECKS = 0;
SET AUTOCOMMIT = 0;
START TRANSACTION;
SET time_zone = "+00:00";

-- Drop tables if they exist for easy importing
DROP TABLE IF EXISTS Player_Game_Stats;
DROP TABLE IF EXISTS Team_Season_Stats;
DROP TABLE IF EXISTS Games;
DROP TABLE IF EXISTS Players;
DROP TABLE IF EXISTS Teams;
DROP TABLE IF EXISTS Seasons;

-- ---------------------------------------------------------
-- Table structure for table `Games` that displays the score with the home and away team w/ date
CREATE TABLE `Games` (
  `gameId` int(11) NOT NULL,
  `gameDate` date NOT NULL,
  `homeTeamId` int(11) NOT NULL,
  `awayTeamId` int(11) NOT NULL,
  `homeScore` int(11) NOT NULL,
  `awayScore` int(11) NOT NULL,
  `seasonId` int(11) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;
-- ---------------------------------------------------------

-- ---------------------------------------------------------
-- Table structure for table `Players` which holds a single player's name and team
CREATE TABLE `Players` (
  `playerId` int(11) NOT NULL,
  `teamId` int(11) NULL,
  `firstName` varchar(45) NOT NULL,
  `lastName` varchar(45) NOT NULL,
  `position` varchar(2) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;
-- ---------------------------------------------------------

-- ---------------------------------------------------------
-- Table structure for table `Player_Game_Stats`, intersection table between a player and game
-- Composite key with playerId and gameId
CREATE TABLE `Player_Game_Stats` (
  `minutes` int(11) NOT NULL,
  `points` int(11) NOT NULL,
  `rebounds` int(11) NOT NULL,
  `assists` int(11) NOT NULL,
  `steals` int(11) NOT NULL,
  `blocks` int(11) NOT NULL,
  `turnovers` int(11) NOT NULL,
  `fgm` int(11) NOT NULL,
  `fga` int(11) NOT NULL,
  `threePm` int(11) NOT NULL,
  `threePa` int(11) NOT NULL,
  `ftm` int(11) NOT NULL,
  `fta` int(11) NOT NULL,
  `playerId` int(11) NOT NULL,
  `gameId` int(11) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;
-- ---------------------------------------------------------

-- ---------------------------------------------------------
-- Table structure for table `Seasons`, holds a season's dates
CREATE TABLE `Seasons` (
  `seasonId` int(11) NOT NULL,
  `seasonYear` int(11) NOT NULL,
  `startDate` date NOT NULL,
  `endDate` date NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;
-- --------------------------------------------------------

-- ---------------------------------------------------------
-- Table structure for table `Teams`, holds the team's name, conference, and abbr
CREATE TABLE `Teams` (
  `teamId` int(11) NOT NULL,
  `teamName` varchar(145) NOT NULL,
  `conference` varchar(9) NOT NULL DEFAULT '1',
  `abbreviation` varchar(4) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;
-- ---------------------------------------------------------

-- ---------------------------------------------------------
-- Table structure for table `Team_Season_Stats`, intersection table between a team and their stats on the season
-- Composite key with teamId and seasonId
CREATE TABLE `Team_Season_Stats` (
  `gamesPlayed` int(11) NOT NULL,
  `wins` int(11) NOT NULL,
  `losses` int(11) NOT NULL,
  `pointsFor` DECIMAL(5,1) NOT NULL,
  `pointsAgainst` DECIMAL(5,1) NOT NULL,
  `assistsFor` DECIMAL(5,1) NOT NULL,
  `reboundsFor` DECIMAL(5,1) NOT NULL,
  `threePm` DECIMAL(5,1) NOT NULL,
  `threePa` DECIMAL(5,1) NOT NULL,
  `teamId` int(11) NOT NULL,
  `seasonId` int(11) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;
-- ---------------------------------------------------------

-- ---------------------------------------------------------
-- Primary key and foreign key constraints for each table:

-- 1 PK and 3 FK for Games
ALTER TABLE `Games`
  ADD PRIMARY KEY (`gameId`),
  ADD UNIQUE KEY `gameId_UNIQUE` (`gameId`),
  ADD KEY `fk_game_season` (`seasonId`),
  ADD KEY `fk_game_home` (`homeTeamId`),
  ADD KEY `fk_game_away` (`awayTeamId`);

-- 1 PK and 1 FK for Players
ALTER TABLE `Players`
  ADD PRIMARY KEY (`playerId`),
  ADD UNIQUE KEY `playerId_UNIQUE` (`playerId`),
  ADD KEY `fk_player_team` (`teamId`);

-- Composite key for the two FK for Player_Game_Stats
ALTER TABLE `Player_Game_Stats`
  ADD PRIMARY KEY (`playerId`,`gameId`),
  ADD KEY `fk_player_stats_player` (`playerId`),
  ADD KEY `fk_player_stats_game` (`gameId`);

-- 1 PK for Seasons
ALTER TABLE `Seasons`
  ADD PRIMARY KEY (`seasonId`),
  ADD UNIQUE KEY `seasonId_UNIQUE` (`seasonId`);

-- 1 PK for Teams
ALTER TABLE `Teams`
  ADD PRIMARY KEY (`teamId`),
  ADD UNIQUE KEY `teamName_UNIQUE` (`teamName`),
  ADD UNIQUE KEY `teamId_UNIQUE` (`teamId`);

-- Composite key for the two FK for Team_Season_Stats
ALTER TABLE `Team_Season_Stats`
  ADD PRIMARY KEY (`teamId`,`seasonId`),
  ADD KEY `fk_team_id` (`teamId`),
  ADD KEY `fk_team_season` (`seasonId`);

-- ---------------------------------------------------------

-- Set AI for the PKs
ALTER TABLE `Games`
  MODIFY `gameId` int(11) NOT NULL AUTO_INCREMENT;

ALTER TABLE `Players`
  MODIFY `playerId` int(11) NOT NULL AUTO_INCREMENT;

ALTER TABLE `Seasons`
  MODIFY `seasonId` int(11) NOT NULL AUTO_INCREMENT;

ALTER TABLE `Teams`
  MODIFY `teamId` int(11) NOT NULL AUTO_INCREMENT;

-- ---------------------------------------------------------

-- FK Constraints here + Cascade
-- Constraints for Games
ALTER TABLE `Games`
  ADD CONSTRAINT `fk_game_away` FOREIGN KEY (`awayTeamId`) REFERENCES `Teams` (`teamId`)
  ON DELETE CASCADE
  ON UPDATE CASCADE,
  ADD CONSTRAINT `fk_game_home` FOREIGN KEY (`homeTeamId`) REFERENCES `Teams` (`teamId`)
  ON DELETE CASCADE
  ON UPDATE CASCADE,
  ADD CONSTRAINT `fk_game_season` FOREIGN KEY (`seasonId`) REFERENCES `Seasons` (`seasonId`)
  ON DELETE CASCADE
  ON UPDATE CASCADE;


-- Constraints Players
ALTER TABLE `Players`
  ADD CONSTRAINT `fk_player_team` FOREIGN KEY (`teamId`) REFERENCES `Teams` (`teamId`)
  ON DELETE CASCADE
  ON UPDATE CASCADE;


-- Constraints for Player_Game_Stats
ALTER TABLE `Player_Game_Stats`
  ADD CONSTRAINT `fk_player_stats_game` FOREIGN KEY (`gameId`) REFERENCES `Games` (`gameId`)
  ON DELETE CASCADE
  ON UPDATE CASCADE,
  ADD CONSTRAINT `fk_player_stats_player` FOREIGN KEY (`playerId`) REFERENCES `Players` (`playerId`)
  ON DELETE CASCADE
  ON UPDATE CASCADE;


-- Constraints for Team_Season_Stats
ALTER TABLE `Team_Season_Stats`
  ADD CONSTRAINT `fk_team_id` FOREIGN KEY (`teamId`) REFERENCES `Teams` (`teamId`)
  ON DELETE CASCADE
  ON UPDATE CASCADE,
  ADD CONSTRAINT `fk_team_season` FOREIGN KEY (`seasonId`) REFERENCES `Seasons` (`seasonId`)
  ON DELETE CASCADE
  ON UPDATE CASCADE;


-- ---------------------------------------------------------

-- Insert queries here

-- Insert 4 teams
INSERT INTO Teams (teamName, conference, abbreviation)
VALUES ("Los Angeles Lakers", "West", "LAL"), 
("Golden State Warriors", "West", "GSW"),
("Portland Trail Blazers", "West", "POR"),
("Boston Celtics", "East", "BOS");

-- Insert 4 players who are each on the 4 teams above
INSERT INTO Players (teamId, firstName, lastName, position)
VALUES ((SELECT teamId FROM Teams WHERE abbreviation = "LAL"), "LeBron", "James", "SF"),
((SELECT teamId FROM Teams WHERE abbreviation = "GSW"), "Stephen", "Curry", "PG"),
((SELECT teamId FROM Teams WHERE abbreviation = "POR"), "Jrue", "Holiday", "G"),
((SELECT teamId FROM Teams WHERE abbreviation = "BOS"), "Derrick", "White", "SG");

-- Insert 2 seasons
INSERT INTO Seasons (seasonYear, startDate, endDate)
VALUES (2023, "2023-10-01", "2024-06-01"),
(2024, "2024-6-01", "2025-06-01");

-- Insert 4 games with the 4 teams 
INSERT INTO Games (gameDate, seasonId, homeTeamId, awayTeamId, homeScore, awayScore)
VALUES ("2023-05-02", (SELECT seasonId  FROM Seasons WHERE seasonYear = 2023), (SELECT teamId FROM Teams WHERE abbreviation = "LAL"), (SELECT teamId FROM Teams where abbreviation = "GSW"), 117, 112),
("2023-12-28", (SELECT seasonId FROM Seasons WHERE seasonYear = 2023), (SELECT teamId FROM Teams WHERE abbreviation = "POR"), (SELECT teamId FROM Teams WHERE abbreviation = "BOS"), 114, 108),
("2023-12-30", (SELECT seasonId FROM Seasons WHERE seasonYear = 2023), (SELECT teamId FROM Teams WHERE abbreviation = "GSW"), (SELECT teamId FROM Teams WHERE abbreviation = "POR"), 118, 112),
("2025-09-02", (SELECT seasonId FROM Seasons WHERE seasonYear = 2024), (SELECT teamId FROM Teams WHERE abbreviation = "LAL"), (SELECT teamId FROM Teams WHERE abbreviation = "GSW"), 108, 122);

-- Insert box scores for the 4 players
INSERT INTO Player_Game_Stats (playerId, gameId, minutes, points, rebounds, assists, steals, blocks, turnovers,
 fgm, fga, threePm, threePa, ftm, fta)
VALUES ((SELECT playerId FROM Players WHERE firstName = "LeBron" and lastName = "James"), (SELECT gameId FROM Games WHERE gameDate = "2023-05-02"), 40, 28, 8, 6, 2, 1, 4, 10, 20, 7, 5, 5, 6),
((SELECT playerId FROM Players WHERE firstName = "Stephen" and lastName = "Curry"), (SELECT gameId FROM Games WHERE gameDate = "2023-12-28"), 42, 33, 5, 7, 2, 0, 3, 12, 19, 10, 7, 7, 8),
((SELECT playerId FROM Players WHERE firstName = "Jrue" and lastName = "Holiday"), (SELECT gameId FROM Games WHERE gameDate = "2023-12-30"), 38, 26, 5, 3, 1, 0, 4, 9, 18, 7, 3, 3, 4),
((SELECT playerId FROM Players WHERE firstName = "Derrick" and lastName = "White"), (SELECT gameId FROM Games WHERE gameDate = "2025-09-02"), 35, 22, 10, 3, 1, 2, 3, 8, 17, 5, 4, 4, 5);


-- Insert each team's stats on the 2023 season
INSERT INTO Team_Season_Stats
(teamId, seasonId, gamesPlayed, wins, losses, pointsFor, pointsAgainst,
 assistsFor, reboundsFor, threePm, threePa)
VALUES
((SELECT teamId FROM Teams WHERE abbreviation = "LAL"), (SELECT seasonId FROM Seasons WHERE seasonYear = 2023), 82, 43, 39, 116.6, 115.3, 25.9, 45.7, 11.0, 32.0),
((SELECT teamId FROM Teams WHERE abbreviation = "GSW"), (SELECT seasonId FROM Seasons WHERE seasonYear = 2023), 82, 44, 38, 118.9, 116.0, 27.2, 45.0, 13.3, 35.0),
((SELECT teamId FROM Teams WHERE abbreviation = "POR"), (SELECT seasonId FROM Seasons WHERE seasonYear = 2023), 82, 33, 49, 113.0, 114.3, 24.5, 42.3, 12.1, 33.2),
((SELECT teamId FROM Teams WHERE abbreviation = "BOS"), (SELECT seasonId FROM Seasons WHERE seasonYear = 2023), 82, 57, 25, 118.5, 112.2, 27.0, 45.5, 15.5, 38.0);


SET FOREIGN_KEY_CHECKS = 1;
COMMIT;
