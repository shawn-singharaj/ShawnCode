import React, { useEffect, useState } from 'react';

export default function Teams({ backendURL }) {
  const [teams, setTeams] = useState([]);

  // fetch teams with get request and select query
  const loadTeams = async () => {
    const res = await fetch(`${backendURL}/Teams`);
    const data = await res.json();
    setTeams(data);
  };

  useEffect(() => { loadTeams(); }, []);

  // map all teams in DB onto the table dynamically
  // CUD doesnt work
  return (
    <div>
      <h2>Teams</h2>

      <table className="nba-table">
        <thead>
          <tr>
            <th>teamId</th>
            <th>teamName</th>
            <th>conference</th>
            <th>abbreviation</th>
            <th>Actions</th>
          </tr>
        </thead>
        <tbody>
          {teams.map((t) => (
            <tr key={t.teamId}>
              <td>{t.teamId}</td>
              <td>{t.teamName}</td>
              <td>{t.conference}</td>
              <td>{t.abbreviation}</td>
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


      <h3>Add Team</h3>

      <form className="add-form" onSubmit={(e) => {
        e.preventDefault();
        alert("Add Team not implemented yet");
      }}>
        <input type="text" placeholder="Team Name" required />
        <input type="text" placeholder="Conference" required />
        <input type="text" placeholder="Abbreviation" required />
        <button type="submit">Add</button>
      </form>

      
    </div>
  );
}
