import React, { useEffect, useState } from 'react';

export default function Players({ backendURL }) {
  const [players, setPlayers] = useState([]);
  const [teams, setTeams] = useState([]);

  //for editing players, we will need to track which player is being edited and the form data for that player
  const [editingId, setEditingId] = useState(null);

  // formdata includes current team for dynamic dropdown
  const [formData, setFormData] = useState({firstName: '', lastName: '', position: '', teamId: ''});

  const loadPlayers = async () => {   
    const res = await fetch(`${backendURL}/players`);   //fetches the players from backend to display the tables
    const data = await res.json();
    setPlayers(data);   //updates the players state with the data from the backend
  };  

  useEffect(() => { loadPlayers(); }, []);  //load the players

  // fetch teams in the same way
  const loadTeams = async () => {
    const res = await fetch(`${backendURL}/teams`);
    const data = await res.json();
    setTeams(data);  
  };

  useEffect(() => {loadTeams(); }, []);

  const handleChange = (e) => {
    setFormData({ ...formData, [e.target.name]: e.target.value });
  };


  //edit 
  const handleEdit = (player) => {
    setEditingId(player.playerId);
    setFormData({
      firstName: player.firstName,
      lastName: player.lastName,
      position: player.position,
      teamId: player.teamId != null ? String(player.teamId) : ''
    });
  };

  //cancel edit
  const handleCancel = () => {
    setEditingId(null);
    setFormData({ firstName: '', lastName: '', position: '' });
  }

  //delete
  const handleDelete = async (playerId) => {
    await fetch(`${backendURL}/players/${playerId}`, {
      method: 'DELETE'
    });
    loadPlayers();
  }

  //submit edit or add 
  const handleSubmit = async (e) => {
    e.preventDefault(); //prevent page refresh

    const payload = {...formData };

    const url = editingId ? `${backendURL}/players/${editingId}` : `${backendURL}/players`;
    const method = editingId ? 'PUT' : 'POST';

    const res = await fetch(url, {
      method,
      headers: { 'Content-Type': 'application/json' },
      body: JSON.stringify(payload)
    });

    if (!res.ok) {
      alert(await res.text());
      return;
    }

    handleCancel(); //reset form and cancel edit mode
    loadPlayers();
  };

  // map all players from the select query and utilizing the team name
  // dynamic select dropdown menu from loadTeams for when adding/editing a player
  // select automatically fills out for player's current team when editing using formdata
  // Add, Edit, Delete buttons functional
  return (
    <div>
      <h2>Players</h2>

      <table className="nba-table">
        <thead>
          <tr>
            <th>playerId</th>
            <th>First Name</th>
            <th>Last Name</th>
            <th>Position</th>
            <th>Team</th>
            <th>Actions</th>
          </tr>
        </thead>
        <tbody>
          {players.map((p) => (
            <tr key={p.playerId}>
              <td>{p.playerId}</td>
              <td>{p.firstName}</td>
              <td>{p.lastName}</td>
              <td>{p.position}</td>
              <td>{p.teamName}</td>
              <td>
                <button type="button" onClick={() => handleEdit(p)}>Edit</button>
                <button type="button" onClick={() => handleDelete(p.playerId)}>Delete</button>
              </td>
            </tr>
          ))}
        </tbody>
      </table>

      <h3>{editingId !== null ? 'Edit Player' : 'Add Player'}</h3>
      <form className="add-form" onSubmit={handleSubmit}>
        <input name="firstName" placeholder="First Name" value={formData.firstName} onChange={handleChange} required />
        <input name="lastName" placeholder="Last Name" value={formData.lastName} onChange={handleChange} required />
        <input name="position" placeholder="Position" value={formData.position} onChange={handleChange} required />
        <label htmlFor="teamId">Team:</label>
        <select name="teamId" value={formData.teamId} onChange={handleChange}>
          <option value="">None</option>
          {teams.map((team) => (
        <option key={team.teamId} value={String(team.teamId)}>
          {team.teamName}
        </option>
          ))}
        </select>
        <button type="submit">{editingId !== null ? 'Update' : 'Add'}</button>
        {editingId !== null && (
          <button type="button" onClick={handleCancel}>Cancel</button>
        )}
      </form>
    </div>
  );
}

