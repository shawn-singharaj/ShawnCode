// ########################################
// ########## SETUP

// Database
const db = require('./database/db-connector');

// Express
const express = require('express');
const app = express();

// Middleware
const cors = require('cors');
app.use(cors({ credentials: true, origin: "*" }));
app.use(express.json()); // this is needed for post requests


const PORT = 6709;

// SELECTS work for all 6 tables
// CUD works for Players and Player_Game_Stats tables

// ####################################################################################FOR PLAYERS TABLE##############
// Players Table CUD utilizes Stored Procedures to Add, Update, Delete from table.
// -----------------------------
// READ: Get all players TO DISPLAY TABLE IN FRONTEND
// Uses JOIN to obtain the team's name based off the teamId
// -----------------------------
app.get('/players', async (req, res) => {
  try {
    const query = `
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
    `;
    const [rows] = await db.query(query);
    res.status(200).json(rows);
  } catch (error) {
    console.error("GET /players error:", error);
    res.status(500).send("Error fetching players.");
  }
});


// -----------------------------
// CREATE: Add a player
// -----------------------------
app.post('/players', async (req, res) => {
  try {
    const { firstName, lastName, position, teamId } = req.body;

    // basic validation
    if (!firstName || !lastName || !position) {
      return res.status(400).send("firstName, lastName, and position are required.");
    }

    // Allow NULL for teamId
    const safeTeamId =
      teamId === "" || teamId === undefined ? null : teamId;

    // call SP
    const query = `
      CALL add_player(?, ?, ?, ?);
    `;

    const [result] = await db.query(query, [
      firstName,
      lastName,
      position,
      safeTeamId
    ]);

    // Return the new id (handy for debugging)
    res.status(201).json({ insertedId: result.insertId });
  } catch (error) {
    console.error("POST /players error:", error);
    res.status(500).send("Error creating player.");
  }
});

// -----------------------------
// UPDATE: Update a player
// -----------------------------
app.put('/players/:id', async (req, res) => {
  try {
    const playerId = Number(req.params.id);
    const { firstName, lastName, position, teamId } = req.body;

    //some basic validation stuff
    if(!Number.isInteger(playerId)) {
      return res.status(400).send("Invalid player ID."); // player id needs to be an integer
    }
    if (!firstName || !lastName || !position) {
      return res.status(400).send("firstName, lastName, and position are required."); // if left blank, send error
    }

    const safeTeamId = (teamId === "" || teamId === undefined) ? null : teamId;   

    // Call SP
    const query = `     
      CALL update_player(?, ?, ?, ?, ?);
      `;

    const [result] = await db.query(query, [
      playerId,
      firstName,
      lastName,
      position,
      safeTeamId     
    ]);

    console.log('result:', JSON.stringify(result));

    if (result.affectedRows === 0) {
      return res.status(404).send("Player not found."); // if no player with that id, send error
    }
    
    res.status(200).json({ message: "Player updated successfully." });
  } catch (error) {
    console.error("PUT /players/:id error:", error);
    res.status(500).send("Error updating player.");
  }

});

// -----------------------------
// DELETE: Delete a player
// -----------------------------
app.delete('/players/:id', async (req, res) => {
  try {
    const playerId = Number(req.params.id);

    if(!Number.isInteger(playerId)) {
      return res.status(400).send("Invalid player ID."); // player id needs to be an integer
    }

    // Call SP
    const query = `
      CALL delete_player(?);
    `;

    const [result] = await db.query(query, [playerId]);

    if (result.affectedRows === 0) {
      return res.status(404).send("Player not found."); // if no player with that id, send error
    }

    res.status(200).json({ message: "Player deleted successfully." });
  } catch (error) {
    console.error("DELETE /players/:id error:", error);
    res.status(500).send("Error deleting player.");
  }

});


// ##################################################################################################


// ####################################################################################FOR TEAMS TABLE##############

// -----------------------------
// SELECT: See teams
// -----------------------------
app.get('/Teams', async (req, res) => {
  try {
    const query = `
      SELECT teamId, teamName, conference, abbreviation
      FROM Teams
      ORDER BY teamId;
    `;
    const [rows] = await db.query(query);
    res.status(200).json(rows);
  } catch (error) {
    console.error("GET /teams error:", error);
    res.status(500).send("Error fetching teams.");
  }
});

// ##################################################################################################


// ####################################################################################FOR GAMES TABLE##############

// -----------------------------
// SELECT: See games
// Utilizes JOINS to get season year and team names 
// -----------------------------
app.get('/Games', async (req, res) => {
  try {
    // Configured query to get the game date formatted without time, and team abbreviations as matchup
    const query = `
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
    `;
    const [rows] = await db.query(query);
    res.status(200).json(rows);
  } catch (error) {
    console.error("GET /Games error:", error);
    res.status(500).send("Error fetching games.");
  }
});

// ##################################################################################################


// ####################################################################################FOR SEASONS TABLE##############

// -----------------------------
// SELECT: See seasons
// -----------------------------
app.get('/Seasons', async (req, res) => {
  try {
    const query = `
      SELECT seasonId, seasonYear, startDate, endDate
      FROM Seasons
      ORDER BY seasonId;
    `;
    const [rows] = await db.query(query);
    res.status(200).json(rows);
  } catch (error) {
    console.error("GET /Seasons error:", error);
    res.status(500).send("Error fetching seasons.");
  }
});

// ##################################################################################################


// ####################################################################################FOR PLAYER_GAME_STATS TABLE##############
// M:M intersection table with CRUD implementation
// -----------------------------
// SELECT: See player game stats
// Utilizes JOINS to obtain player's name, and matchup
// -----------------------------
app.get('/Player_Game_Stats', async (req, res) => {
  try {
  // Configured query to get the game date formatted without time, and team abbreviations as matchup 
  const query = `
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
  `;
    const [rows] = await db.query(query);
    res.status(200).json(rows);
  } catch (error) {
    console.error("GET /Player_Game_Stats error:", error);
    res.status(500).send("Error fetching player game stats.");
  }
});

// -----------------------------
// CREATE: Add a player's game stats
// -----------------------------
app.post('/Player_Game_Stats', async (req, res) => {
  try {
    const {
      playerId, gameId, minutes, points, rebounds, assists,
      steals, blocks, turnovers, fgm, fga, threePm, threePa, ftm, fta
    } = req.body;

    // Need both FKs in request
    if (!playerId || !gameId) {
      return res.status(400).send("playerId and gameId are required.");
    }

    const query = `
      INSERT INTO Player_Game_Stats
      (playerId, gameId, minutes, points, rebounds, assists,
       steals, blocks, turnovers, fgm, fga, threePm, threePa, ftm, fta)
      VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?);
    `;

    await db.query(query, [
      playerId, gameId, minutes, points, rebounds, assists,
      steals, blocks, turnovers, fgm, fga, threePm, threePa, ftm, fta
    ]);

    res.status(201).json({ message: "Player game stats added." });

  } catch (error) {
    console.error("POST /Player_Game_Stats error:", error);
    res.status(500).send("Error creating player game stats.");
  }
});

// -----------------------------
// UPDATE: edit a player's game stats 
// -----------------------------
app.put('/Player_Game_Stats/:playerId/:gameId', async (req, res) => {
  try {
    const playerId = Number(req.params.playerId);
    const gameId = Number(req.params.gameId);

    const {
      minutes, points, rebounds, assists,
      steals, blocks, turnovers, fgm, fga,
      threePm, threePa, ftm, fta
    } = req.body;

    // Fallback since select fields should be integers already
    if (!Number.isInteger(playerId) || !Number.isInteger(gameId)) {
      return res.status(400).send("Invalid playerId or gameId.");
    }

    const query = `
      UPDATE Player_Game_Stats
      SET minutes = ?, points = ?, rebounds = ?, assists = ?,
          steals = ?, blocks = ?, turnovers = ?,
          fgm = ?, fga = ?, threePm = ?, threePa = ?, ftm = ?, fta = ?
      WHERE playerId = ? AND gameId = ?;
    `;

    const [result] = await db.query(query, [
      minutes, points, rebounds, assists,
      steals, blocks, turnovers,
      fgm, fga, threePm, threePa, ftm, fta,
      playerId, gameId
    ]);

    if (result.affectedRows === 0) {
      return res.status(404).send("Stat line not found.");
    }

    res.status(200).json({ message: "Player game stats updated." });

  } catch (error) {
    console.error("PUT /Player_Game_Stats error:", error);
    res.status(500).send("Error updating player game stats.");
  }
});

// -----------------------------
// DELETE: delete a player's game stats from table
// -----------------------------
app.delete('/Player_Game_Stats/:playerId/:gameId', async (req, res) => {
  try {
    const playerId = Number(req.params.playerId);
    const gameId = Number(req.params.gameId);

    // Need both FKs and integers
    if (!Number.isInteger(playerId) || !Number.isInteger(gameId)) {
      return res.status(400).send("Invalid playerId or gameId.");
    }

    const query = `
      DELETE FROM Player_Game_Stats
      WHERE playerId = ? AND gameId = ?;
    `;

    const [result] = await db.query(query, [playerId, gameId]);

    if (result.affectedRows === 0) {
      return res.status(404).send("Stat line not found.");
    }

    res.status(200).json({ message: "Player game stats deleted." });

  } catch (error) {
    console.error("DELETE /Player_Game_Stats error:", error);
    res.status(500).send("Error deleting player game stats.");
  }
});

// ##################################################################################################


// ####################################################################################FOR TEAM_SEASON_STATS TABLE##############
// -----------------------------
// SELECT: See team's season stats
// Utilizes JOINs to get team name and season year
// -----------------------------
app.get('/Team_Season_Stats', async (req, res) => {
  try {
    const query = `
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

    `;
    const [rows] = await db.query(query);
    res.status(200).json(rows);
  } catch (error) {
    console.error("GET /Team_Season_Stats error:", error);
    res.status(500).send("Error fetching team season stats.");
  }
});
// ##################################################################################################

// RESET BUTTON, calls stored function that replaces current tables and data with original sample data
app.post('/Reset', async (req, res) => {
  try {
    // call the SP
    await db.query('CALL sp_reset_data();');
    res.json({message: "Database successfuly reset"});
  } catch(error){
    console.error("RESET error:", error);
    res.status(500).send("Error resetting db");
  }
});
// ########################################

// ########## LISTENER

app.listen(PORT, function () {
    console.log('Express started on http://classwork.engr.oregonstate.edu:' + PORT + '; press Ctrl-C to terminate.');
});
