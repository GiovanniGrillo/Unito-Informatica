import { useState, useEffect } from 'react';
import { getUniverses } from '../services/sparqlService';
import './HomePage.css';

export default function HomePage({ onSelectUniverse }) {
    const [universes, setUniverses] = useState([]);
    const [loading, setLoading] = useState(true);
    const [error, setError] = useState(null);

    useEffect(() => {
        async function loadUniverses() {
            try {
                const data = await getUniverses();
                const results = data.results.bindings.map(b => ({
                    uri: b.universe.value,
                    name: b.name.value,
                    characters: parseInt(b.numCharacters.value),
                    locations: parseInt(b.numLocations.value),
                    works: parseInt(b.numWorks.value)
                }));
                setUniverses(results);
            } catch (err) {
                setError(err.message);
            } finally {
                setLoading(false);
            }
        }

        loadUniverses();
    }, []);

    if (loading) {
        return (
            <div className="loading">
                <div className="spinner"></div>
                <p>Caricamento universi narrativi...</p>
            </div>
        );
    }

    if (error) {
        return (
            <div className="error">
                <h2>⚠️ Errore</h2>
                <p>{error}</p>
                <p className="error-hint">
                    Assicurati che GraphDB e il proxy server siano attivi
                </p>
            </div>
        );
    }

    const universeEmojis = {
        "Universo di Harry Potter": "🧙‍♂️",
        "Universo di Percy Jackson": "⚡",
        "Universo della Terra di Mezzo": "💍"
    };

    return (
        <div className="home-page">
            <header className="hero">
                <h1 className="hero-title">✨ Esplora gli Universi Narrativi</h1>
                <p className="hero-subtitle">
                    Scegli un universo e scopri personaggi, luoghi, oggetti e opere che lo compongono
                </p>
            </header>

            <div className="universes-grid">
                {universes.map(universe => (
                    <div key={universe.uri} className="universe-card">
                        <div className="universe-icon">
                            {universeEmojis[universe.name] || "🌟"}
                        </div>

                        <h2 className="universe-name">{universe.name}</h2>

                        <p className="universe-description">
                            Un mondo ricco di storie, personaggi e avventure.
                        </p>

                        <div className="universe-stats">
                            <div className="stat">
                                <span className="stat-icon">👤</span>
                                <span className="stat-number">{universe.characters}</span>
                                <span className="stat-label">Personaggi</span>
                            </div>

                            <div className="stat">
                                <span className="stat-icon">📍</span>
                                <span className="stat-number">{universe.locations}</span>
                                <span className="stat-label">Luoghi</span>
                            </div>

                            <div className="stat">
                                <span className="stat-icon">📚</span>
                                <span className="stat-number">{universe.works}</span>
                                <span className="stat-label">Opere</span>
                            </div>
                        </div>

                        <button
                            className="explore-button"
                            onClick={() => onSelectUniverse(universe)}
                        >
                            Esplora Universo →
                        </button>
                    </div>
                ))}
            </div>
        </div>
    );
}
