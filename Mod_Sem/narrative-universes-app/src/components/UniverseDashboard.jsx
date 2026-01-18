import { useState, useEffect, useCallback } from 'react';
import { useSearchParams, useNavigate } from 'react-router-dom';
import { getUniverseDetails } from '../services/sparqlService';
import CharactersList from './CharactersList';
import LocationsList from './LocationsList';
import WorksList from './WorksList';
import './UniverseDashboard.css';

export default function UniverseDashboard() {
    const [params] = useSearchParams();
    const uri = params.get("uri");
    const navigate = useNavigate();

    const [universe, setUniverse] = useState(null);
    const [activeTab, setActiveTab] = useState('characters');
    const [error, setError] = useState(null);

    const fetchUniverse = useCallback(async () => {
        try {
            const data = await getUniverseDetails(uri);
            const b = data.results.bindings[0];
            setUniverse({
                uri,
                name: b.name.value,
                characters: parseInt(b.numCharacters.value),
                locations: parseInt(b.numLocations.value),
                works: parseInt(b.numWorks.value)
            });
            setError(null);
        } catch (e) {
            setError(e.message || 'Errore nel caricamento dell’universo');
        }
    }, [uri]);

    useEffect(() => {
        const id = setTimeout(() => {
            fetchUniverse();
        }, 0);
        return () => clearTimeout(id);
    }, [fetchUniverse]);

    if (!universe && !error) {
        return (
            <div className="loading-state">
                <div className="spinner"></div>
                <p>Caricamento universo...</p>
            </div>
        );
    }

    if (error) {
        return (
            <div className="error">
                <h2>Errore</h2>
                <p>{error}</p>
                <button className="back-button" onClick={fetchUniverse}>Riprova</button>
            </div>
        );
    }

    const tabs = [
        { id: 'characters', label: 'Personaggi', count: universe.characters },
        { id: 'locations', label: 'Luoghi', count: universe.locations },
        { id: 'works', label: 'Opere', count: universe.works }
    ];

    return (
        <div className="dashboard">
            <div className="dashboard-header">
                <div className="universe-info">
                    <button
                        className="home-button"
                        onClick={() => navigate('/')}
                    >
                        <span className="home-icon" aria-hidden="true" />
                        <span className="sr-only">Torna alla home</span>
                    </button>
                    <h1 className="universe-title">{universe.name}</h1>
                    <div className="universe-meta">
                        <span className="meta-item">{universe.characters} Personaggi</span>
                        <span className="meta-separator">•</span>
                        <span className="meta-item">{universe.locations} Luoghi</span>
                        <span className="meta-separator">•</span>
                        <span className="meta-item">{universe.works} Opere</span>
                    </div>
                </div>
            </div>

            <div className="tabs">
                {tabs.map(tab => (
                    <button
                        key={tab.id}
                        className={`tab ${activeTab === tab.id ? 'active' : ''}`}
                        onClick={() => setActiveTab(tab.id)}
                    >
                        {tab.label}
                        <span className="tab-count">{tab.count}</span>
                    </button>
                ))}
            </div>

            <div className="tab-content">
                {activeTab === 'characters' && (
                    <CharactersList universeUri={universe.uri} />
                )}
                {activeTab === 'locations' && (
                    <LocationsList universeUri={universe.uri} />
                )}
                {activeTab === 'works' && (
                    <WorksList universeUri={universe.uri} />
                )}
            </div>
        </div>
    );
}
