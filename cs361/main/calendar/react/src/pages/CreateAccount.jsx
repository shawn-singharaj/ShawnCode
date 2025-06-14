import { Link, useNavigate, useParams } from 'react-router-dom';
import { useState, useEffect } from 'react';

// create account button
function Login(){
    const [email, setEmail] = useState('');
    const [password, setPassword] = useState('');
    const [error, setError] = useState('');

    const navigate = useNavigate();

    const handleCreate = async (e) => {
        e.preventDefault();
        try{
            const response = await fetch('http://localhost:3000/users', {
                method: 'POST',
                headers: {"Content-Type": "application/json"},
                body: JSON.stringify({email, password}
                )
            });

            const data = await response.json();
            if(response.status == 201){
                alert('Account Creation Successful!');
                navigate('/');
            }
            else{
                setError(data.error || "Account Already Exists");
            }
        }
        catch(err){
            setError("Server error");
        }
      };

    return(
        <div className="login-page">
            <h2>Create Your Account Here:</h2>
            {error && <p className="error">{error}</p>}
            <form onSubmit={handleCreate} className="login-form">
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

                <button type="submit">Create Account</button>

                <p>Don't have an account yet? Create one here!</p>
            </form>
        </div>
    );

}

export default Login;