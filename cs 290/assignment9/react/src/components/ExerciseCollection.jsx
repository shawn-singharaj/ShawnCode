import ExerciseItem from './ExerciseItem';
import '../App.css';

function ExerciseCollection({ exercises, onDelete }) {
    return (
        <table className="exercise-table">
            <thead>
                <tr className="exercise-table">
                    <th className="exercise-table">Name</th>
                    <th className="exercise-table">Reps</th>
                    <th className="exercise-table">Weight</th>
                    <th className="exercise-table">Unit</th>
                    <th className="exercise-table">Date</th>
                    <th className="exercise-table"></th>
                </tr>
            </thead>
            <tbody>
            {exercises.map((exercise, i) => (
                    <tr key={i} className="exercise-table">
                        <td className="exercise-table">{exercise.name}</td>
                        <td className="exercise-table">{exercise.reps}</td>
                        <td className="exercise-table">{exercise.weight}</td>
                        <td className="exercise-table">{exercise.unit}</td>
                        <td className="exercise-table">{exercise.date}</td>
                        <td className="exercise-table">
                            <ExerciseItem exercise={exercise} onDelete={onDelete} />
                        </td>
                    </tr>
                ))}
            </tbody>
        </table>
    );
}

export default ExerciseCollection;