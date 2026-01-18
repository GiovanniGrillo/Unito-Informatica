import { useState, useEffect } from 'react';
import { useNavigate } from 'react-router-dom';
import { getLocationsByUniverse } from '../services/sparqlService';
import './LocationsList.css';

export default function LocationsList({ universeUri }) {
    const [locations, setLocations] = useState([]);
    const [loading, setLoading] = useState(true);
    const [filter, setFilter] = useState('all');

    const navigate = useNavigate();

    // Etichette italiane per i ruoli
    const roleLabels = {
        SafePlace: "Luogo Sicuro",
        DangerZone: "Zona Pericolosa",
        LiminalSpace: "Spazio di Confine"
    };

    useEffect(() => {
        async function loadLocations() {
            try {
                const data = await getLocationsByUniverse(universeUri);
                const raw = data.results.bindings;

                const grouped = {};

                raw.forEach(b => {
                    const uri = b.location.value;

                    if (!grouped[uri]) {
                        grouped[uri] = {
                            uri,
                            name: b.name.value,
                            narrativeFunction: b.narrativeFunction?.value || "",
                            types: new Set()
                        };
                    }

                    // Estrai localName da URI (sia con # che con /)
                    const role = b.type?.value?.split(/[#/]/).pop() || "Location";
                    grouped[uri].types.add(role);
                });

                const finalLocations = Object.values(grouped).map(l => ({
                    ...l,
                    types: Array.from(l.types).filter(t => t !== "Location")
                }));

                setLocations(finalLocations);
            } catch (error) {
                console.error("Errore nel caricamento dei luoghi:", error);
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

    // Conteggi per i filtri
    const typeCounts = {
        all: locations.length,
        SafePlace: locations.filter(l => l.types.includes("SafePlace")).length,
        DangerZone: locations.filter(l => l.types.includes("DangerZone")).length,
        LiminalSpace: locations.filter(l => l.types.includes("LiminalSpace")).length
    };

    // Filtro attivo
    const filteredLocations =
        filter === 'all'
            ? locations
            : locations.filter(l => l.types.includes(filter));

    return (
        <div className="locations-list">
            {/* FILTRI */}
            <div className="filters">
                <button
                    className={`filter-btn ${filter === 'all' ? 'active' : ''}`}
                    onClick={() => setFilter('all')}
                >
                    Tutti ({typeCounts.all})
                </button>

                <button
                    className={`filter-btn ${filter === 'SafePlace' ? 'active' : ''}`}
                    onClick={() => setFilter('SafePlace')}
                >
                    Luoghi Sicuri ({typeCounts.SafePlace})
                </button>

                <button
                    className={`filter-btn ${filter === 'DangerZone' ? 'active' : ''}`}
                    onClick={() => setFilter('DangerZone')}
                >
                    Zone Pericolose ({typeCounts.DangerZone})
                </button>

                <button
                    className={`filter-btn ${filter === 'LiminalSpace' ? 'active' : ''}`}
                    onClick={() => setFilter('LiminalSpace')}
                >
                    Spazi Liminali ({typeCounts.LiminalSpace})
                </button>
            </div>

            {/* GRID */}
            <div className="cards-grid">
                {filteredLocations.length === 0 ? (
                    <div className="empty-state">
                        <p>Nessun luogo trovato</p>
                    </div>
                ) : (
                    filteredLocations.map(location => (
                        <div
                            key={location.uri}
                            className="location-card"
                            onClick={() =>
                                navigate(`/entity?uri=${encodeURIComponent(location.uri)}`)
                            }
                        >
                            <h3 className="location-name">{location.name}</h3>

                            <div className="location-tags">
                                {location.types.map(role => (
                                    <span key={role} className="tag">
                                        {roleLabels[role] || role}
                                    </span>
                                ))}
                            </div>

                            {location.narrativeFunction && (
                                <p className="location-description">
                                    Funzione narrativa: {location.narrativeFunction}
                                </p>
                            )}
                        </div>
                    ))
                )}
            </div>
        </div>
    );
}
