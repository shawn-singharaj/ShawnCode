import './App.css'
import { BrowserRouter as Router, Routes, Route } from 'react-router-dom';
import items from './data/items';
import Navigation from './components/Navigation'
import HomePage from './pages/HomePage'
import OrderPage from './pages/OrderPage'
import RegistrationPage from './pages/RegistrationPage'



function App() {

  return (
      <div className="app">
        <Router>
          <Navigation/>
          <Routes>
            <Route path="/" element={<HomePage />}></Route>
            <Route path="/order" element={<OrderPage />}></Route>
            <Route path="/registration" element={<RegistrationPage />}></Route>
          </Routes>
        </Router>
      </div>
  )
}

export default App
