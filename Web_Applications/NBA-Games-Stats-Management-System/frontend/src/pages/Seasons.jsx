import React, { useEffect, useState } from 'react';

export default function Seasons({ backendURL }) {
  const [seasons, setSeasons] = useState([]);

  // Fetch and load seasons 
  const loadSeasons = async () => {
    const res = await fetch(`${backendURL}/seasons`);
    const data = await res.json();
    setSeasons(data);
  };

  useEffect(() => { loadSeasons(); }, []);

  // map all seasons in DB onto the table dynamically
  // CUD doesnt work
  return (
    <div>
      <h2>Seasons</h2>

      <table className="nba-table">
        <thead>
          <tr>
            <th>seasonId</th>
            <th>Season Year</th>
            <th>Start Date</th>
            <th>End Date</th>
            <th>Actions</th>
          </tr>
        </thead>
        <tbody>
          {seasons.map((s) => (
            <tr key={s.seasonId}>
              <td>{s.seasonId}</td>
              <td>{s.seasonYear}</td>
              <td>{String(s.startDate).slice(0, 10)}</td>
              <td>{String(s.endDate).slice(0, 10)}</td>
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

      <h3>Add Seasons</h3>

      <form className="add-form" onSubmit={(e) => {
        e.preventDefault();
        alert("Add Season not implemented yet");
      }}>
        <input type="text" placeholder="SeasonYear" required />
        <input type="text" placeholder="startDate" required />
        <input type="text" placeholder="endDate" required />
        <button type="submit">Add</button>
      </form>


    </div>
  );
}
