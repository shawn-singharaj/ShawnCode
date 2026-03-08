import './App.css';
import { BrowserRouter as Router, Routes, Route } from 'react-router-dom';
import HomePage from './pages/HomePage';
import AddExercise from './pages/AddExercise';
import EditExercise from './pages/EditExercise';
import Navigation from './components/Navigation'


function App() {

  return (
    <div className="app">
        <header>
        <h1>Exercise Tracker</h1>
        <p>An app to track and manage your exercises</p>
       </header>

        <Router>
          <Navigation/>
          <Routes>
            <Route path="/" element={<HomePage/>}></Route>
            <Route path="/add-exercise" element={ <AddExercise />}></Route>
            <Route path="/edit-exercise/:_id" element={ <EditExercise />}></Route>
          </Routes>
        </Router>

        
      <footer>
        <p>©2025 Shawn Singharaj</p>
      </footer>
    </div>
  );
}

export default App;