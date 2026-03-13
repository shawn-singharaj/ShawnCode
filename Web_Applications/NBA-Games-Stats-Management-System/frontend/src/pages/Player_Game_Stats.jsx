import React, { useEffect, useState } from 'react';

export default function Player_Game_Stats({ backendURL }) {
  const [stats, setStats] = useState([]);
  const [players, setPlayers] = useState([]);
  const [games, setGames] = useState([]);
  // set state to Player_Game_Stats, Players (for name), Games (for matchup) tables

  const [editingId, setEditingId] = useState(null);

  // set form data to be populated by player stat data
  const [formData, setFormData] = useState({playerId: '', gameId: '', minutes: '', points: '', rebounds: '', assists: '', 
    steals: '', blocks: '', turnovers: '', fgm: '', fga: '', threePm: '', threePa: '', ftm: '', fta: ''});

  // load player stats with get request and select query
  const loadStats = async () => {
    const res = await fetch(`${backendURL}/Player_Game_Stats`);
    const data = await res.json();
    setStats(data);
  };

  useEffect(() => { loadStats(); }, []);

  // load player list with get request and select query for dropdown select
  const loadPlayers = async () => {
    const res = await fetch(`${backendURL}/players`);
    const data = await res.json();
    setPlayers(data);
  };

  useEffect(() => { loadPlayers(); }, []);

  // load games list with get request and select query for dropdown select
  const loadGames = async () => {
    const res = await fetch(`${backendURL}/Games`);
    const data = await res.json();
    setGames(data);
  };

  useEffect(() => { loadGames(); }, []);

  const handleChange = (e) => {
    setFormData({ ...formData, [e.target.name]: e.target.value });
  }

  // set form data so when editing, the row's data will be populated in the input fields
  // edit 
  const handleEdit = (pgs) => {
    setEditingId({playerId: pgs.playerId, 
      gameId: pgs.gameId});
    setFormData({
      playerId: String(pgs.playerId), gameId: String(pgs.gameId), minutes: pgs.minutes, 
      points: pgs.points, rebounds: pgs.rebounds, assists: pgs.assists, 
      steals: pgs.steals, blocks: pgs.blocks, turnovers: pgs.turnovers, 
      fgm: pgs.fgm, fga: pgs.fga, threePm: pgs.threePm, threePa: pgs.threePa, 
      ftm: pgs.ftm, fta: pgs.fta
    });
  }

  // cancel edit
  const handleCancel = () => {
    setEditingId(null);
    setFormData({
      playerId: '', gameId: '', minutes: '', points: '', rebounds: '', assists: '', 
      steals: '', blocks: '', turnovers: '', fgm: '', fga: '', threePm: '', threePa: '', 
      ftm: '', fta: ''
    });
  }

  // delete request using the two FK
  const handleDelete = async (playerId, gameId) => {
    if (!window.confirm("Delete this stat line?")) return;

    const res = await fetch(
      `${backendURL}/Player_Game_Stats/${playerId}/${gameId}`,
      { method: "DELETE" }
    );

    if (!res.ok) {
      alert(await res.text());
      return;
    }

    loadStats();
  };

  // when editing or adding something
  const handleSubmit = async (e) => {
      e.preventDefault();

      const payload = {...formData };

      const url = editingId ? `${backendURL}/Player_Game_Stats/${editingId.playerId}/${editingId.gameId}` : `${backendURL}/Player_Game_Stats`;
      const method = editingId ? 'PUT' : 'POST';

      const res = await fetch(url, {
        method,
        headers: { 'Content-Type': 'application/json '},
        body: JSON.stringify(payload)
      });

      if (!res.ok){
        alert(await res.text());
        return;
      }

      handleCancel();
      loadStats();
    }

  // map all stats from the select query and utilizing the player's name and gamedate and matchup
  // two dynamic select dropdown menus from loadPlayers and loadGames for when adding/editing a statline 
  // select automatically fills out for player's current team when editing using formdata
  // the rest of the input fields are integer inputs
  // Add, Edit, Delete buttons functional
  return (
    <div>
      <h2>Player Game Stats</h2>

      <table className="nba-table">
        <thead>
          <tr>
            <th>Player</th>
            <th>Matchup</th>
            <th>Minutes</th>
            <th>Points</th>
            <th>Rebounds</th>
            <th>Assists</th>
            <th>Steals</th>
            <th>Blocks</th>
            <th>Turnovers</th>
            <th>Fgm</th>
            <th>Fga</th>
            <th>ThreePm</th>
            <th>ThreePa</th>
            <th>Ftm</th>
            <th>Fta</th>
            <th>Actions</th>
          </tr>
        </thead>
        <tbody>
          {stats.map((s, index) => (
            <tr key={index}>
              <td>{s.lastName}, {s.firstName}</td>
              <td>{s.gameDate}, {s.matchup}</td>
              <td>{s.minutes}</td>
              <td>{s.points}</td>
              <td>{s.rebounds}</td>
              <td>{s.assists}</td>
              <td>{s.steals}</td>
              <td>{s.blocks}</td>
              <td>{s.turnovers}</td>
              <td>{s.fgm}</td>
              <td>{s.fga}</td>
              <td>{s.threePm}</td>
              <td>{s.threePa}</td>
              <td>{s.ftm}</td>
              <td>{s.fta}</td>
              <td>
                <button type="button" onClick={() => handleEdit(s)}>
                  Edit
                </button>
                <button type="button" onClick={() => handleDelete(s.playerId, s.gameId)}>
                  Delete
                </button>
              </td>
            </tr>
          ))}
        </tbody>
      </table>


      <h3>{editingId !== null ? 'Edit Player Game Stats' : 'Add Player Game Stats'}</h3>
      <form className="add-form" onSubmit={handleSubmit}>
      <select
          name="playerId"
          value={formData.playerId}
          onChange={handleChange}
          required
        >
          <option value="">Select Player</option>
          {players.map((p) => (
            <option key={p.playerId} value={p.playerId}>
              {p.firstName} {p.lastName}
            </option>
          ))}
        </select>


         <select
            name="gameId"
            value={formData.gameId}
            onChange={handleChange}
            required
          >
            <option value="">Select Game</option>
            {games.map((g) => (
              <option key={g.gameId} value={g.gameId}>
                {g.gameDate}, {g.matchup}
              </option>
            ))}
          </select>
          
        <input type="number" name="minutes" value={formData.minutes} onChange={handleChange} placeholder="Minutes" required />
        <input type="number" name="points" value={formData.points} onChange={handleChange} placeholder="Points" required />
        <input type="number" name="rebounds" value={formData.rebounds} onChange={handleChange} placeholder="Rebounds" required />
        <input type="number" name="assists" value={formData.assists} onChange={handleChange} placeholder="Assists" required />
        <input type="number" name="steals" value={formData.steals} onChange={handleChange} placeholder="Steals" required />
        <input type="number" name="blocks" value={formData.blocks} onChange={handleChange} placeholder="Blocks" required />
        <input type="number" name="turnovers" value={formData.turnovers} onChange={handleChange} placeholder="Turnovers" required />
        <input type="number" name="fgm" value={formData.fgm} onChange={handleChange} placeholder="FGM" required />
        <input type="number" name="fga" value={formData.fga} onChange={handleChange} placeholder="FGA" required />
        <input type="number" name="threePm" value={formData.threePm} onChange={handleChange} placeholder="3PM" required />
        <input type="number" name="threePa" value={formData.threePa} onChange={handleChange} placeholder="3PA" required />
        <input type="number" name="ftm" value={formData.ftm} onChange={handleChange} placeholder="FTM" required />
        <input type="number" name="fta" value={formData.fta} onChange={handleChange} placeholder="FTA" required />

        <button type="submit">{editingId !== null ? 'Update' : 'Add'}</button>

        {editingId !== null && (
          <button type="button" onClick={handleCancel}>Cancel</button>
        )}
      </form>
    </div>
  );
}
