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


const PORT = 6704;

// ####################################################################################FOR PLAYERS TABLE##############
// -----------------------------
// READ: Get all players TO DISPLAY TABLE IN FRONTEND
// -----------------------------
app.get('/players', async (req, res) => {
  try {
    const query = `
      SELECT playerId, firstName, lastName, position, teamId
      FROM Players
      ORDER BY playerId;
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

    const query = `
      INSERT INTO Players (firstName, lastName, position, teamId)
      VALUES (?, ?, ?, ?);
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

//UPDATE: Update a player

app.put('/players/:id', async (req, res) => {
  try {
    const playerId = Number(req.params.id);
    const { firstName, lastName, position, teamId } = req.body;

    //some basic validation stuff
    if(!Number.isInteger(playerId)) {
      return res.status(400).send("Invalid player ID."); //player id needs to be an integer
    }
    if (!firstName || !lastName || !position) {
      return res.status(400).send("firstName, lastName, and position are required."); //if left blank, send error
    }

    const safeTeamId = (teamId === "" || teamId === undefined) ? null : teamId;   

    //QUERY TO UPDATE A PLAYER
    const query = `     
      UPDATE Players
      SET firstName = ?, lastName = ?, position = ?, teamId = ?
      WHERE playerId = ?;
      `;

    const [result] = await db.query(query, [
      firstName,
      lastName,
      position,
      safeTeamId,
      playerId
    ]);

    if (result.affectedRows === 0) {
      return res.status(404).send("Player not found."); //if no player with that id, send error
    }
    
    res.status(200).json({ message: "Player updated successfully." });
  } catch (error) {
    console.error("PUT /players/:id error:", error);
    res.status(500).send("Error updating player.");
  }

});


//DELETE: Delete a player       WILL NOT WORK YET SINCE IT IS CONNECTED TO THE TEAMS TABLE, NEED TO FIGURE OUT HOW TO DELETE PLAYER WITHOUT DELETING THE TEAM THEY ARE ON, OR DELETE THE TEAM TOO, NOT SURE YET
app.delete('/players/:id', async (req, res) => {
  try {
    const playerId = Number(req.params.id);

    if(!Number.isInteger(playerId)) {
      return res.status(400).send("Invalid player ID."); //player id needs to be an integer
    }

    const query = `
      DELETE FROM Players
      WHERE playerId = ?;
    `;

    const [result] = await db.query(query, [playerId]);

    if (result.affectedRows === 0) {
      return res.status(404).send("Player not found."); //if no player with that id, send error
    }

    res.status(200).json({ message: "Player deleted successfully." });
  } catch (error) {
    console.error("DELETE /players/:id error:", error);
    res.status(500).send("Error deleting player.");
  }

});


// ##################################################################################################






// ####################################################################################FOR TEAMS TABLE##############

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


app.post('/Teams', async (req, res) => {
  try {
    const { teamName, conference, abbreviation } = req.body;

    // basic validation
    if (!teamName || !conference || !abbreviation) {
      return res.status(400).send("teamName, conference, and abbreviation are required.");
    }


    const query = `
      INSERT INTO Teams (teamName, conference, abbreviation)
      VALUES (?, ?, ?);
    `;

    const [result] = await db.query(query, [
      teamName,
      conference,
      abbreviation
    ]);

    // Return the new id (handy for debugging)
    res.status(201).json({ insertedId: result.insertId });
  } catch (error) {
    console.error("POST /Teams error:", error);
    res.status(500).send("Error creating team.");
  }
});



// ##################################################################################################




// ####################################################################################FOR GAMES TABLE##############

app.get('/Games', async (req, res) => {
  try {
    const query = `
      SELECT gameId, gameDate, seasonId, homeTeamId, awayTeamId, homeScore, awayScore
      FROM Games
      ORDER BY gameId;
    `;
    const [rows] = await db.query(query);
    res.status(200).json(rows);
  } catch (error) {
    console.error("GET /Games error:", error);
    res.status(500).send("Error fetching games.");
  }
});

app.post('/Games', async (req, res) => {
  try {
    const { gameDate, seasonId, homeTeamId, awayTeamId, homeScore, awayScore } = req.body;

    // basic validation
    if (!gameDate || !seasonId || !homeTeamId || !awayTeamId || homeScore === undefined || awayScore === undefined) {
      return res.status(400).send("gameDate, seasonId, homeTeamId, awayTeamId, homeScore, and awayScore are required.");
    }

    const query = `
      INSERT INTO Games (gameDate, seasonId, homeTeamId, awayTeamId, homeScore, awayScore)
      VALUES (?, ?, ?, ?, ?, ?);
    `;

    const [result] = await db.query(query, [
      gameDate,
      seasonId,
      homeTeamId,
      awayTeamId,
      homeScore,
      awayScore
    ]);

    // Return the new id (handy for debugging)
    res.status(201).json({ insertedId: result.insertId });
  } catch (error) {
    console.error("POST /Games error:", error);
    res.status(500).send("Error creating game.");
  }
});
// ##################################################################################################



// ####################################################################################FOR SEASONS TABLE##############

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

app.post('/Seasons', async (req, res) => {
  try {
    const { seasonYear, startDate, endDate } = req.body;

    // basic validation
    if (!seasonYear || !startDate || !endDate) {
      return res.status(400).send("seasonYear, startDate, and endDate are required.");
    }

    const query = `
      INSERT INTO Seasons (seasonYear, startDate, endDate)
      VALUES (?, ?, ?);
    `;

    const [result] = await db.query(query, [
      seasonYear,
      startDate,
      endDate
    ]);

    // Return the new id (handy for debugging)
    res.status(201).json({ insertedId: result.insertId });
  } catch (error) {
    console.error("POST /Seasons error:", error);
    res.status(500).send("Error creating season.");
  }
});


// ##################################################################################################




// ####################################################################################FOR PLAYER_GAME_STATS TABLE##############
app.get('/Player_Game_Stats', async (req, res) => {
  try {
  const query = `
    SELECT minutes, points, rebounds, assists, steals, blocks, turnovers, fgm, fga, threePm, threePa, ftm, fta, playerId, gameId
    FROM Player_Game_Stats
    ORDER BY playerId;
  `;
    const [rows] = await db.query(query);
    res.status(200).json(rows);
  } catch (error) {
    console.error("GET /Player_Game_Stats error:", error);
    res.status(500).send("Error fetching player game stats.");
  }
});


// ##################################################################################################


// ####################################################################################FOR TEAM_SEASON_STATS TABLE##############
app.get('/Team_Season_Stats', async (req, res) => {
  try {
    const query = `
      SELECT teamId, seasonId, wins, losses, pointsFor, pointsAgainst, assistsFor, reboundsFor, threePm, threePa
      FROM Team_Season_Stats
      ORDER BY teamId;

    `;
    const [rows] = await db.query(query);
    res.status(200).json(rows);
  } catch (error) {
    console.error("GET /Team_Season_Stats error:", error);
    res.status(500).send("Error fetching team season stats.");
  }
});


// ##################################################################################################

// RESET BUTTON
app.post('/Reset', async (req, res) => {
  try {
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