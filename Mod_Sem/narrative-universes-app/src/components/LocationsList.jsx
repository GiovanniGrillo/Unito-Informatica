import { useState, useEffect } from 'react';
import { getLocationsByUniverse } from '../services/sparqlService';
import './LocationsList.css';

export default function LocationsList({ universeUri }) {
    const [locations, setLocations] = useState([]);
    const [loading, setLoading] = useState(true);
    const [filter, setFilter] = useState('all');

    useEffect(() => {
        async function loadLocations() {
            try {
                const data = await getLocationsByUniverse(universeUri);
                const results = data.results.bindings.map(b => ({
                    uri: b.location.value,
                    name: b.name.value,
                    type: b.type?.value || 'Location',
                    narrativeFunction: b.function?.value || null,
                    dangerLevel: b.danger?.value || null
                }));
                setLocations(results);
            } catch (err) {
                console.error('Error loading locations:', err);
            } finally {
                setLoading(false);
            }
        }

        loadLocations();
    }, [universeUri]);

    if (loading) {
        return (
            <div className="loading-state">
                <div className="spinner"></div>
                <p>Caricamento luoghi...</p>
            </div>
        );
    }

    const filtered = locations.filter(loc => {
        if (filter === 'all') return true;
        return loc.type === filter;
    });

    const typeCounts = {
        all: locations.length,
        SafePlace: locations.filter(l => l.type === 'SafePlace').length,
        DangerZone: locations.filter(l => l.type === 'DangerZone').length,
        LiminalSpace: locations.filter(l => l.type === 'LiminalSpace').length
    };

    return (
        <div className="locations-list">
            <div className="filters">
                <button className={filter === 'all' ? 'active' : ''} onClick={() => setFilter('all')}>
                    Tutti ({typeCounts.all})
                </button>

                {typeCounts.SafePlace > 0 && (
                    <button className={filter === 'SafePlace' ? 'active' : ''} onClick={() => setFilter('SafePlace')}>
                        Luoghi Sicuri ({typeCounts.SafePlace})
                    </button>
                )}

                {typeCounts.DangerZone > 0 && (
                    <button className={filter === 'DangerZone' ? 'active' : ''} onClick={() => setFilter('DangerZone')}>
                        Zone Pericolose ({typeCounts.DangerZone})
                    </button>
                )}

                {typeCounts.LiminalSpace > 0 && (
                    <button className={filter === 'LiminalSpace' ? 'active' : ''} onClick={() => setFilter('LiminalSpace')}>
                        Spazi di Confine ({typeCounts.LiminalSpace})
                    </button>
                )}
            </div>

            <div className="cards-grid">
                {filtered.length === 0 ? (
                    <div className="empty-state">Nessun luogo trovato</div>
                ) : (
                    filtered.map(loc => (
                        <div key={loc.uri} className="location-card">
                            <h3 className="location-name">{loc.name}</h3>
                            <span className="location-type">{loc.type}</span>

                            <div className="location-info">
                                {loc.narrativeFunction && (
                                    <p><strong>Funzione narrativa:</strong> {loc.narrativeFunction}</p>
                                )}
                                {loc.dangerLevel && (
                                    <p><strong>Pericolo:</strong> {loc.dangerLevel}</p>
                                )}
                            </div>
                        </div>
                    ))
                )}
            </div>
        </div>
    );
}
