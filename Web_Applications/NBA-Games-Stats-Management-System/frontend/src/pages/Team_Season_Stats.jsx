import React, { useEffect, useState } from 'react';

export default function Team_Season_Stats({ backendURL }) {
  const [stats, setStats] = useState([]);

  // load team season stats using get request and select query
  const loadStats = async () => {
    const res = await fetch(`${backendURL}/Team_Season_Stats`);
    const data = await res.json();
    setStats(data);
  };

  useEffect(() => { loadStats(); }, []);

  // map all team season statistics in DB onto the table dynamically, along with the season year
  // CUD doesnt work
  return (
    <div>
      <h2>Team Season Stats</h2>

      <table className="nba-table">
        <thead>
          <tr>
            <th>Team</th>
            <th>Season</th>
            <th>Wins</th>
            <th>Losses</th>
            <th>Points For</th>
            <th>Points Against</th>
            <th>Assists For</th>
            <th>Rebounds For</th>
            <th>ThreePm</th>
            <th>ThreePa</th>
            <th>Actions</th>
          </tr>
        </thead>
        <tbody>
          {stats.map((s, index) => (
            <tr key={index}>
              <td>{s.teamName}</td>
              <td>{s.seasonYear}</td>
              <td>{s.wins}</td>
              <td>{s.losses}</td>
              <td>{s.pointsFor}</td>
              <td>{s.pointsAgainst}</td>
              <td>{s.assistsFor}</td>
              <td>{s.reboundsFor}</td>
              <td>{s.threePm}</td>
              <td>{s.threePa}</td>
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


      <h3>Add Team_Season_Stats</h3>

      <form className="add-form" onSubmit={(e) => {
        e.preventDefault();
        alert("Add Team_Season_Stats not implemented yet");
      }}>
        <input type="text" placeholder="teamId Name" required />
        <input type="text" placeholder="seasonId" required />
        <input type="text" placeholder="wins" required />
        <input type="text" placeholder="losses" required />
        <input type="text" placeholder="pointsFor" required />
        <input type="text" placeholder="pointsAgainst" required />
        <input type="text" placeholder="assistsFor" required />
        <input type="text" placeholder="reboundsFor" required />
        <input type="text" placeholder="threePm" required />
        <input type="text" placeholder="threePa" required />
        <button type="submit">Add</button>
      </form>


    </div>
  );
}
