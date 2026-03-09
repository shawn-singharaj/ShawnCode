-- Group 44: Golden Fellows
-- Shawn Singharaj and Andy Bui

-- CRUD Functionality for the NBA DBMS

-- Player Table:
-- Retrieve player info
 SELECT playerId, firstName, lastName, position, teamId
      FROM Players
      ORDER BY playerId;

-- Add player to DB
INSERT INTO Players (firstName, lastName, position, teamId)
VALUES (@firstName, @lastName, @position, @teamId);

-- Update Player
UPDATE Players
      SET firstName = @firstName, lastName = @lastName, position = @position, teamId = @teamId
      WHERE playerId = @playerId;

-- Delete player
DELETE FROM Players
      WHERE playerId = @playerId;

-- Teams Table:
-- Retrive info for teams
 SELECT teamId, teamName, conference, abbreviation
      FROM Teams
      ORDER BY teamId;

-- Insert team
INSERT INTO Teams (teamName, conference, abbreviation)
      VALUES (@teamName, @conference, @abbreviation);
      
-- Update a team
UPDATE Teams
	SET teamName = @teamName, conference = @conference, abbreviation = @abbreviation
    WHERE teamId = @teamId;
    
-- Delete a team
DELETE FROM Teams
	WHERE teamId = @teamId;

-- Games Table:
-- Get games
SELECT gameId, gameDate, seasonId, homeTeamId, awayTeamId, homeScore, awayScore
      FROM Games
      ORDER BY gameId;

-- Add game to DB
INSERT INTO Games (gameDate, homeTeamId, awayTeamId, homeScore, awayScore, seasonId)
VALUES (@gameDate, @homeTeamId, @awayTeamId, @homeScore, @awayScore, @seasonId);

-- Update a game
UPDATE Games
	SET gameDate = @gameDate, seasonId = @seasonId, homeTeamId = @homeTeamId, awayTeamId = @awayTeamId, homeScore = @homeScore, awayScore = @awayScore
    WHERE gameId = @gameId;
    
-- Delete a game
DELETE FROM Games
	WHERE gameId = @gameId;

-- Seasons Table:
-- Get seasons
 SELECT seasonId, seasonYear, startDate, endDate
      FROM Seasons
      ORDER BY seasonId;

-- Add season
INSERT INTO Seasons (seasonYear, startDate, endDate)
      VALUES (@seasonYear, @startDate, @endDate);
      
-- Update season
UPDATE Seasons
	SET seasonYear = @seasonYear, startDate = @startDate, endDate = @endDate
    WHERE seasonId = @seasonId;

-- Delete season
DELETE FROM Seasons
	WHERE seasonId = @seasonId;

-- Player_Game_Stats Table:
-- Get player stats
SELECT minutes, points, rebounds, assists, steals, blocks, turnovers, fgm, fga, threePm, threePa, ftm, fta, playerId, gameId
    FROM Player_Game_Stats
    ORDER BY playerId;

-- Team_Season_Stats Table:
-- Get team stats
 SELECT teamId, seasonId, wins, losses, pointsFor, pointsAgainst, assistsFor, reboundsFor, threePm, threePa
      FROM Team_Season_Stats
      ORDER BY teamId;

-- EXAMPLE USE CASES W/ JOINS, NOT YET IMPLEMENTED:

-- Retrieve Game Scores + Team Names + Date
SELECT 
    ht.abbreviation AS Home,
    g.homeScore, 
    at.abbreviation AS Away,
    g.awayScore, 
    g.gameDate
FROM Games g
    JOIN Teams ht ON ht.teamId = g.homeTeamId
    JOIN Teams at ON at.teamId = g.awayTeamId;

-- Retrieve Player Game stats
SELECT 
    CONCAT(p.firstName, ' ', p.lastName) AS name,
    g.minutes,
    g.points,
    g.rebounds,
    g.assists,
    g.steals,
    g.blocks,
    g.turnovers,
    g.fgm,
    g.fga,
    g.threePm,
    g.threePa,
    g.ftm,
    g.fta
FROM Player_Game_Stats g
    JOIN Players p ON p.playerId = g.playerId;

-- Retrieve Players and team
SELECT 
    p.firstName,
    p.lastName,
    t.teamName,
    p.position
FROM Players p
    JOIN Teams t ON t.teamId = p.teamId;

-- Retrieve Teams' Season Stats
SELECT 
    t.teamName,
    s.seasonYear,
    ts.gamesPlayed,
    ts.wins,
    ts.losses,
    ts.pointsFor,
    ts.pointsAgainst,
    ts.assistsFor,
    ts.reboundsFor,
    ts.threePm,
    ts.threePa
FROM Seasons s
    JOIN Team_Season_Stats ts ON ts.seasonId = s.seasonId 
    JOIN Teams t ON t.teamId = ts.teamId;

-- Update a player when he gets waived to free agency
UPDATE Players
SET teamId = NULL 
WHERE firstName = "input" AND lastName = "input";

-- Update player team when trade
UPDATE Players
SET teamId = @newTeamId
WHERE playerId = @playerId;

-- Update game score
UPDATE Games
SET homeScore = @homeScore,
    awayScore = @awayScore
WHERE gameId = @gameId;

-- Team gets renamed
UPDATE Teams
SET teamName = @teamName,
WHERE teamId = @teamId;

-- Delete Game + stats
DELETE FROM Player_Game_Stats
WHERE gameId = @gameId;
DELETE FROM Games 
WHERE gameId = @gameId;

-- Delete player stats 
DELETE FROM Player_Game_Stats
WHERE playerId = @playerId AND gameId = @gameId;


