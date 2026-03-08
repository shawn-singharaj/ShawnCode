import { useEffect, useState } from 'react';
import { useParams } from 'react-router-dom';
import DailyTable from '../components/DailyTable';
import Navigation from '../components/Navigation';

function DailyView() {
  const { userId, month, date, day } = useParams();
  const [events, setEvents] = useState([]);
  const [loading, setLoading] = useState(true);

  // Build ISO date string in YYYY-MM-DD format — adjust year as needed
  // Make sure month and date are padded with leading zeros if single digit
  const pad = (n) => n.toString().padStart(2, '0');
  const isoDate = `2025-${pad(month)}-${pad(date)}`;

  useEffect(() => {
    async function fetchEvents() {
      try {
        const response = await fetch(`http://localhost:3000/events/user/${userId}?date=${isoDate}`);
        if (!response.ok) throw new Error('Network response was not ok');
        const data = await response.json();
        setEvents(data);
      } catch (error) {
        console.error('Failed to fetch events:', error);
        setEvents([]);
      } finally {
        setLoading(false);
      }
    }

    fetchEvents();
  }, [userId, isoDate]);

  if (loading) return <p>Loading events...</p>;

  const dayOfWeek = new Date(isoDate).toLocaleDateString('en-US', { weekday: 'long' });

  return (
    <>
      <Navigation />
      <h2>Daily View for {day}, {isoDate}</h2>
      <DailyTable events={events} dayOfWeek={day} />
    </>
  );
}

export default DailyView;
