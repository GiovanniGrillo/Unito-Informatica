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
        SAFEPLACE: "Luogo Sicuro",
        DANGERZONE: "Zona Pericolosa",
        LIMINALSPACE: "Spazio di Confine"
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
                    const role = b.type?.value?.split(/[#/]/).pop() || "LOCATION";
                    grouped[uri].types.add(role);
                });

                const finalLocations = Object.values(grouped).map(l => ({
                    ...l,
                    types: Array.from(l.types).filter(t => t !== "LOCATION" && t !== "Location")
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
        SAFEPLACE: locations.filter(l => l.types.includes("SAFEPLACE")).length,
        DANGERZONE: locations.filter(l => l.types.includes("DANGERZONE")).length,
        LIMINALSPACE: locations.filter(l => l.types.includes("LIMINALSPACE")).length
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
                    className={`filter-btn ${filter === 'SAFEPLACE' ? 'active' : ''}`}
                    onClick={() => setFilter('SAFEPLACE')}
                >
                    Luoghi Sicuri ({typeCounts.SAFEPLACE})
                </button>

                <button
                    className={`filter-btn ${filter === 'DANGERZONE' ? 'active' : ''}`}
                    onClick={() => setFilter('DANGERZONE')}
                >
                    Zone Pericolose ({typeCounts.DANGERZONE})
                </button>

                <button
                    className={`filter-btn ${filter === 'LIMINALSPACE' ? 'active' : ''}`}
                    onClick={() => setFilter('LIMINALSPACE')}
                >
                    Spazi di Confine ({typeCounts.LIMINALSPACE})
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
