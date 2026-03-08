
import './App.css'
import { BrowserRouter as Router, Routes, Route } from 'react-router-dom';
import Login from './pages/Login';
import DailyView from './pages/DailyView';
import WeeklyView from './pages/WeeklyView';
import Navigation from './components/Navigation';
import CreateAccount from './pages/CreateAccount';
import AddEvent from './pages/AddEvent';
import EditEvent from './pages/EditEvent';
import Settings from './pages/Settings';



function App() {

  return (
    <>
      <div className="app">
       <header className="main-header">
        <h2>Shawn's Weekly Planner App</h2>
        <p>An app to plan your time and schedule: Add, Edit, Delete events to help you visualize
          your weekly and daily plans
        </p>
        <Router>
          <Routes>
            <Route path="/" element={<Login/>}></Route>
            <Route path="/weekly-view/:userId" element={ <WeeklyView/>}></Route>
            <Route path="/daily-view/:userId/:month/:date/:day" element={ <DailyView/>}></Route>
            <Route path="/create-account" element={<CreateAccount/>}></Route>
            <Route path="/addevent/:userId" element={<AddEvent/>}></Route>
            <Route path="/editevent/:eventId" element={<EditEvent/>}></Route>
            <Route path="/settings/:userId" element={<Settings/>}></Route>       
          </Routes>
        </Router>
       </header>
      
      

      <footer className="main-footer">
        <p>
        ©Shawn Singharaj / CS361 2025
        </p>
      </footer>
      </div>
    </>
  );
}

export default App;
