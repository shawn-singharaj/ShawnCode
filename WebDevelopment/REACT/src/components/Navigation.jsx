import {Link} from 'react-router-dom';
import '../App.css';

function Navigation(){

    return(
        <nav className="app-nav">
            <table className="home-table">
                <caption>Options:</caption>
                <tbody>
                    <tr className="home-table">
                        <td className="home-table">
                            <Link to="/">Home</Link> 
                        </td>
                    </tr>
                    <tr className="home-table">
                        <td className="home-table">
                            <Link to="/order">Order</Link>
                        </td>
                    </tr>
                    <tr className="home-table">
                        <td className="home-table">                        
                            <Link to="/registration">Registration</Link>
                        </td>
                    </tr>
                </tbody>          
            </table>
        </nav>
    );
}

export default Navigation;