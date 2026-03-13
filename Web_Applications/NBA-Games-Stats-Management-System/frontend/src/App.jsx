import React from 'react';
import { Routes, Route } from 'react-router-dom';

// Pages
import Home from './pages/Home';
import Players from './pages/Players';
import Games from './pages/Games';
import Seasons from './pages/Seasons';
import Teams from './pages/Teams';
import Player_Game_Stats from './pages/Player_Game_Stats';
import Team_Season_Stats from './pages/Team_Season_Stats';

// Components
import Navigation from './components/Navigation';

// Define the backend port and URL for API requests
// Shawn - 6704 
// Andy - 4589
const backendPort = 6709;  // Use the port you assigned to the backend server, this would normally go in a .env file
const backendURL = `http://classwork.engr.oregonstate.edu:${backendPort}`;

function App() {
    return (
        <>
            <Navigation />
            <Routes>
                <Route path="/" element={<Home backendURL={backendURL} />} />
                <Route path="/Players" element={<Players backendURL={backendURL} />} />
                <Route path="/Teams" element={<Teams backendURL={backendURL} />} />
                <Route path="/Games" element={<Games backendURL={backendURL} />} />
                <Route path="/Seasons" element={<Seasons backendURL={backendURL} />} />
                <Route path="/Player_Game_Stats" element={<Player_Game_Stats backendURL={backendURL} />} />
                <Route path="/Team_Season_Stats" element={<Team_Season_Stats backendURL={backendURL} />} />

            </Routes>
        </>
    );

} export default App;
