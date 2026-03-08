import { useState } from 'react';
import { useNavigate } from 'react-router-dom';

export const AddExercise = () => {

    const [name, setName] = useState('');
    const [reps, setReps] = useState('');
    const [weight, setWeight] = useState('');
    const [unit, setUnit] = useState('');
    const [date, setDate] = useState('');

    const navigate = useNavigate();

    const addExercise = async () => {
        const newExercise = {name, reps, weight, unit, date};
        const response = await fetch(
            '/exercises', {
                method: 'POST',
                headers: {'Content-type': 'application/json'},
                body: JSON.stringify(newExercise)
            });
            if(response.status === 201){
                alert("Succesfully added exercise");
            }
            else{
                alert("Failed to add exercise");
            }
            navigate('/');
    };

    return (
        <div>
            <h2>Add Exercise</h2>
            <input
                type="text"
                placeholder="Enter exercise name"
                value={name}
                onChange={e => setName(e.target.value)} />
            <input
                type="number"
                value={reps}
                placeholder="Enter reps"
                onChange={e => setReps(e.target.valueAsNumber)} />
            <input
                type="number"
                placeholder="Enter weight"
                value={weight}
                onChange={e => setWeight(e.target.valueAsNumber)} />
            <input
                type="text"
                placeholder="Enter units"
                value={unit}
                onChange={e => setUnit(e.target.value)} />
            <input
                type="text"
                placeholder="Enter date (mm-dd-yy)"
                value={date}
                onChange={e => setDate(e.target.value)} />
            <button
                onClick={addExercise}
            >Add</button>
        </div>
    );
}

export default AddExercise;