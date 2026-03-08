import { useState } from 'react';
import { useNavigate, useParams } from 'react-router-dom';


export const EditExercise = () => {
    
    const {_id} = useParams();
    const [name, setName] = useState('');
    const [reps, setReps] = useState('');
    const [weight, setWeight] = useState('');
    const [unit, setUnit] = useState('kg');
    const [date, setDate] = useState('');

    const navigate = useNavigate();

    const onEdit = async () => {
        const editedExercise = {name, reps, weight, unit, date, _id};
        const response = await fetch(
            `/exercises/${_id}`, {
                method: "PUT",
                headers: {"Content-Type": "application/json"},
                body: JSON.stringify(editedExercise)
            }
        );
        if(response.status === 200){
            alert(`Succesfully edited exercise with id ${_id}`);
        }
        else{
            alert(`Failed to edit exercise with id ${_id}`);
        }
        navigate('/');
    }

    return (
        <>
        <h2>Edit Exercise</h2>
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
         <select
                value={unit}
                onChange={e => setUnit(e.target.value)}>
                <option value="kg">kg</option>
                <option value="lbs">lbs</option>
            </select>
        <input
               type="text"
               placeholder="Enter date (mm-dd-yy)"
               value={date}
               onChange={e => setDate(e.target.value)} />
        <button onClick={onEdit}>Edit</button>
        </>
    );
}

export default EditExercise;