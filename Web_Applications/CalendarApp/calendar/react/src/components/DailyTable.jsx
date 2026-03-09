import EventItem from './EventItem';
import '../App.css';

export default function DailyTable ({events, dayOfWeek}) {
  return (
    <table className="daily-table">
      <thead>
        <tr>
          <th key={dayOfWeek}>{dayOfWeek}</th>
        </tr>
      </thead>
      <tbody>
        {events.map((eventI, index) => (
          <tr key={index}>
            <td>
              <EventItem title={eventI.title}
              description={eventI.description}
              date={eventI.date}
              time_end={eventI.time_end}
              eventId={eventI._id}
              />
            </td>
          </tr>
        ))}
      </tbody>
    </table>
  );
}