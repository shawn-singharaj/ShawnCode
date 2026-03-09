import {Link, useNavigate, useParams} from 'react-router-dom';
import '../App.css';

function Navigation(){
    const navigate = useNavigate();
    const {userId} = useParams();

    const handleLoginClick = (e) => {
        const confirmed = window.confirm("Are you sure you want to log out?");
        if(confirmed){
            navigate('/');
        }
    };


    return(
         <nav className="app-nav">
            <div className="nav-buttons">
                <Link to="/">
                    <button className="nav-button" onClick={handleLoginClick}>Log Out</button>
                </Link>
                <Link to={`/weekly-view/${userId}`}>
                    <button className="nav-button">Weekly View</button>
                </Link>
                <Link to={`/settings/${userId}`}>
                    <button className="nav-button">Settings</button>
                </Link>
            </div>
        </nav>
    );
}

export default Navigation;