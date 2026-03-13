-- Group 44: Golden Fellows
-- Shawn Singharaj and Andy Bui

-- CRUD Functionality for the NBA DBMS
-- CRUD works for Players and Player_Game_Stats tables
-- SELECTS work for all 6 tables

-- Player Table:
-- Retrieve player info and team name
SELECT
    Players.playerId,
    Players.firstName,
    Players.lastName,
    Players.position,
    Players.teamId,
    Teams.teamName
FROM Players
    LEFT JOIN Teams ON Players.teamId = Teams.teamId
 ORDER BY Players.playerId;

-- Add player
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

-- Games Table:
-- Get games, game date and matchup
SELECT
    g.gameId,
    DATE_FORMAT(g.gameDate, '%Y-%m-%d') AS gameDate,
    CONCAT(awayTeam.abbreviation, ' vs ', homeTeam.abbreviation) AS matchup,
    s.seasonYear,
    homeTeam.teamName AS homeTeam,
    awayTeam.teamName AS awayTeam,
    g.homeScore,
    g.awayScore
FROM Games g
    JOIN Seasons s ON g.seasonId = s.seasonId
    JOIN Teams homeTeam ON g.homeTeamId = homeTeam.teamId
    JOIN Teams awayTeam ON g.awayTeamId = awayTeam.teamId
    ORDER BY g.gameId;

-- Seasons Table:
-- Get seasons
 SELECT seasonId, seasonYear, startDate, endDate
      FROM Seasons
      ORDER BY seasonId;

-- Player_Game_Stats Table:
-- Get player stats, player name and game date + matchup
SELECT 
      DATE_FORMAT(g.gameDate, '%Y-%m-%d') AS gameDate,
      CONCAT(awayTeam.abbreviation, ' vs ', homeTeam.abbreviation) AS matchup,
      pgs.minutes,
      pgs.points,
      pgs.rebounds,
      pgs.assists,
      pgs.steals,
      pgs.blocks,
      pgs.turnovers,
      pgs.fgm,
      pgs.fga,
      pgs.threePm,
      pgs.threePa,
      pgs.ftm,
      pgs.fta,
      p.firstName,
      p.lastName,
      pgs.gameId,
      pgs.playerId
FROM Player_Game_Stats pgs
    JOIN Players p 
      ON pgs.playerId = p.playerId
    JOIN Games g 
      ON pgs.gameId = g.gameId
    JOIN Teams homeTeam 
      ON g.homeTeamId = homeTeam.teamId
    JOIN Teams awayTeam 
      ON g.awayTeamId = awayTeam.teamId
    ORDER BY p.lastName;

-- Add player stat
INSERT INTO Player_Game_Stats
    (playerId, gameId, minutes, points, rebounds, assists,
       steals, blocks, turnovers, fgm, fga, threePm, threePa, ftm, fta)
    VALUES (@playerId, @gameId, @minutes, @points, @rebounds, @assists, @steals, @blocks, @turnovers, @fgm, @fga, @threePm, @threepa, @ftm, @fta);

-- Update player stat
UPDATE Player_Game_Stats
    SET minutes = @minutes, points = @points, rebounds = @rebounds, assists = @assists,
        steals = @steals, blocks = @blocks, turnovers = @turnovers,
        fgm = @fgm, fga = @fga, threePm = @threePm, threePa = @threePa, ftm = @ftm, fta = @fta
    WHERE playerId = @playerId AND gameId = @gameId;

-- Delete player stat
DELETE FROM Player_Game_Stats
      WHERE playerId = @gameId AND gameId = @gameId;

-- Team_Season_Stats Table:
-- Get team stats and season year
SELECT 
        t.teamName,
        s.seasonYear,
        tss.wins,
        tss.losses,
        tss.pointsFor,
        tss.pointsAgainst,
        tss.assistsFor,
        tss.reboundsFor,
        tss.threePm,
        tss.threePa
      FROM Team_Season_Stats tss
      JOIN Teams t 
        ON tss.teamId = t.teamId
      JOIN Seasons s 
        ON tss.seasonId = s.seasonId
      ORDER BY t.teamName, s.seasonYear;
 