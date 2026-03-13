import React, { useEffect, useState } from 'react';

export default function Games({ backendURL }) {
  const [games, setGames] = useState([]);

  // load games from db by calling a get request and select query
  const loadGames = async () => {
    const res = await fetch(`${backendURL}/games`);
    const data = await res.json();
    setGames(data);
  };

  useEffect(() => { loadGames(); }, []);

  // map all games in DB onto the table dynamically, and formatting the date so it doesn't have the time
  // CUD doesnt work
  return (
    <div>
      <h2>Games</h2>

      <table className="nba-table">
        <thead>
          <tr>
            <th>gameId</th>
            <th>Game Date</th>
            <th>Season</th>
            <th>Home Team</th>
            <th>Away Team</th>
            <th>Home Score</th>
            <th>Away Score</th>
            <th>Actions</th>
          </tr>
        </thead>
        <tbody>
          {games.map((g) => (
            <tr key={g.gameId}>
              <td>{g.gameId}</td>
              <td>{String(g.gameDate).slice(0, 10)}</td>
              <td>{g.seasonYear}</td>
              <td>{g.homeTeam}</td>
              <td>{g.awayTeam}</td>
              <td>{g.homeScore}</td>
              <td>{g.awayScore}</td>
              <td>
                <button type="button" onClick={() => alert("Edit not implemented yet")}>
                  Edit
                </button>
                <button type="button" onClick={() => alert("Delete not implemented yet")}>
                  Delete
                </button>
              </td>
            </tr>
          ))}
        </tbody>
      </table>

      <h3>Add Games</h3>

      <form className="add-form" onSubmit={(e) => {
        e.preventDefault();
        alert("Add Games not implemented yet");
      }}>
        <input type="text" placeholder="gameDate" required />
        <input type="text" placeholder="seasonId" required />
        <input type="text" placeholder="homeTeamId" required />
        <input type="text" placeholder="awayTeamId" required />
        <input type="text" placeholder="homeScore" required />
        <input type="text" placeholder="awayScore" required />
        <button type="submit">Add</button>
      </form>


    </div>
  );
}
