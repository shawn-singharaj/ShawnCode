import React, { useState, useEffect } from 'react';
import { useParams, useNavigate } from 'react-router-dom';

function EditEvent() {
  const { eventId } = useParams();
  const navigate = useNavigate();

  const [formData, setFormData] = useState({
    title: '',
    description: '',
    date: '',
    time_end: '',
    reoccuring_day: '',
  });

  // Fetch the existing event details
  useEffect(() => {
    fetch(`http://localhost:3000/events/${eventId}`)
      .then((res) => res.json())
      .then((data) => {
        // Format datetime for input fields
        const formatDate = (isoString) => isoString ? isoString.slice(0, 16) : '';
        setFormData({
          title: data.title || '',
          description: data.description || '',
          date: formatDate(data.date),
          time_end: formatDate(data.time_end),
          reoccuring_day: data.reoccuring_day || '',
        });
      })
      .catch((err) => console.error('Failed to fetch event:', err));
  }, [eventId]);

  const handleChange = (e) => {
    const { name, value } = e.target;
    setFormData(prev => ({ ...prev, [name]: value }));
  };

  const handleSubmit = (e) => {
    e.preventDefault();

    fetch(`http://localhost:3000/events/${eventId}`, {
      method: 'PUT',
      headers: { 'Content-Type': 'application/json' },
      body: JSON.stringify(formData),
    })
      .then((res) => {
        if (!res.ok) throw new Error('Failed to update event');
        return res.json();
      })
      .then(() => navigate(-1)) // Go back
      .catch((err) => console.error('Error updating event:', err));
  };

  const handleDelete = () => {
  if (window.confirm("Are you sure you want to delete this event?")) {
    fetch(`http://localhost:3000/events/${eventId}`, {
      method: 'DELETE',
    })
      .then(res => {
        if (res.ok) {
          alert("Event deleted successfully");
          navigate(-1); // Go back after deletion
        } else {
          throw new Error('Failed to delete event');
        }
      })
      .catch(err => console.error('Error deleting event:', err));
  }
};

  return (
    <div>
      <h1>Edit Event</h1>
      <form onSubmit={handleSubmit}>
        <label>Title: <input name="title" value={formData.title} onChange={handleChange} required /></label><br />
        <label>Description: <input name="description" value={formData.description} onChange={handleChange} /></label><br />
        <label>Date & Time: <input type="datetime-local" name="date" value={formData.date} onChange={handleChange} required /></label><br />
        <label>End Time: <input type="datetime-local" name="time_end" value={formData.time_end} onChange={handleChange} /></label><br />
        <label>Recurring Day: <input name="reoccuring_day" value={formData.reoccuring_day} onChange={handleChange} /></label><br />
        <button type="submit">Save Changes</button>
        <div></div>
        <button type="button" onClick={handleDelete} style={{ marginLeft: '10px', backgroundColor: 'red', color: 'white' }}>
        Delete Event
        </button>
      </form>
    </div>
  );
}

export default EditEvent;
