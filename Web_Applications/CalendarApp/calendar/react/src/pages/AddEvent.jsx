import React, { useState } from 'react';
import { useParams, useNavigate } from 'react-router-dom';

function AddEvent() {
  const { userId } = useParams();
  const navigate = useNavigate();

  const [formData, setFormData] = useState({
    title: '',
    description: '',
    date: '',
    time_end: '',
    reoccuring_day: '',
  });

  const handleChange = (e) => {
    const { name, value } = e.target;
    setFormData(prev => ({ ...prev, [name]: value }));
  };

  const handleSubmit = async (e) => {
    e.preventDefault();

    const eventData = {
      ...formData,
      userId,
      date: new Date(formData.date), // Ensure ISO date format
      time_end: formData.time_end ? new Date(formData.time_end) : null
    };

    try {
      const res = await fetch('http://localhost:3000/events', {
        method: 'POST',
        headers: { 'Content-Type': 'application/json' },
        body: JSON.stringify(eventData)
      });

      if (!res.ok) throw new Error('Failed to add event');

      navigate(`/weekly-view/${userId}`);
    } catch (err) {
      console.error('Error adding event:', err);
    }
  };

  return (
    <div className="add-event-form">
      <h2>Add New Event</h2>
      <form onSubmit={handleSubmit}>
        <label>
          Title (required):
          <input type="text" name="title" value={formData.title} required onChange={handleChange} />
        </label>
        <br />

        <label>
          Description:
          <textarea name="description" value={formData.description} onChange={handleChange} />
        </label>
        <br />

        <label>
          Date (Required):
          <input type="datetime-local" name="date" value={formData.date} required onChange={handleChange} />
        </label>
        <br />

        <label>
          End Time (Required):
          <input type="datetime-local" name="time_end" value={formData.time_end} onChange={handleChange} />
        </label>
        <br />

        <label>
          Reoccurring Day:
          <select name="reoccuring_day" value={formData.reoccuring_day} onChange={handleChange}>
            <option value="">None</option>
            {['Sunday','Monday','Tuesday','Wednesday','Thursday','Friday','Saturday'].map(day => (
              <option key={day} value={day}>{day}</option>
            ))}
          </select>
        </label>
        <br />

        <button type="submit">Add Event</button>
      </form>
    </div>
  );
}

export default AddEvent;
