import {Link} from 'react-router-dom';
import '../App.css';

function Navigation(){

    return(
         <nav className="app-nav">
            <div className="nav-buttons">
                <Link to="/">
                    <button className="nav-button">Home</button>
                </Link>
                
                <Link to="/add-exercise">
                    <button className="nav-button">Create</button>
                </Link>
            </div>
        </nav>
    );
}

export default Navigation;