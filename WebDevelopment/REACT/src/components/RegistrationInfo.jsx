import { useState } from "react";

function RegistrationInfo(){
    const [name, setName] = useState('');
    const [email, setEmail] = useState('');

    const handleSubmit = (event) => {
        event.preventDefault(); 
        const message = `Hi ${name}. Your registration email is ${email}.`;
        alert(message);
    };

    return (
        <form onSubmit={handleSubmit}>
            <fieldset>
                <legend>Registration Information</legend>

                <div>
                    <label htmlFor="name">Name: </label>
                    <input
                        type="text"
                        id="name"
                        value={name}
                        onChange={(e) => setName(e.target.value)}
                        required
                    />
                </div>

                <div>
                    <label htmlFor="email">Email: </label>
                    <input
                        type="email"
                        id="email"
                        value={email}
                        onChange={(e) => setEmail(e.target.value)}
                        required
                    />
                </div>

                <button type="submit">Submit</button>
            </fieldset>
        </form>
    );

}

export default RegistrationInfo;