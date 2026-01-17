import { useState } from 'react';
import HomePage from './components/HomePage';
import UniverseDashboard from './components/UniverseDashboard';
import './App.css';

function App() {
    const [selectedUniverse, setSelectedUniverse] = useState(null);

    return (
        <div className="app">
            <header className="header">
                <h1>Narrative Universes Explorer</h1>
                {selectedUniverse && (
                    <button
                        className="back-button"
                        onClick={() => setSelectedUniverse(null)}
                    >
                        ← Torna alla Home
                    </button>
                )}
            </header>

            <div className="container">
                {!selectedUniverse ? (
                    <HomePage onSelectUniverse={setSelectedUniverse} />
                ) : (
                    <UniverseDashboard universe={selectedUniverse} />
                )}
            </div>
        </div>
    );
}

export default App; 