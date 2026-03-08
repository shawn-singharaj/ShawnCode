import React, { useState, useEffect } from 'react';
import EventItem from './EventItem';
import { Link, useParams, useNavigate } from 'react-router-dom';
import '../App.css';

const currentWeek = (dateObj, dateNum, dayNum, monthNum) => {
  let dateSunday = dateNum - dayNum;

  // Handle if dateSunday goes into the previous month
  if (dateSunday <= 0) {
    const prevMonth = monthNum - 1;
    let daysInPrevMonth = 30;
    if ([0, 2, 4, 6, 7, 9, 11].includes(prevMonth)) daysInPrevMonth = 31;
    if (prevMonth === 1) daysInPrevMonth = 28; 
    dateSunday = daysInPrevMonth + dateSunday;
  }

  const updatedWeek = ['Sunday', 'Monday', 'Tuesday', 'Wednesday', 'Thursday', 'Friday', 'Saturday'].map(
    (day, i) => {
      const date = new Date(dateObj);
      date.setDate(dateSunday + i);
      return {
        day: day,
        date: date.getDate(),
        month: date.getMonth() + 1, 
      };
    }
  );

  return updatedWeek;
};

function WeeklyTable( {userId}) {
  const [currentDate, setCurrentDate] = useState(new Date());
  const [daysOfWeek, setDaysOfWeek] = useState([]);
  const [events, setEvents] = useState({});

  const navigate = useNavigate();


  useEffect(() => {
    const d = new Date(currentDate);
    const updated = currentWeek(d, d.getDate(), d.getDay(), d.getMonth());
    setDaysOfWeek(updated);
  }, [currentDate]);

  useEffect(() => {
  if (!userId) return;

  fetch(`http://localhost:3000/events/user/${userId}`)
    .then((res) => res.json())
    .then((data) => {
      const eventsDay = {};

      data.forEach((event) => {
        // Use event.date if it exists
        let dayName;
        if (event.date) {
          const eventDate = new Date(event.date);
          dayName = eventDate.toLocaleDateString('en-US', { weekday: 'long' });
        } else if (event.reoccuring_day) {
          dayName = event.reoccuring_day;
        }

        if (dayName) {
          if (!eventsDay[dayName]) {
            eventsDay[dayName] = [];
          }
          eventsDay[dayName].push(event);
        }
      });

      setEvents(eventsDay);
    })
    .catch(console.error);
}, [userId]);

  const handlePreviousWeek = () => {
    const newDate = new Date(currentDate);
    newDate.setDate(currentDate.getDate() - 7);
    setCurrentDate(newDate);
  };

  const handleNextWeek = () => {
    const newDate = new Date(currentDate);
    newDate.setDate(currentDate.getDate() + 7);
    setCurrentDate(newDate);
  };

  const handleAddEvent = () => {
    navigate(`/addevent/${userId}`);
  };
  
  return (
    <>
      <div className="weekly-table">
        <button onClick={handlePreviousWeek}>Previous Week</button>
        <button onClick={handleNextWeek}>Next Week</button>
      </div>

      <table className="weekly-table">
        <thead>
          <tr>
            {daysOfWeek.map((dayObj) => (
              <th key={dayObj.day}>
                <Link to={`/daily-view/${userId}/${dayObj.month}/${dayObj.date}/${dayObj.day}`}>
                  <button type="button">
                    {dayObj.day} {dayObj.month}/{dayObj.date}
                  </button>
                </Link>
              </th>
            ))}
          </tr>
        </thead>
        <tbody>
          <tr>
            {daysOfWeek.map((dayObj) => (
              <td key={dayObj.day}>
                {(events[dayObj.day] || []).map((event, index) => (
                  <EventItem key={index} title={event.title}
                    description={event.description}
                    date={event.date}
                    time_end={event.time_end}
                    eventId={event._id} />
                ))}
              </td>
            ))}
          </tr>
        </tbody>
      </table>

       <div className="weekly-table">
            <button onClick={handleAddEvent}>Add Event</button>
        </div>
    </>
  );
}

export default WeeklyTable;
