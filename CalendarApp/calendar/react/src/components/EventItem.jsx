import { Link } from "react-router-dom";

export default function EventItem({ title, description, date, time_end, eventId }) {
  const startTime = new Date(date).toLocaleTimeString([], { hour: '2-digit', minute: '2-digit' });
  const endTime = time_end ? new Date(time_end).toLocaleTimeString([], { hour: '2-digit', minute: '2-digit' }) : null;

  return (
    <div className="event-item">
      <h4><Link to={`/editevent/${eventId}`} style={{ color: 'white' }}>{title}</Link></h4>
      {description && <p>{description}</p>}
      <p>
        {startTime}
        {endTime && ` - ${endTime}`}
      </p>
    </div>
  );
  }