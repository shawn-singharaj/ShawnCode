import { Link } from 'react-router-dom';
import ExerciseCollection from '../components/ExerciseCollection';
import { useState, useEffect } from 'react';


function HomePage() {
    const [exercises, setExercises] = useState([]);

    const fetchExercises = async () => {
        const response = await fetch('/exercises');
        const data = await response.json();
        setExercises(data);
    }

    useEffect( () => {
        fetchExercises();
    }, []);

    const onDelete = async(_id) => {
        const response = await fetch( `/exercises/${_id}`, {method: 'DELETE'});
        if(response.status === 204){
            setExercises(exercises.filter( e => e._id !== _id))
            alert(`Successfully deleted movie with id ${exercise._id}`);
        }
        else{
            alert(`Failed to delete movie with id ${_id}, status code: ${response.status}`);
        }
    }

    return (
        <>
            <h2>Exercises</h2>
            <ExerciseCollection exercises={exercises} onDelete={onDelete}></ExerciseCollection>
            <Link to="/add-exercise">Add an Exercise</Link>
        </>
    );
}

export default HomePage;