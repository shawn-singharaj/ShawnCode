import React, { useState } from 'react';
import { useNavigate } from 'react-router-dom';
import Navigation from '../components/Navigation';

function SettingsPage({ userId, currentEmail }) {
  const navigate = useNavigate();
  const [formData, setFormData] = useState({
    email: currentEmail || '',
    password: '',
  });
  const [error, setError] = useState(null);

  const handleChange = e => {
    const { name, value } = e.target;
    setFormData(prev => ({ ...prev, [name]: value }));
  };

  const handleUpdate = async e => {
    e.preventDefault();
    setError(null);

    try {
      const res = await fetch(`http://localhost:3000/users/${userId}`, {
        method: 'PUT',
        headers: { 'Content-Type': 'application/json' },
        body: JSON.stringify(formData),
      });

      if (!res.ok) {
        const data = await res.json();
        throw new Error(data.message || 'Failed to update user');
      }

      alert('User updated successfully');
      setFormData(prev => ({ ...prev, password: '' })); // clear password
    } catch (err) {
      setError(err.message);
    }
  };

  const handleDelete = async () => {
    if (!window.confirm('Are you sure you want to delete your account? This action cannot be undone.')) {
      return;
    }

    try {
      const res = await fetch(`http://localhost:3000/users/${userId}`, {
        method: 'DELETE',
      });

      if (!res.ok) {
        const data = await res.json();
        throw new Error(data.message || 'Failed to delete user');
      }

      alert('Account deleted successfully');
      navigate('/'); // redirect to home or login page
    } catch (err) {
      setError(err.message);
    }
  };

  return (
    <div>
        <Navigation/>
      <h2>Settings</h2>
      {error && <p style={{ color: 'red' }}>{error}</p>}
      <form onSubmit={handleUpdate}>
        <label>
          Email: 
          <input
            type="email"
            name="email"
            value={formData.email}
            onChange={handleChange}
            required
          />
        </label><br />

        <label>
          Password (leave blank to keep current):
          <input
            type="password"
            name="password"
            value={formData.password}
            onChange={handleChange}
            placeholder="New password"
          />
        </label><br />

        <button type="submit">Update</button>
      </form>

      <hr />

      <button
        onClick={handleDelete}
        style={{ backgroundColor: 'red', color: 'white', marginTop: '20px' }}
      >
        Delete Account
      </button>
    </div>
  );
}

export default SettingsPage;
