import { Link, useNavigate, useParams } from 'react-router-dom';
import { useState, useEffect } from 'react';

// create account button
function Login(){
    const [email, setEmail] = useState('');
    const [password, setPassword] = useState('');
    const [error, setError] = useState('');

    const navigate = useNavigate();

    const handleLogin = async (e) => {
        e.preventDefault();
        try{
            const response = await fetch('http://localhost:3000/login', {
                method: 'POST',
                headers: {"Content-Type": "application/json"},
                body: JSON.stringify({email, password}
                )
            });

            const data = await response.json();
            if(data.success){
                alert('Login Successful');
                navigate(`/weekly-view/${data.userId}`);
            }
            else{
                setError(data.error || "Login Failed");
            }
        }
        catch(err){
            setError("Server error");
            console.error("Login error:", err);
        }
      };

    return(
        <div className="login-page">
            <h2>Login</h2>
            {error && <p className="error">{error}</p>}
            <form onSubmit={handleLogin} className="login-form">
                <div>
                    <label htmlFor="email">Email:</label><br />
                    <input
                        type="email"
                        id="email"
                        value={email}
                        onChange={(e) => setEmail(e.target.value)}
                        required
                    />
                </div>

                <div>
                    <label htmlFor="password">Password:</label><br />
                    <input 
                        type="password"
                        id="password"
                        value={password}
                        onChange={(e) => setPassword(e.target.value)}
                        required
                    />
                </div>

                <button type="submit">Log In</button>
                <button type="submit" onClick={() => navigate("/create-account")}>Create Account</button>

                <p>Logging in keeps your schedule saved across devices. Do not share your password.</p>
            </form>
        </div>
    );

}

export default Login;