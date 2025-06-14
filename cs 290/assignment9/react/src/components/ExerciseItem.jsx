import '../App.css';
import {Link} from 'react-router-dom';
import { FiEdit } from "react-icons/fi";
import { MdOutlineDeleteForever } from "react-icons/md";



function ExerciseItem({exercise, onDelete}) {

    return (
        <div className="exercise-table">
            <p>
            <Link to={`/edit-exercise/${exercise._id}`}><FiEdit/></Link> 
                <a href="/" onClick={e => {e.preventDefault(); onDelete(exercise._id)}}><MdOutlineDeleteForever /></a>
            </p>
        </div>
    );
}

export default ExerciseItem;

